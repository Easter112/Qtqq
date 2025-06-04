// TreeItemDelegate.h
#include <QApplication>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QStyleOptionViewItem>

class CustomTreeDelegate : public QStyledItemDelegate
{
public:
    explicit CustomTreeDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

};
