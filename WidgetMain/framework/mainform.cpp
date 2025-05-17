#include "mainform.h"
#include "ui_mainform.h"
#include <QFile>

MainForm::MainForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainForm)
{
    ui->setupUi(this);
    //setWindowFlag(Qt::FramelessWindowHint);
    m_contactForm = new contactForm;
    m_toolsBar = new toolsBar;

    ui->contactLayout_2->addWidget(m_contactForm);
    ui->leftToollLayout->addWidget(m_toolsBar);
    m_toolsBar->loadStyleSheet("toolsBar");

}

MainForm::~MainForm()
{
    delete ui;
}

