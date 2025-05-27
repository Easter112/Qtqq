#ifndef MAINFORM_H
#define MAINFORM_H
#include "WidgetMain/framework/contactform.h"
#include "WidgetMain/mainApp/leftToolsBar/toolsbar.h"
#include "WidgetMain/framework/chatform.h"
#include "WidgetMain/utils/windowbehaviour.h"

#include <QWidget>

namespace Ui {
class MainForm;
}

class MainForm : public windowBehaviour
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = nullptr);
    void initConnect();
    ~MainForm();

public slots:
    void onClose();
    void onMax();
    void onMin();
    void onNormal();

signals:
    void changeToContact(int index);
    void changeToChat(int index);

private:
    Ui::MainForm *ui;
    contactForm *m_contactForm;
    toolsBar *m_toolsBar;
    chatForm *m_chatForm;
};

#endif // MAINFORM_H
