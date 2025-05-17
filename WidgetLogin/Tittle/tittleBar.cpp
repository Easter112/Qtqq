#include "tittlebar.h"
#include "ui_tittlebar.h"  // 注意：UI 文件生成的头文件
#include "WidgetLogin/utils/utils.h"

#include <QFile>
#include <QColor>
#include <QDebug>
#include <QColorDialog>

// 单例 utils 全局引用
Utils &utils = Utils::getInstance();

tittleBar::tittleBar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::tittleBar)
{
    ui->setupUi(this);
    initWidget();
    initConnect();

}

void tittleBar::initWidget()
{
    loadStyleSheet("loginWidget");

    QPixmap logoPixmap(":/image/qqlogoclassic.png");
    logoPixmap = logoPixmap.scaled(ui->label->width(),ui->label->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);

    ui->label->setPixmap(logoPixmap);

    ui->skinBtn->setIcon(QIcon(":/image/skin.png"));
    ui->skinBtn->setIconSize(QSize(24, 24));  // 设置图标尺寸，必须设置，否则可能看不到图
    ui->skinBtn->setText("");                 // 清除文字（可选）

}

void tittleBar::initConnect()
{
    connect(ui->skinBtn, &QPushButton::clicked, this, [=]() {
        backgroundColor = QColorDialog::getColor(utils.getDefaultColor(), this, "选择颜色");
        if (backgroundColor.isValid()) {
            utils.setDefaultColor(backgroundColor);
            emit colorChange();
            loadStyleSheet("loginWidget");
        }
    });
    connect(ui->minBtn, &QPushButton::clicked, this, [=]() {

        parentWidget()->showMinimized();
    });

    connect(ui->closeBtn, &QPushButton::clicked, this, [=]() {

        parentWidget()->close();
    });
}

tittleBar::~tittleBar()
{
    delete ui;
}

void tittleBar::loadStyleSheet(const QString &sheetName)
{
    backgroundColor = utils.getDefaultColor();
    QFile file(":/css/" + sheetName + ".css");

    if (file.open(QFile::ReadOnly))
    {
        QString qssStyleSheet = file.readAll();
        QString r = QString::number(backgroundColor.red());
        QString g = QString::number(backgroundColor.green());
        QString b = QString::number(backgroundColor.blue());

        qssStyleSheet += QString(
            "QWidget[bodySkin=true] {"
            "background-color: rgb(%1,%2,%3);"
            "border-top-left-radius: 4px;}"
            "QWidget[tittleSkin=true] {"
            "border-top: 1px solid rgba(%1,%2,%3,70);"
            "background-color: rgba(%1,%2,%3,100);"
            "border-bottom-left-radius: 4px;"
            "border-bottom-right-radius: 4px;}"
        ).arg(r, g, b);

        this->setStyleSheet(qssStyleSheet);
        file.close();
    }
    else
    {
        qWarning() << "Failed to open stylesheet:" << file.fileName();
    }
}
