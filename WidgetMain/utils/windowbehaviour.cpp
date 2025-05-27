#include "windowbehaviour.h"

windowBehaviour::windowBehaviour(QWidget *parent) : QWidget(parent)
{

}

void windowBehaviour::mousePressEvent(QMouseEvent *event)  {
    if (event->button() == Qt::LeftButton) {
        m_dragStartPos = event->globalPos();  // 记录鼠标按下时的全局坐标
        m_windowStartPos = this->pos();       // 记录窗口初始位置
        m_dragging = true;
    }
}

void windowBehaviour::mouseMoveEvent(QMouseEvent *event)  {
    if (m_dragging) {
        QPoint delta = event->globalPos() - m_dragStartPos;  // 计算鼠标移动距离
        this->move(m_windowStartPos + delta);               // 更新窗口位置
    }
}

void windowBehaviour::mouseReleaseEvent(QMouseEvent *event)  {
    if (event->button() == Qt::LeftButton) {
        m_dragging = false;
    }
}
