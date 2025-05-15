#include "formwork.h"
#include "ui_formwork.h"
#include <QSettings>

FormWork::FormWork(BaseFrame *parent) :
    BaseFrame(parent),
    ui(new Ui::FormWork)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    m_tittleBar = new tittleBar;
    m_centerwidget = new centerWidget;

    ui->tittleBarLayout->addWidget(m_tittleBar);
    ui->bodyLayout->addWidget(m_centerwidget);
    //connect(m_tittleBar,&tittleBar::colorChange,m_centerwidget,&centerWidget::SignalColorChange);
    connect(m_tittleBar,&tittleBar::colorChange,m_centerwidget,&centerWidget::OnColorChange);
    connect(m_centerwidget,&centerWidget::LoginSuccess,this,&FormWork::loginSuccess);
}

FormWork::~FormWork()
{
    delete ui;
}




