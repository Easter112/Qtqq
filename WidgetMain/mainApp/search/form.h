#ifndef FORM_H
#define FORM_H

#include <QWidget>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    void loadStyleSheet(const QString &sheetName);
    ~Form();

private:
    Ui::Form *ui;
};

#endif // FORM_H
