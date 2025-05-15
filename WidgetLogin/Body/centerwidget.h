#ifndef CENTERWIDGET_H
#define CENTERWIDGET_H
#include <QStackedLayout>
#include "Body/login/loginwidget.h"
#include "Body/regist/registwidget.h"
#include "Body/modify/modifypassword.h"

#include <QWidget>

namespace Ui {
class centerWidget;
}

class centerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit centerWidget(QWidget *parent = nullptr);
    ~centerWidget();
    void initControl();
    void initConnect();

signals:
    void LoginSuccess();

public slots:
    void OnColorChange();

private:
    Ui::centerWidget *ui;
    QStackedLayout *m_StackedLayout;
    loginWidget *m_loginwidget;
    registWidget*m_registWidget;
    ModifyPassword *m_modifyPassword;

};

#endif // CENTERWIDGET_H
