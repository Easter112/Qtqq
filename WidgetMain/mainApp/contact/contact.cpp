#include "contact.h"
#include <QFileDialog>
#include <QIODevice>
#include <QDebug>
#include <QTreeWidget>
#include <QListView>
#include <QStandardItem>
#include <QMouseEvent>
#include <QDebug>
#include "ui_contact.h"
#include "WidgetMain/utils/messageitemdelegate.h"
#include "WidgetMain/utils/CustomTreeDelegate.h"
static const int itemHeight = 80;

Contact::Contact(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Contact)
{
        ui->setupUi(this);
        ui->chatListWidget->viewport()->installEventFilter(this);
        initContactTreeWidget();
        initChatListWidget();
        initConnect();

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

void Contact::changeWidget(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}



auto Contact::addListItem(const QString& iconPath, const QString& text,
                        const QString& time, bool showRedDot)
{
    QListWidgetItem* item = new QListWidgetItem();
    item->setSizeHint(QSize(ui->chatListWidget->width(), 80)); // 高度与委托一致

    // 设置数据（与MessageItemDelegate中定义的角色对应）
    item->setData(Qt::UserRole + 1, QVariant::fromValue(QPixmap(iconPath))); // 头像
    item->setData(Qt::UserRole + 2, text); // 标题
    item->setData(Qt::UserRole + 3, "hello"); // 副标题（可选）
    item->setData(Qt::UserRole + 4, time); // 时间
    item->setData(Qt::UserRole + 5, showRedDot); // 红点提示
    item->setData(Qt::UserRole + 99, false); // 不是分组项

    ui->chatListWidget->addItem(item);
    return item;
}

void Contact::initConnect()
{
    connect(this,&Contact::itemClicked,this,[=](const QModelIndex &index){
        bool showRedDot = index.data(Qt::UserRole + 5).toBool();
        if (showRedDot)
        {
            // 使用index.row() 获取当前项的指针 QListWidgetItem *item(int row) const
            QListWidgetItem* item = ui->chatListWidget->item(index.row());

            if (item)
            {
                // 将红点状态设置为false
                item->setData(Qt::UserRole + 5, false);
                ui->chatListWidget->update(index);
            }
        }
    });

    connect(ui->contactTreeWidget,&QTreeWidget::itemClicked,this,[=](QTreeWidgetItem *item){
        if(item->data(0,Qt::UserRole + 1).toInt() == 0)   //根据层级关系  0代表根项
        {
            if(!item->isExpanded())
                item->setExpanded(true);
            else
            {
                item->setExpanded(false);
            }
        }
    });
}

bool Contact::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->chatListWidget->viewport() &&
            event->type() == QEvent::MouseButtonPress) {

            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            QModelIndex index = ui->chatListWidget->indexAt(mouseEvent->pos());

            if (!index.isValid()) return false;  // 点击空白区域不处理

            // 获取点击项的矩形区域
            QRect itemRect = ui->chatListWidget->visualRect(index);
            if(itemRect.contains(mouseEvent->pos()))
            {
                emit itemClicked(index);
                return  true;
            }

    }
}

void Contact::addTreeItem(QTreeWidgetItem *parent, const QString &text, const QString &iconPath, int level, const QVariant &data)
{

        QTreeWidgetItem* item = new QTreeWidgetItem(parent);
        item->setText(0, text);
        item->setSizeHint(0,QSize(ui->chatListWidget->width(), itemHeight));
        // 设置图标
        if (!iconPath.isEmpty()) {
            item->setIcon(0, QIcon(iconPath));
        }


        // 层级和数据绑定
        item->setData(0, Qt::UserRole + 1, level);
        if (data.isValid()) {
            item->setData(0, Qt::UserRole + 2, data);
        }

        // 自动添加到树（如果parent为nullptr）
        if (!parent) {
            ui->contactTreeWidget->addTopLevelItem(item);
        }
}

auto Contact::addTreeRootItem(const QString &text, const QFont &font)
{
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setSizeHint(0,QSize(ui->chatListWidget->width(), itemHeight - 30));
        item->setFont(0, font);
        item->setData(0, Qt::UserRole + 1, text); // 标记为顶层
        ui->contactTreeWidget->addTopLevelItem(item);
        return item;
}


void Contact::initContactTreeWidget()
{

    // 初始化树形列表
    ui->contactTreeWidget->setHeaderHidden(true);
    ui->contactTreeWidget->setIconSize(QSize(60,40));
    ui->contactTreeWidget->setItemDelegate(new CustomTreeDelegate(ui->contactTreeWidget));
    auto rootItem = addTreeRootItem("群聊");

    addTreeItem(rootItem,"技术交流群",":/image/logo.png");

    auto contactRootItem = addTreeRootItem("联系人");
    addTreeItem(contactRootItem,"果果",":/image/logo.png");

    ui->contactTreeWidget->setIndentation(0);

    ui->contactTreeWidget->expandAll();

    ui->stackedWidget->setCurrentIndex(0);
}


void Contact::initChatListWidget()
{

    // 设置自定义委托
    MessageItemDelegate* delegate = new MessageItemDelegate(ui->chatListWidget);
    ui->chatListWidget->setItemDelegate(delegate);

    // 样式表
    ui->chatListWidget->setStyleSheet("QListWidget::item { padding: 8px 0; }");

    // 添加项目
    addListItem(":/image/123.png", "技术交流群", "12:30", true);
    addListItem(":/image/logo.png", "产品讨论群", "10:15", false);
    addListItem(":/image/logo.png", "Admin", "昨天", true);
}

