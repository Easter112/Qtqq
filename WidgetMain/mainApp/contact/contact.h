#ifndef CONTACT_H
#define CONTACT_H

#include <QWidget>

class Contact : public QWidget
{
    Q_OBJECT

public:
    explicit Contact(QWidget *parent = nullptr);
    ~Contact(){}
    void loadStyleSheet(const QString &sheetName);

};
#endif // CONTACT_H
