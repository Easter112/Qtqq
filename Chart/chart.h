#ifndef CHART_H
#define CHART_H

#include <QWidget>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChartView>
#include <QSerialPort>
#include <QTimer>
#include <QDateTime>
#include <QQueue>

QT_BEGIN_NAMESPACE
namespace Ui {
class Chart;
}
QT_END_NAMESPACE

class Chart : public QWidget
{
    Q_OBJECT

public:
    Chart(QWidget *parent = nullptr);
    ~Chart();
    void initControl();
    void initConnect();

private:
    void lockControl();
    void unlockControl();

public slots:
    void readSerialData();

private:
    Ui::Chart *ui;
    QChart *chart;
    QLineSeries *series;
    QDateTimeAxis *axisX;
    QValueAxis *axisY;
    QChartView *chartView;
    QSerialPort *serial;
    QDateTime startTime;
    QDateTime endTime;
    bool btnIsLocked = false;
    QByteArray buffer;
    QQueue<QPointF> dataQueue; // 存储温度数据点（时间戳, 温度）
    const int maxPoints = 7;   // 最多保留7个点

};
#endif // CHART_H
