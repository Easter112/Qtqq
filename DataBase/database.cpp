#include "DataBase/database.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QApplication>

#define DataBaseName "qq.db"

DataBase::DataBase()
{
}

bool DataBase::ConnectToDataBase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");  // SQLite 驱动
    db.setDatabaseName(DataBaseName);  // 数据库文件名

    if (!db.open()) {
        qDebug() << "数据库连接失败:" << db.lastError().text();
        return false;
    }

    qDebug() << "数据库连接成功";
    //if(tableIsEmpty())
    return true;
}

void DataBase::initDataBase()
{
    ConnectToDataBase();
    QString sql = "CREATE table users ";
    QSqlQuery query;

    bool success = query.exec(
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY,"
        "name TEXT NOT NULL,"
        "password TEXT NOT NULL,"
        "status INTEGER DEFAULT 1 CHECK(status IN (1, 2, 3)))"  // ✅ 加上结尾的右括号
        );

    if (!success) {
        qDebug() << "创建 users 表失败:" << query.lastError().text();
    } else {
        qDebug() << "users 表创建成功或已存在";
    }


    if(tableIsEmpty())
    {
        //qDebug() << "i am come";
        // 插入用户，使用 prepare 和 bindValue 防注入
        query.prepare("INSERT INTO users (id, name, password, status) "
                      "VALUES (:id, :name, :password, :status)");

        query.bindValue(":id", 1001);
        query.bindValue(":name", "admin");
        query.bindValue(":password", "root");
        query.bindValue(":status", 1);

        if (!query.exec())
        {
            qDebug() << "Insert failed:" << query.lastError().text();
        }
        else
        {
            qDebug() << "User inserted successfully.";
        }
    }


}

bool DataBase::tableIsEmpty()
{
    QSqlQuery query;

    // 使用 prepare 语句防止 SQL 注入
    query.prepare("SELECT COUNT(*) FROM users");

    if (!query.exec())
    {
        qDebug() << "SQL 执行失败：" << query.lastError().text();
        return true;  // 如果执行失败，默认返回表为空
    }

    if (query.next())
    {
        int count = query.value(0).toInt();
        if (count == 0)
        {
            qDebug() << "users 表是空的。";
            return true;
        }
        else
        {
            qDebug() << "users 表中有数据：" << count << "条。";
            return false;
        }
    }
    else
    {
        qDebug() << "查询没有返回数据。";
        return true;  // 如果查询没有返回数据，也返回表为空
    }
}

int DataBase::IdReturn(const QString &name)
{
    QSqlQuery query;
    query.prepare("SELECT id FROM users WHERE name = :name");
    query.bindValue(":name", name);
    int id;

    if (query.exec())
    {
        if (query.next())
        {
            id = query.value(0).toInt();
            return id;
        }
        else
        {
            qDebug() << "未找到该账号";
            return -1;
        }
    }
    else
    {
        qDebug() << "查询失败:" << query.lastError().text();
        return -1;

    }
}

bool DataBase::QueryData(int id,QString *password)
{
    QSqlQuery query;
    query.prepare("SELECT password FROM users WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec())
    {
        if (query.next())
        {
            *password = query.value(0).toString();
            return true;
        }
        else
        {
            qDebug() << "未找到该账号";
            return false;
        }
    }
    else
    {
        qDebug() << "查询失败:" << query.lastError().text();
        return false;
    }

}

bool DataBase::InsertData(const QString &name, const QString &password)
{
    QSqlQuery query;
    query.prepare("INSERT INTO users (name, password) VALUES (:name, :password)");
    query.bindValue(":name", name);
    query.bindValue(":password", password);

    if (query.exec()) {
        qDebug() << "插入成功";
        return true;
    } else {
        qDebug() << "插入失败:" << query.lastError().text();
        return false;
    }
}

bool DataBase::NameIsSame(const QString &name) {
    // 假设你已经正确设置并打开了默认数据库连接
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query;

    query.prepare("SELECT COUNT(*) FROM users WHERE name = :name");
    query.bindValue(":name", name);

    if (!query.exec()) {
        qDebug() << "Query execution failed:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        int count = query.value(0).toInt();
        return count > 0;  // 如果存在该名称，返回 true
    }

    return false;
}


