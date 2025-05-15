#ifndef MODIFYPASSWORD_H
#define MODIFYPASSWORD_H

#include <QWidget>

namespace Ui {
class ModifyPassword;
}

class ModifyPassword : public QWidget
{
    Q_OBJECT

public:
    explicit ModifyPassword(QWidget *parent = nullptr);
    ~ModifyPassword();
    void initConnect();
    void loadStyleSheet(const QString&);

signals:
    void disPlay(int);

private:
    Ui::ModifyPassword *ui;
};

#endif // MODIFYPASSWORD_H
