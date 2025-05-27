#ifndef CONTACTFORM_H
#define CONTACTFORM_H

#include <QWidget>
#include "WidgetMain/mainApp/Contact/contact.h"
#include "WidgetMain/mainApp/search/form.h"

namespace Ui {
class contactForm;
}

class contactForm : public QWidget
{
    Q_OBJECT

public:
    explicit contactForm(QWidget *parent = nullptr);
    void changeContactWidget(int);
    ~contactForm();

private:
    Ui::contactForm *ui;
    Contact *m_contact;
    Form *m_search;
};

#endif // CONTACTFORM_H
