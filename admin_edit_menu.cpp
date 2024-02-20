#include "admin_edit_menu.h"
#include "ui_admin_edit_menu.h"
#include <QStandardItemModel>
#include <QMessageBox>

#include <QSql>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

admin_edit_menu::admin_edit_menu(QWidget *parent, db_handler &dbHandler) :
    QDialog(parent),
    ui(new Ui::admin_edit_menu),
    dbHandler(dbHandler)
{
    ui->setupUi(this);

}

admin_edit_menu::~admin_edit_menu()
{
    delete ui;
}

void admin_edit_menu::setupModel()
{
    if (!dbHandler.db.open()) {
        qDebug() << "Error opening menu database:" << dbHandler.db.lastError().text();
        return;
    }

    QSqlQuery query;

    if (!query.exec("SELECT * FROM menu")) {
        qDebug() << "Error executing query:";
        return;
    }

    QStandardItemModel *model = new QStandardItemModel;

    model->setHorizontalHeaderLabels({"Menu ID", "Meal Type", "Name", "Price"});
    ui->tableView->setModel(model);

    while (query.next()) {
        QList<QStandardItem*> row;

        QString menuId = query.value("menu_id").toString();
        QString mealType = query.value("meal_type").toString();
        QString name = query.value("name").toString();
        QString price = query.value("price").toString();

        row.append(new QStandardItem(menuId));
        row.append(new QStandardItem(mealType));
        row.append(new QStandardItem(name));
        row.append(new QStandardItem(price));

        model->appendRow(row);
    }

    ui->tableView->resizeColumnsToContents();
}


void admin_edit_menu::on_loadTable_clicked()
{
    setupModel();
}


void admin_edit_menu::on_deleteItem_clicked()
{
    QString id = ui->id->text();

    if (id.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter an Item ID.");
        return;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM MENU WHERE menu_id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error executing delete query:" << query.lastError().text();
        return;
    }

    if (query.numRowsAffected() > 0)
        QMessageBox::information(this, "Success", "Item deleted successfully.");
    else
        QMessageBox::warning(this, "Warning", "Item with the specified ID not found.");

}


void admin_edit_menu::on_updatePrice_clicked()
{
    QString id = ui->id->text();
    QString updatedPrice = ui->price->text();

    if (id.isEmpty() || updatedPrice.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter both Item ID and Price.");
        return;
    }

    QSqlQuery query2;
    query2.prepare("SELECT * FROM menu WHERE menu_id = :id");
    query2.bindValue(":id", id);

    if (!query2.exec()) {
        qDebug() << "Error executing select query:" << query2.lastError().text();
        return;
    }

    if (!query2.next()) {
        QMessageBox::warning(this, "Warning", "Item with the specified ID not found.");
        return;
    }

    // Update the price in the database
    QSqlQuery query3;
    query3.prepare("UPDATE menu SET price = :updatedPrice WHERE menu_id = :id");
    query3.bindValue(":updatedPrice", updatedPrice);
    query3.bindValue(":id", id);

    if (!query3.exec()) {
        qDebug() << "Error executing update query:" << query3.lastError().text();
        return;
    }

    QMessageBox::information(this, "Success", "Price updated successfully.");

}

void admin_edit_menu::on_addItem_clicked()
{
    QString id = ui->id->text();
    QString name = ui->name->text();
    QString price = ui->price->text();
    QString mealType = ui->mealType->text();

    if (id.isEmpty() || name.isEmpty() || price.isEmpty() || mealType.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter all item details.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM menu WHERE menu_id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error executing select query:" << query.lastError().text();
        return;
    }

    if (query.next()) {
        QMessageBox::warning(this, "Warning", "Item with the specified ID already exists.");
        return;
    }

    // inserting new items
    QSqlQuery query2;
    query2.prepare("INSERT INTO menu (menu_id, name, price, meal_type) VALUES (:id, :name, :price, :mealType)");
    query2.bindValue(":id", id);
    query2.bindValue(":name", name);
    query2.bindValue(":price", price);
    query2.bindValue(":mealType", mealType);

    if (!query2.exec()) {
        qDebug() << "Error executing insert query:" << query2.lastError().text();
        return;
    }

    QMessageBox::information(this, "Success", "Item added successfully.");
}


#include "admin_page.h"
void admin_edit_menu::on_backButton_clicked()
{
    admin_page aPage(this);
    this->hide();
    aPage.show();
}

