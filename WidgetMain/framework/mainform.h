#ifndef MAINFORM_H
#define MAINFORM_H
#include "WidgetMain/framework/contactform.h"
#include "WidgetMain/mainApp/leftToolsBar/toolsbar.h"

#include <QWidget>

namespace Ui {
class MainForm;
}

class MainForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = nullptr);
    ~MainForm();

private:
    Ui::MainForm *ui;
    contactForm *m_contactForm;
    toolsBar *m_toolsBar;
};

#endif // MAINFORM_H
