#ifndef TOOLSBAR_H
#define TOOLSBAR_H

#include <QWidget>
#include "WidgetMain/utils/windowbehaviour.h"

namespace Ui {
class toolsBar;
}

class toolsBar : public QWidget
{
    Q_OBJECT

public:
    explicit toolsBar(QWidget *parent = nullptr);
    ~toolsBar();
    void initControl();
    void initConnect();
    void loadStyleSheet(const QString &sheetName);


signals:
    void signalContact();
    void signalChat();

private:
    Ui::toolsBar *ui;
};

#endif // TOOLSBAR_H
