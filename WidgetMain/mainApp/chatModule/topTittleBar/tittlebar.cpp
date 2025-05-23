#include "tittlebar.h"
#include "ui_tittlebar.h"

tittleBar::tittleBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tittleBar)
{
    ui->setupUi(this);
}

tittleBar::~tittleBar()
{
    delete ui;
}
