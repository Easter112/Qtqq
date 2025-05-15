#ifndef DATABASE_H
#define DATABASE_H
#include <QString>


class DataBase
{
public:
    static DataBase& getInstance()
    {
        static DataBase instance;  // 局部静态变量，线程安全（C++11）
        return instance;
    }

    bool ConnectToDataBase();
    void initDataBase();
    bool tableIsEmpty();
    int IdReturn(const QString &name);
    bool QueryData(int id,QString *password = nullptr);
    bool InsertData(const QString &name, const QString &password);
    bool NameIsSame(const QString &name);

private:
    DataBase();  // 构造函数设为私有
    DataBase(const DataBase&) = delete;
    DataBase& operator=(const DataBase&) = delete;
};
#endif // DATABASE_H
