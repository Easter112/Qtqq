#include "WidgetLogin/Body/centerwidget.h"
#include "ui_centerwidget.h"

centerWidget::centerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::centerWidget)
{
    ui->setupUi(this);
    initControl();
    initConnect();
}

centerWidget::~centerWidget()
{
    delete ui;
}

void centerWidget::initControl()
{
    m_loginwidget = new loginWidget;
    m_registWidget= new registWidget;
    m_modifyPassword = new ModifyPassword;

    m_StackedLayout = new QStackedLayout(this);

    m_StackedLayout->addWidget(m_loginwidget);
    m_StackedLayout->addWidget(m_registWidget);
    m_StackedLayout->addWidget(m_modifyPassword);

}

void centerWidget::initConnect()
{
//    connect(m_loginwidget,&loginWidget::disPlay,m_StackedLayout,&QStackedLayout::setCurrentIndex);

    //connect(this,&centerWidget::SignalColorChange,m_loginwidget,&loginWidget::SkinChange);
    connect(m_loginwidget, &loginWidget::disPlay, this, [=](int index){
        m_StackedLayout->setCurrentIndex(index);
        if(index == 1)
            m_registWidget->loadStyleSheet("loginWidget");
        else
            m_modifyPassword->loadStyleSheet("loginWidget");
    });

    connect(m_registWidget,&registWidget::disPlay,m_StackedLayout,&QStackedLayout::setCurrentIndex);
    connect(m_modifyPassword,&ModifyPassword::disPlay,m_StackedLayout,&QStackedLayout::setCurrentIndex);
    connect(m_loginwidget,&loginWidget::loginSuccess,this,&centerWidget::LoginSuccess);
}

void centerWidget::OnColorChange()
{
    m_registWidget->loadStyleSheet("loginWidget");
    m_modifyPassword->loadStyleSheet("loginWidget");
    m_loginwidget->loadStyleSheet("loginWidget");
}

