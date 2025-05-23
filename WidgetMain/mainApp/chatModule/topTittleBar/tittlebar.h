#ifndef TITTLEBAR_H
#define TITTLEBAR_H

#include <QWidget>

namespace Ui {
class tittleBar;
}

class tittleBar : public QWidget
{
    Q_OBJECT

public:
    explicit tittleBar(QWidget *parent = nullptr);
    ~tittleBar();

private:
    Ui::tittleBar *ui;
};

#endif // TITTLEBAR_H
