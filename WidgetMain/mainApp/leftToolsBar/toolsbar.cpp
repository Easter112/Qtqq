#include "toolsbar.h"
#include "ui_toolsbar.h"
#include <QFile>
#include "WidgetLogin/utils/utils.h"
#include <QDebug>
#include <QButtonGroup>

Utils &util = Utils::getInstance();

toolsBar::toolsBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::toolsBar)
{
    ui->setupUi(this);
    initControl();
    initConnect();

}

toolsBar::~toolsBar()
{
    delete ui;
}

void toolsBar::initControl()
{
    // 设置按钮为可切换
    ui->chatBtn->setCheckable(true);
    ui->contactBtn->setCheckable(true);

    // 创建按钮组，确保互斥选择
    QButtonGroup *buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(ui->chatBtn);
    buttonGroup->addButton(ui->contactBtn);

    // 默认选中第一个按钮（可选）
    ui->chatBtn->setChecked(true);
}

void toolsBar::initConnect()
{
    connect(ui->contactBtn,&QPushButton::clicked,this,&toolsBar::signalContact);
    connect(ui->chatBtn,&QPushButton::clicked,this,&toolsBar::signalChat);
}

void toolsBar::loadStyleSheet(const QString &sheetName)
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



