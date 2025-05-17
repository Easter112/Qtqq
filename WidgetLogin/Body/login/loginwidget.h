#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QApplication>
#include <QFile>
#include <QStackedLayout>
#include "WidgetLogin/Tittle/tittlebar.h"

QT_BEGIN_NAMESPACE
namespace Ui { class loginWidget; }
QT_END_NAMESPACE

class loginWidget : public QWidget
{
    Q_OBJECT

signals:
    void loginSuccess();
    void disPlay(int index);


public:
    loginWidget(QWidget *parent = nullptr);
    void loadStyleSheet(const QString & sheetName);
    void Verify();
    ~loginWidget();

private:
    Ui::loginWidget *ui;
    tittleBar *titleBar;
    QString m_styleSheetName;
    QColor backgroundColor;
};


#endif // LOGINWIDGET_H
