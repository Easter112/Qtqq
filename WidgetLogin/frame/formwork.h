#ifndef FORMWORK_H
#define FORMWORK_H

#include <QWidget>
#include "Body/centerwidget.h"
#include "Tittle/tittlebar.h"
#include "baseframe.h"

namespace Ui {
class FormWork;
}

class FormWork : public BaseFrame
{
    Q_OBJECT

public:
    explicit FormWork(BaseFrame *parent = nullptr);
    ~FormWork();

signals:
    void loginSuccess();

private:
    Ui::FormWork *ui;
    tittleBar *m_tittleBar;
    centerWidget * m_centerwidget;
};

#endif // FORMWORK_H
