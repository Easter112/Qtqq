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
    void initWidget();
    void initConnect();
    ~tittleBar();
    void loadStyleSheet(const QString & sheetName);

signals:
    void colorChange();

private:
    Ui::tittleBar *ui;
    QColor backgroundColor;
};

#endif // TITTLEBAR_H
