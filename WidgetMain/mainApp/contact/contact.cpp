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
    bool showReadDot = index.data(Qt::UserRole + 5).toBool();

    if(showReadDot)
    {
        QString iconPath = index.data(Qt::UserRole + 1).toString();
        QString text = index.data(Qt::UserRole + 2).toString();
        QString time = index.data(Qt::UserRole + 4).toString();
        qDebug() << iconPath;

        addListItem(iconPath,text,time,false);
    }
    else
        return ;
    });
}

bool Contact::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->chatListWidget->viewport() &&
            event->type() == QEvent::MouseButtonPress) {

            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            QModelIndex index = ui->chatListWidget->indexAt(mouseEvent->pos());

            if (!index.isValid()) return false;  // 点击空白区域不处理

            // 获取点击项的矩形区域（与paint()中一致）
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
        // 设置图标（如果提供了路径）
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
        item->setSizeHint(0,QSize(ui->chatListWidget->width(), itemHeight));
        item->setText(0, text);
        item->setFont(0, font);
        item->setData(0, Qt::UserRole + 1, 0); // 标记为顶层
        ui->contactTreeWidget->addTopLevelItem(item);
        return item;
}


void Contact::initContactTreeWidget()
{

    // 初始化树形列表
    ui->contactTreeWidget->setHeaderHidden(true);
    ui->contactTreeWidget->setIconSize(QSize(40,40));
    auto rootItem = addTreeRootItem("群聊");
    addTreeItem(rootItem,"技术交流群",":/image/logo.png");

    ui->contactTreeWidget->expandAll();

    ui->stackedWidget->setCurrentIndex(0);
}


void Contact::initChatListWidget()
{
    // 设置列表控件属性
    ui->chatListWidget->setViewMode(QListView::ListMode);
    ui->chatListWidget->setIconSize(QSize(50, 50));
    ui->chatListWidget->setWordWrap(true);

    // 设置自定义委托
    MessageItemDelegate* delegate = new MessageItemDelegate(ui->chatListWidget);
    ui->chatListWidget->setItemDelegate(delegate);

    // 布局控制
    ui->chatListWidget->setGridSize(QSize(-1, 60)); // 高度与委托中定义的60一致
    ui->chatListWidget->setUniformItemSizes(true);
    ui->chatListWidget->setResizeMode(QListView::Adjust);

    // 样式表
    ui->chatListWidget->setStyleSheet("QListWidget::item { padding: 8px 0; }");

    // 添加项目
    addListItem(":/image/123.png", "技术交流群", "12:30", true);
    addListItem(":/image/logo.png", "产品讨论群", "10:15", false);
    addListItem(":/image/logo.png", "Admin", "昨天", true);
}

