#include "form.h"
#include "ui_form.h"
#include <QFile>
#include <QDebug>

Form::Form(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Form)
{
    ui->setupUi(this);
    initControl();
    initConnect();
}

void Form::initControl()
{

}

void Form::initConnect()
{

}

Form::~Form()
{
    delete ui;
}

void Form::loadStyleSheet(const QString &sheetName)
{
    QFile file(":/css/" + sheetName + ".css");

    if (file.open(QFile::ReadOnly))
    {
        QString qssStyleSheet = file.readAll();
        this->setStyleSheet(qssStyleSheet);
        file.close();
    }
    else
    {
        qWarning() << "Failed to open stylesheet:" << file.fileName();
    }
}

