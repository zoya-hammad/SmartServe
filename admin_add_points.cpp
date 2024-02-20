#include "admin_add_points.h"
#include "ui_admin_add_points.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

admin_add_points::admin_add_points(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin_add_points)
{
    ui->setupUi(this);
}

admin_add_points::~admin_add_points()
{
    delete ui;
}

void admin_add_points::on_updateUserData_clicked()
{
    QString id = ui->id->text();
    QString points = ui->points->text();

    QSqlQuery query;
    query.prepare("SELECT * FROM active_mess_cards WHERE user_id = :userId");
    query.bindValue(":userId", id);

    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        return;
    }

    if (query.next()) {
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE active_mess_cards SET mess_points = mess_points + :points WHERE user_id = :userId");
        updateQuery.bindValue(":points", points);
        updateQuery.bindValue(":userId", id);

        if (!updateQuery.exec()) {
            qDebug() << "Failed to execute update query:" << updateQuery.lastError().text();
            return;
        }
    }

    else {
        QSqlQuery query2;
        query2.prepare("INSERT INTO active_mess_cards (user_id, mess_points) VALUES (:userId, :messPoints)");
        query2.bindValue(":userId", id);
        query2.bindValue(":messPoints", points);

        if (!query2.exec()) {
            qDebug() << "Failed to execute insert query:" << query2.lastError().text();
            return;
        }
    }

    QMessageBox::information(this, "Update User Data", "User data updated successfully.");
}


#include "admin_page.h"
void admin_add_points::on_backButton_clicked()
{
    admin_page aPage(this);
    this->hide();
    aPage.show();
}
