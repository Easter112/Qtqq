#include "mainform.h"
#include "ui_mainform.h"
#include <QFile>

MainForm::MainForm(QWidget *parent)
    : windowBehaviour(parent)
    , ui(new Ui::MainForm)
{
    ui->setupUi(this);
    m_contactForm = new contactForm;
    m_toolsBar = new toolsBar;

    ui->contactLayout_2->addWidget(m_contactForm);
    ui->leftToollLayout->addWidget(m_toolsBar);
    m_toolsBar->loadStyleSheet("toolsBar");
    
    
    m_chatForm = new chatForm;
    ui->chatLayout_2->addWidget((m_chatForm));
    setWindowFlag(Qt::FramelessWindowHint);
    setStyleSheet(QString("QWidget#MainForm {"
                          "background-color: #f3f3f3;"
                          "border: none;"
                          "padding: 0;}"));
    initConnect();

}

void MainForm::initConnect()
{
    connect(m_chatForm,&chatForm::requestMin,this,&MainForm::onMin);
    connect(m_chatForm,&chatForm::requestMax,this,&MainForm::onMax);
    connect(m_chatForm,&chatForm::requestClose,this,&MainForm::onClose);
    connect(m_chatForm,&chatForm::requestNormal,this,&MainForm::onNormal);

    m_contactForm->changeContactWidget(1);
    connect(m_toolsBar,&toolsBar::signalContact,this,[=](){
        m_contactForm->changeContactWidget(0);
    });
    connect(m_toolsBar,&toolsBar::signalChat,this,[=](){
        m_contactForm->changeContactWidget(1);
    });
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::onClose()
{
    close();
}

void MainForm::onMax()
{
    showMaximized();
}

void MainForm::onMin()
{
    showMinimized();
}

void MainForm::onNormal()
{
    showNormal();
}

