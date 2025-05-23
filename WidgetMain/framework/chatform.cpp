#include "chatform.h"
#include "ui_chatform.h"

chatForm::chatForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chatForm)
{
    ui->setupUi(this);
}

chatForm::~chatForm()
{
    delete ui;
}
