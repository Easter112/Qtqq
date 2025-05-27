#include "sendmsg.h"
#include "ui_sendmsg.h"
#include <QFile>
#include <QDebug>

sendMsg::sendMsg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sendMsg)
{
    ui->setupUi(this);
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


sendMsg::~sendMsg()
{
    delete ui;
}
