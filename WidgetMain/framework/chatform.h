#ifndef CHATFORM_H
#define CHATFORM_H

#include <QWidget>
#include "WidgetMain/mainApp/chatModule/communicate/message.h"
#include "WidgetMain/mainApp/chatModule/send/sendmsg.h"
#include "WidgetMain/mainApp/chatModule/topTittleBar/toptittle.h"

namespace Ui {
class chatForm;
}

class chatForm : public QWidget
{
    Q_OBJECT

public:
    explicit chatForm(QWidget *parent = nullptr);
    void initConnect();
    ~chatForm();

signals:
    void requestClose();
    void requestMax();
    void requestMin();
    void requestNormal();


private:
    Ui::chatForm *ui;
    message *m_message;
    sendMsg *m_sendMsg;
    TopTittle *m_topTittle;
};

#endif // CHATFORM_H
