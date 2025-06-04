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


    //模拟点击条目的样式表  如果重写了paint()方法且没有调用基类实现，就会丢失样式表效果
    QColor backgroundColor = opt.state & QStyle::State_Selected ?
        QColor("#F0F0F0") :
        (opt.state & QStyle::State_MouseOver ? QColor("#F0F0F0") : Qt::white);

    p->fillRect(opt.rect, backgroundColor);
    // 获取数据
    QPixmap raw = index.data(Qt::UserRole + 1).value<QPixmap>();
    QPixmap avatar = raw.size().width() > 50 ? raw.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation) : raw;

    QString title = index.data(Qt::UserRole + 2).toString();            //主标题
    QString subtitle = index.data(Qt::UserRole + 3).toString();         //副标题
    QString time = index.data(Qt::UserRole + 4).toString();             //时间
    bool showRedDot = index.data(Qt::UserRole + 5).toBool();            //未读事件提示

    // 画头像（矩形）
    QRect headRect(r.left() + 10, r.top() + 16, 50, 50);
    p->drawPixmap(headRect, avatar);


    // 计算用户名区域：头像右边 + 10 像素开始，到右侧时间前
    int titleLeft = headRect.right() + 10;
    int titleRight = r.right() - 70;  // 留出空间给右上角时间
    QRect titleRect(titleLeft, r.top() + 10, titleRight - titleLeft, r.height()/2);

    //计算最新消息位置 头像右边 + 10 像素开始，到右侧时间前 在tittleRect下5px
    QRect newMsgRect(titleLeft,r.height()/2 - 5,titleRight - titleLeft,r.height()/2);

    // 设置字体和颜色
    p->setPen(Qt::black);
    QFont f = p->font();
    f.setPointSize(12);
    p->setFont(f);

    // 绘制标题
    p->drawText(titleRect, Qt::AlignVCenter | Qt::AlignLeft, title);

    p->setPen(Qt::gray);
    QFont subTitleFont = p->font();
    subTitleFont.setPointSize(10);
    p->setFont(subTitleFont);
    //绘制最新一条消息
    p->drawText(newMsgRect, Qt::AlignVCenter | Qt::AlignLeft, subtitle);

    // 画右上角时间
    QFont timeFont = p->font();
    timeFont.setPointSize(8);
    p->setFont(timeFont);
    p->drawText(QRect(r.right() - 60, r.top() + 13, 50, 30), Qt::AlignRight, time);

     // 红点提示（左上角）
     if (showRedDot) {
         p->setBrush(Qt::red);
         p->setPen(Qt::NoPen);
         p->drawEllipse(QPoint(headRect.left(), headRect.top()), 5, 5);
     }



    p->restore();
}

QSize MessageItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRect r = option.rect;
    bool isGroup = index.data(Qt::UserRole + 99).toBool();
    if (isGroup) {
        return QSize(r.right() - r.left(), 80);  // 分组项高度小一点
    }
    return QSize(r.right() - r.left(), 80);      // 消息项高度
}
