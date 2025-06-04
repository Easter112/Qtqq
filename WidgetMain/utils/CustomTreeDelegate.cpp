#include "CustomTreeDelegate.h"
#include <QPainter>

void CustomTreeDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // 先调用父类的绘制方法
    QStyledItemDelegate::paint(painter, option, index);

    // 获取模型和项
    const QAbstractItemModel *model = index.model();
    if (!model->hasChildren(index))
        return;

    // 获取展开状态
    bool isExpanded = static_cast<const QTreeWidget*>(option.widget)->isExpanded(index);


    // 计算箭头位置
    QRect r = option.rect;

    QRect arrowRect(r.left() + 5,r.top(),12,12);
    arrowRect.moveTop(arrowRect.top() + (option.rect.height() - arrowRect.height()) / 2 + 3);

    // 绘制箭头
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    QPen pen(Qt::gray, 2);
    painter->setPen(pen);

    if (isExpanded) {
        // 向下箭头 (类似"∨")
        QPoint points[] = {
            arrowRect.topLeft(),
            QPoint(arrowRect.center().x(), arrowRect.bottom() - 4),
            arrowRect.topRight()
        };
        painter->drawPolyline(points, 3);
    } else {
        // 向右箭头 (类似">")
        QPoint points[] = {
            QPoint(arrowRect.topLeft().x() + 3,arrowRect.topLeft().y()),
            QPoint(arrowRect.right(), arrowRect.center().y()),
            QPoint(arrowRect.bottomLeft().x() + 3,arrowRect.bottomLeft().y())
        };
        painter->drawPolyline(points, 3);
    }
    QString text = index.data(Qt::UserRole + 1).toString();
    QRect textRect = option.rect.adjusted(arrowRect.right() + 10, 0, 0, 0);
    painter->save();
    painter->setPen(Qt::black);  // 明确设置文本颜色
    QFont font;
    font.setPointSize(10);
    painter->setFont(font);
    painter->drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, text);
    painter->restore();

    painter->restore();
}
