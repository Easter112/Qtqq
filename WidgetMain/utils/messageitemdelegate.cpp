#include "messageitemdelegate.h"


void MessageItemDelegate::paint(QPainter *p, const QStyleOptionViewItem &opt, const QModelIndex &index) const
{
    // 判断是否是分组项，如果是就使用默认绘制
    bool isGroup = index.data(Qt::UserRole + 99).toBool();
    if (isGroup) {
        QStyledItemDelegate::paint(p, opt, index);
        return;
    }

    p->save();
    QRect r = opt.rect;
    p->setRenderHint(QPainter::Antialiasing);
    p->setRenderHint(QPainter::SmoothPixmapTransform);

    // 获取数据
    QPixmap raw = index.data(Qt::UserRole + 1).value<QPixmap>();
    QPixmap avatar = raw.size().width() > 48 ? raw.scaled(48, 48, Qt::KeepAspectRatio, Qt::SmoothTransformation) : raw;

    QString title = index.data(Qt::UserRole + 2).toString();
    QString subtitle = index.data(Qt::UserRole + 3).toString();
    QString time = index.data(Qt::UserRole + 4).toString();
    bool showRedDot = index.data(Qt::UserRole + 5).toBool();

    // 画头像（矩形）
    QRect avatarRect(r.left() + 10, r.top() + 6, 48, 48);
    p->drawPixmap(avatarRect, avatar);

    // 画主标题
    // 计算标题区域：头像右边 + 10 像素开始，到右侧时间前
    int titleLeft = avatarRect.right() + 10;
    int titleRight = r.right() - 70;  // 留出空间给右上角时间
    QRect titleRect(titleLeft, r.top(), titleRight - titleLeft, r.height());

    // 设置字体和颜色
    p->setPen(Qt::black);
    QFont f = p->font();
    f.setPointSize(13);
    p->setFont(f);

    // 绘制标题
    p->drawText(titleRect, Qt::AlignVCenter | Qt::AlignLeft, title);

    // 画右上角时间
    p->setPen(Qt::gray);
    p->drawText(QRect(r.right() - 60, r.top() + 8, 50, 20), Qt::AlignRight, time);

    // // 红点提示（左上角）
    // if (showRedDot) {
    //     p->setBrush(Qt::red);
    //     p->setPen(Qt::NoPen);
    //     p->drawEllipse(QPoint(avatarRect.left(), avatarRect.top()), 5, 5);
    // }

    p->restore();
}

QSize MessageItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    bool isGroup = index.data(Qt::UserRole + 99).toBool();
    if (isGroup) {
        return QSize(200, 60);  // 分组项高度小一点
    }
    return QSize(200, 60);      // 消息项高度
}
