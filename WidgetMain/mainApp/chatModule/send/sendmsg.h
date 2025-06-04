#ifndef SENDMSG_H
#define SENDMSG_H

#include <QWidget>

namespace Ui {
class sendMsg;
}

class sendMsg : public QWidget
{
    Q_OBJECT

public:
    explicit sendMsg(QWidget *parent = nullptr);
    void loadStyleSheet(const QString &sheetName);
    void keyPressEvent(QKeyEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;
    void initControl();
    void initConnect();
    ~sendMsg();

private:
    Ui::sendMsg *ui;
};

#endif // SENDMSG_H
