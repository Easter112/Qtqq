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

