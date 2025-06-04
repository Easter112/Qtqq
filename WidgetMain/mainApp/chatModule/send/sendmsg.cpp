#include "sendmsg.h"
#include "ui_sendmsg.h"
#include <QFile>
#include <QDebug>
#include <QKeyEvent>

sendMsg::sendMsg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sendMsg)
{
    ui->setupUi(this);
    ui->textEdit->installEventFilter(this);
    initControl();
    initConnect();
}

void sendMsg::loadStyleSheet(const QString &sheetName)
{
        QFile file(":/css/" + sheetName + ".css");

        if (file.open(QFile::ReadOnly))
        {
            QString qssStyleSheet = file.readAll();
            this->setStyleSheet(qssStyleSheet);
            file.close();
        }
        else
        {
            qWarning() << "Failed to open stylesheet:" << file.fileName();
        }
}

void sendMsg::keyPressEvent(QKeyEvent *event)
{
    if(!ui->sendBtn->isEnabled())
        return;
    if(event->key() == Qt::Key_Enter)
    {
        QString text = ui->textEdit->toPlainText();
        qDebug() << text;
    }

}

// textEdit会拦截Enter的事件用于自己换行 通过事件过滤器函数拦截textEdit的事件进行自定义
bool sendMsg::eventFilter(QObject *watched, QEvent *event) {
    if (watched == ui->textEdit && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return) {
            if (ui->sendBtn->isEnabled()) {
                QString text = ui->textEdit->toPlainText();
                qDebug() << "Enter pressed, text:" << text;

                return true; // 拦截事件，阻止默认换行行为
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

void sendMsg::initControl()
{
    if(ui->textEdit->toPlainText().trimmed().isEmpty())     //trimmed()自动过滤掉\r \n 和空
        ui->sendBtn->setEnabled(false);
}

void sendMsg::initConnect()
{
    connect(ui->textEdit,&QTextEdit::textChanged,this,[=](){
        if(ui->textEdit->toPlainText().trimmed().isEmpty())
            ui->sendBtn->setEnabled(false);
        else
            ui->sendBtn->setEnabled(true);
    });
}


sendMsg::~sendMsg()
{
    delete ui;
}
