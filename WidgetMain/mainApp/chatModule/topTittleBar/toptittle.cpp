#include "toptittle.h"
#include "ui_toptittle.h"
#include <QDebug>
#include <QFile>

TopTittle::TopTittle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TopTittle)
{
    ui->setupUi(this);
    initConnect();
}

void TopTittle::initConnect()
{
    connect(ui->btnMin,&QPushButton::clicked,this,&TopTittle::windowMin);
    connect(ui->btnMax,&QPushButton::clicked,this,[=](){
        if(!maxBtnIsPressed)
        {
            maxBtnIsPressed = true;
            ui->btnMax->setIcon(QIcon(":/image/restore.png"));
            windowMax();
        }
        else
        {
            maxBtnIsPressed = false;
            ui->btnMax->setIcon(QIcon(":/image/max.png"));
            windowNormal();
        }

    });
    connect(ui->btnClose,&QPushButton::clicked,this,&TopTittle::windowClose);

    //connect(ui->btnMax,&QPushButton::clicked,this,&TopTittle::windowMin);
}

void TopTittle::loadStyleSheet(const QString &sheetName)
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

TopTittle::~TopTittle()
{
    delete ui;
}
