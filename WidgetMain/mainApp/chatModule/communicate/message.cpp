#include "message.h"
#include "ui_message.h"
#include <QFile>
#include <QDebug>

message::message(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::message)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
    ui->textEdit->viewport()->setCursor(Qt::ArrowCursor);
    LoadInitText();
    ui->textEdit->setHtml(html);
}

QString& message::LoadInitText()
{
    QFile file(":/html/test.html");

    if (file.open(QFile::ReadOnly))
    {
        html = file.readAll();

        file.close();
        return html;
    }
    else
    {
        qWarning() << "Failed to open stylesheet:" << file.fileName();
    }
}

message::~message()
{
    delete ui;
}
