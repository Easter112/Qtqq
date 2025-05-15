#include "baseframe.h"
#include <QMouseEvent>

BaseFrame::BaseFrame(QWidget *parent)
    : QWidget(parent), m_isPressed(false)
{
    // 建议添加无边框设置在这里
    setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
}

void BaseFrame::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_isPressed = true;
        // 记录当前窗口与鼠标的偏移
        startPos = event->globalPos() - this->frameGeometry().topLeft();
    }
}

void BaseFrame::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isPressed && (event->buttons() & Qt::LeftButton)) {
        // 移动窗口
        this->move(event->globalPos() - startPos);
    }
}

void BaseFrame::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_isPressed = false;
}
