#ifndef REGISTWIDGET_H
#define REGISTWIDGET_H

#include <QWidget>

namespace Ui {
class registWidget;
}

class registWidget : public QWidget
{
    Q_OBJECT

public:
    explicit registWidget(QWidget *parent = nullptr);
    void initConnect();
    void initControl();
    void loadStyleSheet(const QString &sheetName);
    void regist();
    ~registWidget();

signals:
    void disPlay(int);

private:
    Ui::registWidget *ui;
};

#endif // REGISTWIDGET_H
