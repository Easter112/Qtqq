#ifndef TOPTITTLE_H
#define TOPTITTLE_H

#include <QWidget>

namespace Ui {
class TopTittle;
}

class TopTittle : public QWidget
{
    Q_OBJECT

public:
    explicit TopTittle(QWidget *parent = nullptr);
    void initConnect();
    void loadStyleSheet(const QString &sheetName);
    ~TopTittle();

signals:
    void windowMin();
    void windowMax();
    void windowNormal();
    void windowClose();


private:
    Ui::TopTittle *ui;
    bool maxBtnIsPressed = false;
};

#endif // TOPTITTLE_H
