#include "chatwindow.h"
#include "ui_chatwindow.h"

chatWindow::chatWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chatWindow)
{
    ui->setupUi(this);
}

chatWindow::~chatWindow()
{
    delete ui;
}

void chatWindow::addChatWindow()
{
    chatForm *m_chatForm = new chatForm;
    ui->stackedWidget->setCurrentWidget(m_chatForm);
}
