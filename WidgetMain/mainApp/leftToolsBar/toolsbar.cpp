#include "toolsbar.h"
#include "ui_toolsbar.h"
#include <QFile>
#include "WidgetLogin/utils/utils.h"

Utils &util = Utils::getInstance();

toolsBar::toolsBar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::toolsBar)
{
    ui->setupUi(this);
    ui->chatBtn->setIcon(QIcon(util.createChatIcon()));
    ui->chatBtn->setIconSize(QSize(50, 50));

    ui->contactBtn->setIcon(QIcon(util.createUserIcon()));
    ui->contactBtn->setIconSize(QSize(50, 50));
}

toolsBar::~toolsBar()
{
    delete ui;
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
