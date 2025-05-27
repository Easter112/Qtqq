#include "message.h"
#include "ui_message.h"

message::message(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::message)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
    ui->textEdit->viewport()->setCursor(Qt::ArrowCursor);
}




message::~message()
{
    delete ui;
}
