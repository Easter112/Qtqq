#ifndef WINDOWBEHAVIOUR_H
#define WINDOWBEHAVIOUR_H

#include <QWidget>
#include <QMouseEvent>
class windowBehaviour : public QWidget
{
    Q_OBJECT
public:
    explicit windowBehaviour(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    bool m_dragging = false;
    QPoint m_dragStartPos;   // 鼠标按下时的全局坐标
    QPoint m_windowStartPos; // 窗口初始位置

};

#endif // WINDOWBEHAVIOUR_H
