#ifndef DB_HANDLER_H
#define DB_HANDLER_H

#include <QString>
#include <QSqlDatabase>

class db_handler
{
public:
    db_handler();
    bool isUserIdExists(const QString& userId);
    bool verifyUserPassword(const QString& userId, const QString& enteredPassword);

    bool isAdminIdExists(const QString& userId);
    bool verifyAdminPassword(const QString& userId, const QString& enteredPassword);
    void addUser(QString,QString);

    //private:
    QSqlDatabase db;
    QString hashPassword(const QString& password);
    //QSqlDatabase getDatabase();

    //~db_handler();
};
#endif // DB_HANDLER_H
