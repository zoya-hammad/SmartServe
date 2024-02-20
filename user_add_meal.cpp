#include "user_add_meal.h"
#include "ui_user_add_meal.h"
#include "globals.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDate>
#include <QSqlError>
#include <QStandardItemModel>
#include <QDebug>
#include "QrCodeGenerator.h"

user_add_meal::user_add_meal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::user_add_meal)
{

    ui->setupUi(this);
}

user_add_meal::~user_add_meal()
{
    delete ui;
}
void user_add_meal::displayQRCode(const QString& mealName, const QDate& date)
{
    QrCodeGenerator generator;
    QString data = "Meal: " + mealName + "\nDate: " + date.toString("yyyy-MM-dd");
    QImage qrCodeImage = generator.generateQr(data);

    QLabel* qrCodeLabel = new QLabel(this);
    qrCodeLabel->setPixmap(QPixmap::fromImage(qrCodeImage));
    qrCodeLabel->setScaledContents(true);  // to fix dimensions
    qrCodeLabel->setFixedSize(150, 150);

    qrCodeLabel->show();
}

void user_add_meal::setupModel()
{
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


void user_add_meal::on_addMealPlan_clicked()
{
    QString mealId = ui->m_id->text();

    if (mealId.isEmpty()) {
        QMessageBox::critical(this, "Error", "Please enter a valid meal ID.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT meal_type,name FROM menu WHERE menu_id = :mealId");
    query.bindValue(":mealId", mealId);

    if (!query.exec() || !query.next()) {
        QMessageBox::critical(this, "Error", "Failed to fetch meal type from the menu.");
        return;
    }

    QString mealType = query.value(0).toString();
    QString mealName = query.value(1).toString();

    QSqlQuery query2;
    query2.prepare("SELECT " + mealType + " FROM active_meal_plans WHERE user_id = :id");
    query2.bindValue(":id", currentUserID);

    if (!query2.exec()) {
        QMessageBox::critical(this, "Error", "Failed to fetch available slots for meal type.");
        return;
    }

    if (query2.next()) {
        int availableSlots = query2.value(0).toInt();

        if (availableSlots > 0) {
            QSqlQuery query3;
            query3.prepare("UPDATE active_meal_plans SET " + mealType + " = :currentValue WHERE user_id = :id");
            query3.bindValue(":currentValue", availableSlots - 1);
            query3.bindValue(":id", currentUserID);

            if (!query3.exec()) {
                QMessageBox::critical(this, "Error", "Failed to update meal type values.");
            }
            else {
                QSqlQuery query4;
                query4.prepare("INSERT INTO meal_plan_info (meal_plan_id, date, user_id, meal_type, name) VALUES (:meal_plan_id, :date, :userId, :mealType, :name)");
                query4.bindValue(":meal_plan_id", mealId);
                query4.bindValue(":date", QDate::currentDate());
                query4.bindValue(":userId", currentUserID);
                query4.bindValue(":mealType", mealType);
                query4.bindValue(":name", mealName);

                if (!query4.exec()) {
                    QMessageBox::critical(this, "Error", "Failed to insert meal information into meal_plan_info table.");
                }
                else {
                    QMessageBox::information(this, "Success", "Meal Deducted from meal plan and recorded successfully.");
                    displayQRCode(mealName, QDate::currentDate());
                }

            }
        }
        else
            QMessageBox::warning(this, "Warning", "No available slots for the selected meal type.");
    }
}

void user_add_meal::on_menu_clicked()
{
    setupModel();
}


void user_add_meal::on_addCard_clicked()
{
    QString mealId = ui->m_id->text();

    if (mealId.isEmpty()) {
        QMessageBox::critical(this, "Error", "Please enter a valid meal ID.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT meal_type, name, price FROM menu WHERE menu_id = :mealId");
    query.bindValue(":mealId", mealId);

    if (!query.exec() || !query.next()) {
        QMessageBox::critical(this, "Error", "Failed to fetch meal information from the menu.");
        return;
    }

    QString type = query.value(0).toString();
    QString name = query.value(1).toString();
    int price = query.value(2).toInt();

    QSqlQuery query2;
    query2.prepare("SELECT mess_points FROM active_mess_cards WHERE user_id = :id");
    query2.bindValue(":id", currentUserID);

    if (!query2.exec() || !query2.next()) {
        QMessageBox::critical(this, "Error", "User does not have an active mess card.");
        return;
    }

    int balance = query2.value(0).toInt();

    if (balance >= price) {
        balance -= price;

        QSqlQuery query3;
        query3.prepare("UPDATE active_mess_cards SET mess_points = :newBalance WHERE user_id = :id");
        query3.bindValue(":newBalance", balance);
        query3.bindValue(":id", currentUserID);

        if (!query3.exec()) {
            QMessageBox::critical(this, "Error", "Failed to update mess card balance.");
            return;
        }

        QSqlQuery query4;
        query4.prepare("INSERT INTO mess_card_info (date, user_id, mealtype, name, menu_id) VALUES (:date, :userId, :mealType, :name, :menuId)");
        query4.bindValue(":date", QDate::currentDate());
        query4.bindValue(":userId", currentUserID);
        query4.bindValue(":mealType", type);
        query4.bindValue(":name", name);
        query4.bindValue(":menuId", mealId);

        if (!query4.exec()) {
            QMessageBox::critical(this, "Error", "Failed to insert information into mess_card_info table.");
            return;
        }
        else{
            displayQRCode(name, QDate::currentDate());
            QMessageBox::information(this, "Success", "Meal purchased using mess card. New balance: " + QString::number(balance));}
    }
    else
        QMessageBox::warning(this, "Warning", "Insufficient balance in mess card. Available balance: " + QString::number(balance));
}


#include "user_page.h"
void user_add_meal::on_backButton_clicked()
{
    user_page uPage(this);
    this->hide();
    uPage.show();
}

