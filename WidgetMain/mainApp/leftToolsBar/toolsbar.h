#ifndef TOOLSBAR_H
#define TOOLSBAR_H

#include <QWidget>

namespace Ui {
class toolsBar;
}

class toolsBar : public QWidget
{
    Q_OBJECT

public:
    explicit toolsBar(QWidget *parent = nullptr);
    ~toolsBar();
    void loadStyleSheet(const QString &sheetName);

private:
    Ui::toolsBar *ui;
};

#endif // TOOLSBAR_H
