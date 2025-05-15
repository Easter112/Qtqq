#ifndef UTILS_H
#define UTILS_H
#include <QColor>


class Utils
{
public:
    static Utils &getInstance()
    {
        static Utils instance;
        return instance;
    }

    void setDefaultColor(const QColor &color);
    QColor getDefaultColor();


private:
    Utils() {}  // 构造函数私有化
    Utils(const Utils &) = delete;             // 禁止拷贝构造
    Utils &operator=(const Utils &) = delete;  // 禁止赋值
};


#endif // UTILS_H
