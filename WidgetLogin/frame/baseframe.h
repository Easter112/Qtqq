#ifndef BASEFRAME_H
#define BASEFRAME_H

#include <QWidget>
#include <QMouseEvent>

class BaseFrame : public QWidget
{
    Q_OBJECT
public:
    explicit BaseFrame(QWidget *parent = nullptr);

signals:

public:
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    bool m_isPressed;
    QPoint startPos;

};

#endif // BASEFRAME_H
