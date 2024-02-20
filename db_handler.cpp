#include "db_handler.h"
#include <QSqlQuery>
#include <QCryptographicHash>
#include <QSqlError>
#include <QMessageBox>


db_handler::db_handler()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/92310/Downloads/cafe.db");

    if (!db.open()) {
        qDebug() << "Error opening the database:" << db.lastError().text();
    }
}

bool db_handler::isUserIdExists(const QString& userId)
{
    db_handler();
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM user_info WHERE id = :userId");
    query.bindValue(":userId", userId);

    if (query.exec()) {
        query.next();
        int count = query.value(0).toInt();
        return (count > 0);
    }

    return false;

}

bool db_handler::isAdminIdExists(const QString& adminId)
{
    db_handler();
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM admin_info WHERE id = :Id");
    query.bindValue(":Id", adminId);

    if (query.exec()) {
        query.next();
        int count = query.value(0).toInt();
        return (count > 0);
    }

    return false;

}

bool db_handler::verifyUserPassword(const QString& userId, const QString& enteredPassword)
{
    QSqlQuery query;
    query.prepare("SELECT password FROM user_info WHERE id = :userId");
    query.bindValue(":userId", userId);

    if (query.exec() && query.next()) {
        QString storedPassword = query.value(0).toString();

        // Hash the entered password using SHA-256
        QString enteredPasswordHash = hashPassword(enteredPassword);

        // Compare the hashed entered password with the stored password
        return (storedPassword == enteredPasswordHash);
    } else {
        qDebug() << "Error executing query or no records found.";
    }

    return false;
}

bool db_handler::verifyAdminPassword(const QString& adminId, const QString& enteredPassword)
{
    QSqlQuery query;
    query.prepare("SELECT password FROM admin_info WHERE id = :Id");
    query.bindValue(":Id", adminId);

    if (query.exec() && query.next()) {
        QString storedPassword = query.value(0).toString();

        // Hash the entered password using SHA-256
        QString enteredPasswordHash = hashPassword(enteredPassword);

        // Compare the hashed entered password with the stored password
        return (storedPassword == enteredPasswordHash);
    } else {
        qDebug() << "Error executing query or no records found.";
    }

    return false;
}

QString db_handler::hashPassword(const QString& password)
{
    QCryptographicHash hash(QCryptographicHash::Sha256);
    hash.addData(password.toUtf8());
    return QString(hash.result().toHex());
}

void db_handler::addUser(QString id,QString password){
    QSqlQuery query;

    query.prepare("INSERT INTO user_info (id, password) VALUES (:id, :password)");
    query.bindValue(":id", id);
    query.bindValue(":password", password);

    if (query.exec())
        QMessageBox::information(nullptr, "Success", "User added successfully!");
    else
        QMessageBox::critical(nullptr, "Error", "Failed to add user to the database: " + query.lastError().text());
}


