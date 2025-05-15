#include "modifypassword.h"
#include "ui_modifypassword.h"
#include "Utils/utils.h"
#include <QDebug>
#include <QFile>

static Utils &utils = Utils::getInstance();

ModifyPassword::ModifyPassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifyPassword)
{
    ui->setupUi(this);
    initConnect();
}

ModifyPassword::~ModifyPassword()
{
    delete ui;
}

void ModifyPassword::initConnect()
{
    connect(ui->backBtn,&QPushButton::clicked,this,[=](){
        emit disPlay(0);
    });
}

void ModifyPassword::loadStyleSheet(const QString & sheetName)
{
    QColor backgroundColor = utils.getDefaultColor();
    QFile file(":/css/" + sheetName + ".css");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        //setStyleSheet("");
        QString qssStyleSheet = file.readAll();

        //获取当前皮肤颜色的RGB值
        QString r = QString::number(backgroundColor.red());
        QString g = QString::number(backgroundColor.green());
        QString b = QString::number(backgroundColor.blue());
        qssStyleSheet += QString(R"(QWidget[bodySkin=true]{
                                    background-color: rgb(%1, %2, %3);}
                                    QPushButton#headBtn {
                                    background-color: rgb(%1, %2, %3);
                                    color: white;
                                    border: none;
                                    border-radius: 6px;
                                    font-weight: bold;})").arg(r).arg(g).arg(b);
        qDebug() << qssStyleSheet;
        setStyleSheet(qssStyleSheet);
        //update();
    }
    else
    {
        qDebug() << "Failed to open CSS file!";
    }
    file.close();
}
