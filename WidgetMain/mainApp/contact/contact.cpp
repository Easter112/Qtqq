#include "contact.h"
#include <QFileDialog>
#include <QIODevice>
#include <QDebug>
#include <QTreeWidget>
#include <QListView>
#include <QStandardItem>
#include "WidgetMain/utils/messageitemdelegate.h"

Contact::Contact(QWidget *parent) :
    QWidget(parent)
{
    QTreeView *treeView = new QTreeView(this);
    treeView->resize(312,809);

    treeView->setHeaderHidden(true);     // 不显示表头
    treeView->setIndentation(10);        // 控制缩进

    QStandardItemModel *model = new QStandardItemModel(this);
    treeView->setModel(model);
    // 分组项（不可点击）
    QStandardItem *groupItem = new QStandardItem("群聊");
    groupItem->setEditable(false);
    QFont font = groupItem->font();
    font.setBold(true);
    groupItem->setFont(font);
    groupItem->setData(true, Qt::UserRole + 99);

    // 创建一个“联系人”分组（顶层项）
    QStandardItem *contactGroupItem = new QStandardItem("联系人");
    contactGroupItem->setEditable(false);
    QFont contactFont = contactGroupItem->font();
    contactFont.setBold(true);
    contactGroupItem->setFont(contactFont);
    contactGroupItem->setData(true, Qt::UserRole + 99);  // 标记为分组

    // 添加联系人项到该分组
    QStandardItem *contactItem = new QStandardItem();
    contactItem->setEditable(false);
    contactItem->setData(QPixmap(":/image/logo.png"), Qt::UserRole + 1);  // 头像
    contactItem->setData("张三", Qt::UserRole + 2);                           // 主标题
    // contactItem->setData("最近很忙", Qt::UserRole + 3);                       // 副标题
    // contactItem->setData("15:20", Qt::UserRole + 4);                          // 时间
    // contactItem->setData(true, Qt::UserRole + 5);                             // 红点

    contactGroupItem->appendRow(contactItem);

    // 添加到模型（和群聊同级）
    model->appendRow(contactGroupItem);
    treeView->expand(contactGroupItem->index());  // 默认展开

    // QDate today = QDate::currentDate();
    // QLocale locale(QLocale::Chinese);
    // QString weekDayStr = locale.dayName(today.dayOfWeek());  // 输出：星期一、星期二 等

    QStandardItem *item = new QStandardItem();
    item->setData(QPixmap(":/image/123.png"), Qt::UserRole + 1);       // 头像
    item->setData("admin", Qt::UserRole + 2);            // 标题
    // item->setData("", Qt::UserRole + 3);        // 副标题
    // item->setData("", Qt::UserRole + 4);                          // 时间
    item->setData(true, Qt::UserRole + 5);                              // 红点
    groupItem->appendRow(item);
    item->setEditable(false);

    model->appendRow(groupItem);
    treeView->expand(groupItem->index());  // 默认展开
    treeView->setItemDelegate(new MessageItemDelegate(treeView));
    loadStyleSheet("contact");

}

void Contact::loadStyleSheet(const QString &sheetName)
{
    QFile file(":/css/" + sheetName + ".css");

    if (file.open(QFile::ReadOnly))
    {
        QString qssStyleSheet = file.readAll();
        this->setStyleSheet(qssStyleSheet);
        file.close();
    }
    else
    {
        qWarning() << "Failed to open stylesheet:" << file.fileName();
    }
}

