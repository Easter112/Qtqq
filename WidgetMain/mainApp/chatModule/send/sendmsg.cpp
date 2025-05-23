#include "sendmsg.h"
#include "ui_sendmsg.h"

sendMsg::sendMsg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sendMsg)
{
    ui->setupUi(this);
}

sendMsg::~sendMsg()
{
    delete ui;
}
