#ifndef CONTACT_H
#define CONTACT_H

#include <QWidget>
#include "ui_contact.h"  // 必须包含自动生成的 UI 头文件

class Contact : public QWidget
{
    Q_OBJECT

public:
    explicit Contact(QWidget *parent = nullptr);
    ~Contact(){}
    void loadStyleSheet(const QString &sheetName);
    void changeWidget(int index);
    void initConnect();
    void initContactTreeWidget();
    void initChatListWidget();
    auto addListItem(const QString& iconPath, const QString& text,
                               const QString& time, bool showRedDot);

    bool eventFilter(QObject *object, QEvent *event) override;
    void addTreeItem(
        QTreeWidgetItem* parent,         // 父项（如果是顶层则传nullptr）
        const QString& text,             // 显示文本
        const QString& iconPath = "",    // 图标路径（可选）
        int level = 0,                   // 层级（0=顶层，1=子项）
        const QVariant& data = QVariant() // 自定义数据（可选）
    );

    auto addTreeRootItem(
        const QString& text,
        const QFont& font = QFont("PingFang SC", 14, QFont::Bold)
    );

signals:
    void itemClicked(const QModelIndex &index);

private:
    Ui::Contact *ui;  // 现在 Ui::Contact 是完整类型
};

#endif // CONTACT_H
