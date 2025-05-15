#include "registwidget.h"
#include "ui_registwidget.h"
#include "Utils/utils.h"
#include <QStyle>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include "DataBase/database.h"

static Utils &utils = Utils::getInstance();
static DataBase &db = DataBase::getInstance();

registWidget::registWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registWidget)
{
    ui->setupUi(this);
    initConnect();
    ui->passwordInput->setEchoMode(QLineEdit::Password);
    ui->passwordReInput->setEchoMode(QLineEdit::Password);
}

void registWidget::initConnect()
{
    connect(ui->backBtn,&QPushButton::clicked,this,[=](){
       disPlay(0);
    });
    connect(ui->registBtn,&QPushButton::clicked,this,&registWidget::regist);
}

void registWidget::initControl()
{
}

void registWidget::loadStyleSheet(const QString &sheetName)
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

void registWidget::regist()
{
    if(ui->nameInput->text().isEmpty())
    {
        ui->label->setText("请输入用户名!");
        ui->label->setStyleSheet("color: yellow;");

    }
    else
    {
        if(ui->passwordInput->text().isEmpty())
        {
             ui->label->setText("请输入密码!");
             ui->label->setStyleSheet("color: yellow;");
        }
        else
        {
            if(ui->passwordReInput->text().isEmpty())
            {
                 ui->label->setText("请再次输入密码!");
                 ui->label->setStyleSheet("color: yellow;");
            }
            else
            {
                //if(db.InsertData(ui->accountInput))
                if(ui->passwordInput->text() == ui->passwordReInput->text())
                {
                    bool ret = db.NameIsSame(ui->nameInput->text());
                    if(ret)
                    {
                        ui->label->setText("用户名已经存在!");
                        ui->label->setStyleSheet("color: red;");
//                        regist();
                        return;
                    }

                    //此处应该用switch
                    if(db.InsertData(ui->nameInput->text(),ui->passwordInput->text()))
                    {
                        int account = db.IdReturn(ui->nameInput->text());
                        QString message = "成功注册,账号为" + QString::number(account);
                        QMessageBox::information(this,"注册成功",message);
                        ui->nameInput->setText("");
                        ui->passwordInput->setText("");
                        ui->passwordReInput->setText("");
                    }
                }
                else
                {
                    ui->label->setText("两次密码输入不一致,请查正后输入!");
                    ui->label->setStyleSheet("color: red;");
                    return;
                }
            }
        }
    }
}

registWidget::~registWidget()
{
    delete ui;
}


