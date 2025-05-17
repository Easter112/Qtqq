#ifndef MESSAGEITEMDELEGATE_H
#define MESSAGEITEMDELEGATE_H
#include <QStyledItemDelegate>
#include <QPainter>

class MessageItemDelegate : public QStyledItemDelegate {
public:
    explicit MessageItemDelegate(QObject *parent = nullptr)
        : QStyledItemDelegate(parent) {}

    void paint(QPainter *p, const QStyleOptionViewItem &opt, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // MESSAGEITEMDELEGATE_H
