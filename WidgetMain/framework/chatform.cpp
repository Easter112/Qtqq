#include "chatform.h"
#include "ui_chatform.h"


chatForm::chatForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chatForm)
{
    ui->setupUi(this);
    m_message = new message;
    m_sendMsg = new sendMsg;
    m_topTittle = new TopTittle;
    ui->tittleLayout->addWidget(m_topTittle);
    ui->messageLayout->addWidget(m_message);
    ui->sendMsgLayout->addWidget(m_sendMsg);
    m_topTittle->loadStyleSheet("topTittle");
    m_sendMsg->loadStyleSheet("sendMsg");
    initConnect();
}

void chatForm::initConnect()
{
    connect(m_topTittle,&TopTittle::windowMin,this,&chatForm::requestMin);
    connect(m_topTittle,&TopTittle::windowMax,this,&chatForm::requestMax);
    connect(m_topTittle,&TopTittle::windowClose,this,&chatForm::requestClose);
    connect(m_topTittle,&TopTittle::windowNormal,this,&chatForm::requestNormal);
}

chatForm::~chatForm()
{
    delete ui;
}
