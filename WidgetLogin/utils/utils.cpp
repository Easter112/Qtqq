#include "utils.h"
#include <QSettings>
#include <QApplication>
#include <QFile>
#include <QPainter>

void Utils::setDefaultColor(const QColor &color)
{
    QString path = QApplication::applicationDirPath() + "/" + "config.ini";
    QSettings setting(path, QSettings::IniFormat);
    setting.setValue("DefaultSkin/red", color.red());
    setting.setValue("DefaultSkin/green", color.green());
    setting.setValue("DefaultSkin/blue", color.blue());
}

QColor Utils::getDefaultColor()
{
    const QString path = QApplication::applicationDirPath() + "/" + QString("config.ini");
    if (!QFile::exists(path))
        setDefaultColor(QColor(22, 154, 218));
    QSettings setting(path, QSettings::IniFormat);
    QColor color;
    color.setRed(setting.value("DefaultSkin/red").toInt());
    color.setGreen(setting.value("DefaultSkin/green").toInt());
    color.setBlue(setting.value("DefaultSkin/blue").toInt());

    //qDebug() << setting.value("DefaultSkin/red").toInt();
    return color;
}

// 生成白色对话气泡图标
QPixmap Utils::createChatIcon() {
    QPixmap pixmap(50, 50);
    pixmap.fill(Qt::transparent); // 透明背景

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    // 白色空心对话气泡
    painter.setPen(QPen(Qt::white, 2)); // 白色边框
    painter.setBrush(Qt::NoBrush);      // 空心
    painter.drawEllipse(10, 10, 30, 30); // 气泡主体
    painter.drawRect(20, 35, 10, 5);    // 气泡底部小三角

    return pixmap;
}

// 生成绿色人形带对话气泡图标
QPixmap Utils::createUserIcon() {
    QPixmap pixmap(50, 50);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绿色人形（简化版）
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 200, 0)); // 绿色填充
    painter.drawEllipse(15, 5, 20, 20);  // 头部
    painter.drawRect(20, 25, 10, 15);    // 身体

    // 人形手持的白色对话气泡
    painter.setPen(QPen(Qt::white, 1));
    painter.setBrush(Qt::white);
    painter.drawEllipse(30, 15, 15, 10); // 小气泡

    return pixmap;
}

