#ifndef MESSAGE_H
#define MESSAGE_H

#include <QWidget>

namespace Ui {
class message;
}

class message : public QWidget
{
    Q_OBJECT

public:
    explicit message(QWidget *parent = nullptr);
    QString& LoadInitText();
    ~message();

private:
    Ui::message *ui;
    QString html;
};

#endif // MESSAGE_H
