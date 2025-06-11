#include "chart.h"
#include "ui_chart.h"
#include <QSerialPortInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVBoxLayout>
#include <QDebug>

const int TIME_WINDOW_SECS = 600;  // 显示最近10分钟

Chart::Chart(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Chart)
    , chart(new QChart())
    , series(new QLineSeries())
    , axisX(new QDateTimeAxis())
    , axisY(new QValueAxis())
    , chartView(new QChartView(chart))
    , serial(new QSerialPort)
{
    ui->setupUi(this);
    initControl();
    initConnect();
}

Chart::~Chart()
{
    if (serial->isOpen())
        serial->close();
    delete ui;
}

void Chart::initControl()
{
    chart->addSeries(series);

    QDateTime now = QDateTime::currentDateTime();
    startTime = now.addSecs(-TIME_WINDOW_SECS);
    endTime = now;

    axisX->setFormat("HH:mm:ss");
    axisX->setTitleText("时间");
    axisX->setTickCount(7);
    axisX->setMin(startTime);
    axisX->setMax(endTime);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    axisY->setRange(0, 100);
    axisY->setTitleText("温度");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->hide();
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *mainLayout = new QVBoxLayout(ui->widget);
    mainLayout->addWidget(chartView);

    // 添加串口列表
    const auto ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : ports)
        ui->comboBox->addItem(info.portName());
}

void Chart::initConnect()
{
    connect(ui->serialBtn, &QPushButton::clicked, this, [=]() {
        if (btnIsLocked) {
            unlockControl();
            btnIsLocked = false;
        } else {
            QString portName = ui->comboBox->currentText();
#ifdef Q_OS_WIN
            serial->setPortName(portName);
#else
            serial->setPortName("/dev/" + portName); // Linux 下使用 /dev/ttyXXX
#endif
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);

            if (serial->open(QIODevice::ReadOnly)) {
                connect(serial, &QSerialPort::readyRead, this, &Chart::readSerialData);
                lockControl();
                btnIsLocked = true;
                qDebug() << "串口已打开：" << portName;
            } else {
                qDebug() << "串口打开失败：" << serial->errorString();
            }
        }
    });
}

void Chart::lockControl()
{
    ui->comboBox->setDisabled(true);
    ui->serialBtn->setText("关闭串口");
}

void Chart::unlockControl()
{
    ui->comboBox->setDisabled(false);
    ui->serialBtn->setText("打开串口");
    serial->close();
}

void Chart::readSerialData()
{
    buffer += serial->readAll();
    while (buffer.contains('\n')) {
        int index = buffer.indexOf('\n');
        QByteArray line = buffer.left(index).trimmed();
        buffer.remove(0, index + 1);

        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(line, &err);
        if (err.error == QJsonParseError::NoError && doc.isObject()) {
            QJsonObject obj = doc.object();
            double temp = obj["temperature"].toDouble();

            QDateTime now = QDateTime::currentDateTime();
            qint64 msecTime = now.toMSecsSinceEpoch();
            series->append(msecTime, temp);
            chartView->repaint();  // 可放在 append 后


            // 移除旧数据，避免数据过多（可选）
            while (!series->points().isEmpty() &&
                   series->points().first().x() < now.addSecs(-TIME_WINDOW_SECS).toMSecsSinceEpoch()) {
                series->removePoints(0, 1);
            }

            endTime = now;
            startTime = endTime.addSecs(-TIME_WINDOW_SECS);
            axisX->setMin(startTime);
            axisX->setMax(endTime);

            qDebug() << "温度:" << temp << "时间:" << now.toString("HH:mm:ss");
        } else {
            qDebug() << "JSON 解析失败：" << err.errorString();
        }
    }
}
