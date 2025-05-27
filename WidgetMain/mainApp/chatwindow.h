#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include "WidgetMain/framework/chatform.h"

namespace Ui {
class chatWindow;
}

class chatWindow : public QWidget
{
    Q_OBJECT

public:
    explicit chatWindow(QWidget *parent = nullptr);
    ~chatWindow();
    void addChatWindow();

private:
    Ui::chatWindow *ui;
};

#endif // CHATWINDOW_H
