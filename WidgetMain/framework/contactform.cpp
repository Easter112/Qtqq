#include "contactform.h"
#include "ui_contactform.h"

contactForm::contactForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::contactForm)
{
    ui->setupUi(this);
    m_contact = new Contact;
    m_search = new Form;

    ui->searchLayout->addWidget(m_search);
    ui->personLayout->addWidget(m_contact);

    m_search->loadStyleSheet("search");

}

void contactForm::changeContactWidget(int index)
{
    m_contact->changeWidget(index);
}

contactForm::~contactForm()
{
    delete ui;
}
