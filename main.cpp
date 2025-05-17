#include "WidgetLogin/frame/formwork.h"
#include <QApplication>
#include <QPushButton>
#include <QObject>
#include "WidgetMain/framework/mainform.h"
#include "DataBase/database.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // DataBase &db = DataBase::getInstance();
    // db.initDataBase();
    // FormWork w;



    // w.show();

    // mainWindow mainwindow;

    // QObject::connect(&w,&FormWork::loginSuccess,[&](){
    //     mainwindow.show();
    //     w.close();
    // });
    MainForm mainForm;
    mainForm.show();
    return a.exec();
}
