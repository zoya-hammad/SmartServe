#include "user_add_meal_plan.h"
#include "ui_user_add_meal_plan.h"
#include "globals.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

user_add_meal_plan::user_add_meal_plan(QWidget *parent, db_handler &dbHandler) :
    QDialog(parent),
    ui(new Ui::user_add_meal_plan),
    dbHandler(dbHandler)
{
    ui->setupUi(this);
}

user_add_meal_plan::~user_add_meal_plan()
{
    delete ui;
}

void user_add_meal_plan::on_addMealPlan_clicked()
{
    QString mp_id = ui->mp_id->text();

    if ( mp_id.isEmpty()) {
        QMessageBox::critical(this, "Error", "Meal Plan ID cannot be empty.");
        return;
    }
    // user id check
    QSqlQuery query;
    query.prepare("SELECT id FROM user_info WHERE id = :u_id");
    query.bindValue(":u_id", currentUserID);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", "Error executing user query: " + query.lastError().text());
        return;
    }

    if (!query.next()) {
        QMessageBox::critical(this, "Error", "User ID does not exist.");
        return;
    }

    // if user id exists
    // Step 2: Check if the meal plan ID corresponds to the provided user ID in the meal_plan table
    QSqlQuery query2;
    query2.prepare("SELECT user_id FROM meal_plan WHERE meal_plan_id = :mp_id AND user_id = :u_id");
    query2.bindValue(":mp_id", mp_id);
    query2.bindValue(":u_id", currentUserID);

    if (!query2.exec()) {
        QMessageBox::critical(this, "Database Error", "Error executing meal plan query: " + query2.lastError().text());
        return;
    }

    if (query2.next()) {
        // Meal plan ID is associated with the provided user ID
        // Check if the user ID exists in the meal_plan_info table
        QSqlQuery query3;
        query3.prepare("SELECT user_id FROM active_meal_plans WHERE user_id = :u_id");
        query3.bindValue(":u_id", currentUserID);

        if (!query3.exec()) {
            QMessageBox::critical(this, "1Database Error", "Error executing select query: " + query3.lastError().text());
            return;
        }

        QSqlQuery query4;
        if (query4.next()) {
            // User ID exists in meal_plan_info, increment integer columns by 20

            query4.prepare("UPDATE active_meal_plans SET breakfast = breakfast + 20, "
                                "lunch = lunch + 20, dinner = dinner + 20, drinks = drinks + 20 "
                                "WHERE user_id = :u_id");
        } else {
            // User ID does not exist in meal_plan_info, set integer columns to 20

            query4.prepare("INSERT OR REPLACE INTO active_meal_plans (user_id, breakfast, lunch, dinner, drinks) "
                                "VALUES (:u_id, 20, 20, 20, 20)");
        }

        query4.bindValue(":u_id", currentUserID);

        if (!query4.exec()) {
            QMessageBox::critical(this, "2Database Error", "Error executing update query: " + query4.lastError().text());
            return;
        }

        // action performed
        QMessageBox::information(this, "Success", "Meal Plan ID is associated with the user ID. User added to active meal plans.");

        QSqlQuery query5;
        query5.prepare("DELETE FROM meal_plan WHERE meal_plan_id = :mp_id AND user_id = :u_id");
        query5.bindValue(":mp_id", mp_id);
       query5.bindValue(":u_id", currentUserID);

        if (query5.exec()) {
            QMessageBox::critical(this, "Database Error", "Error executing delete query: " +query5.lastError().text());
            return;
        }
    }
    else
        QMessageBox::warning(this, "Warning", "Meal Plan ID is not associated with the user ID. No changes made to active meal plans.");
    }

#include "user_page.h"
void user_add_meal_plan::on_backButton_clicked()
{
    user_page uPage(this);
    this->hide();
    uPage.show();
}

