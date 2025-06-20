﻿#include "loginwidget.h"
#include "ui_loginwidget.h"
#include <QFile>
#include <QSettings>
#include <QDebug>
#include "WidgetLogin/utils/utils.h"
#include "DataBase/database.h"

static Utils &utils = Utils::getInstance();
static DataBase &db = DataBase::getInstance();

loginWidget::loginWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::loginWidget)
{
    ui->setupUi(this);

    connect(ui->loginBtn,&QPushButton::clicked,this,[=](){

        int account = ui->m_account->text().toUInt();
        QString passwd = nullptr;


        if(db.QueryData(account,&passwd))
        {
            if(passwd == ui->m_password->text())
            {
                qDebug() << "login success!" ;
                emit loginSuccess();
            }
            else
            {
                qDebug() << "login failed,password incorrect!" ;
            }
        }
        else
        {
          qDebug() << "login failed,account not found!" ;
        }

    });

    loadStyleSheet("loginWidget");
    ui->m_password->setEchoMode(QLineEdit::Password);

    connect(ui->btn_regist,&QPushButton::clicked,this,[=](){
        qDebug() << "regist is clicked!";
        emit disPlay(1);
    });

    connect(ui->btn_modifyPassword,&QPushButton::clicked,this,[=](){
        qDebug() << "modify is clicked!";
        emit disPlay(2);
    });
    //connect(this,&loginWidget::disPlay,m_StackedLayout,&QStackedLayout::setCurrentIndex);
}

void loginWidget::loadStyleSheet(const QString & sheetName)
{
    m_styleSheetName = sheetName;
    backgroundColor = utils.getDefaultColor();
    QFile file(":/css/" + sheetName + ".css");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        setStyleSheet("");
        QString qssStyleSheet = file.readAll();

        //获取当前皮肤颜色的RGB值
        QString r = QString::number(backgroundColor.red());
        QString g = QString::number(backgroundColor.green());
        QString b = QString::number(backgroundColor.blue());
        qDebug() << r << ":" << g << " " << b;
        qssStyleSheet += QString("QWidget[bodySkin=true] {"
                                 "background-color: rgb(%1,%2,%3);"
                                 "border-top-left-radius: 4px;}"
                                 "QPushButton#headBtn {"
                                 "background-color: rgb(%1, %2, %3);"
                                 "color: white;"
                                 "border: none;"
                                 "border-radius: 6px;"
                                 "font-weight: bold;})").arg(r).arg(g).arg(b);
        setStyleSheet(qssStyleSheet);
    }
    file.close();
}

loginWidget::~loginWidget()
{
    delete ui;
    delete titleBar;
}

void loginWidget::Verify()
{
  QString account  =  ui->m_account->text();

}




