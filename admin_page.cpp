#include "admin_page.h"
#include "ui_admin_page.h"
#include "add_user.h"
#include "chains.h"
#include "gen_id.h"
#include "admin_add_points.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include "admin_edit_menu.h"

admin_page::admin_page(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin_page)
{
    ui->setupUi(this);
}

admin_page::~admin_page()
{
    delete ui;
}

void admin_page::on_addUser_clicked()
{
    hide();
    add_user addUser(this,dbHandler);
    addUser.exec();

}

class CustomMessageBox : public QDialog {
public:
    CustomMessageBox(const QString &title, const QString &message, QWidget *parent = nullptr)
        : QDialog(parent)
    {
        setWindowTitle(title);

        QVBoxLayout *layout = new QVBoxLayout(this);
        QLabel *label = new QLabel(message, this);

        layout->addWidget(label);

        setStyleSheet("background-color: white; color: black;");
        setFixedWidth(260);
    }
};


void admin_page::on_addMealPlan_clicked(){

    gen_id generateId(this);
    generateId.exec();

}

void admin_page::on_viewMenu_clicked()
{
    admin_edit_menu editMenu(this,dbHandler);
    editMenu.exec();
}


void admin_page::on_addMessPoints_clicked()
{
    admin_add_points addPoints(this);
    addPoints.exec();
}


void admin_page::on_userData_clicked()
{
    QSqlQuery query1;
    query1.prepare("SELECT COUNT(*) FROM active_meal_plans");

    if (!query1.exec()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve active meal plans count.");
        return;
    }

    query1.next();
    int activeMealPlans = query1.value(0).toInt();

    QSqlQuery query2;
    query2.prepare("SELECT COUNT(*) FROM active_mess_cards");

    if (!query2.exec()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve active mess cards count.");
        return;
    }

    query2.next();
    int activeMessCards = query2.value(0).toInt();

    QSqlQuery query3;
    query3.prepare("SELECT COUNT(*) FROM meal_plan_info");
    if (!query3.exec()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve meals purchased count.");
        return;
    }

    query3.next();
    int mealPlansPurchased =query3.value(0).toInt();

    QSqlQuery query4;
    query4.prepare("SELECT COUNT(*) FROM mess_card_info");
    if (!query4.exec()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve mess card purchases count.");
        return;
    }

    query4.next();
    int messCardsPurchased = query4.value(0).toInt();

    QSqlQuery query5,query6,query7,query8;
    query5.prepare("SELECT COUNT(*) FROM meal_plan_info WHERE meal_type = 'breakfast'");
    if (!query5.exec()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve total breakfast meals purchased.");
        return;
    }
    query5.next();
    int totalBreakfastMeals = query5.value(0).toInt();

    query6.prepare("SELECT COUNT(*) FROM meal_plan_info WHERE meal_type = 'lunch'");
    if (!query6.exec()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve total lunch meals purchased.");
        return;
    }
    query6.next();
    int totalLunchMeals = query6.value(0).toInt();

    query7.prepare("SELECT COUNT(*) FROM meal_plan_info WHERE meal_type = 'dinner'");
    if (!query7.exec()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve total dinner meals purchased.");
        return;
    }
    query7.next();
    int totalDinnerMeals = query7.value(0).toInt();

    query8.prepare("SELECT COUNT(*) FROM meal_plan_info WHERE meal_type = 'drinks'");
    if (!query8.exec()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve total drink meals purchased.");
        return;
    }
    query8.next();
    int totalDrinkMeals = query8.value(0).toInt();

    QSqlQuery query9,query10,query11,query12;
    query9.prepare("SELECT name, COUNT(*) FROM meal_plan_info WHERE meal_type = 'breakfast' GROUP BY meal_type ORDER BY COUNT(*) DESC LIMIT 1");
    if (!query9.exec()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve most popular breakfast meal.");
        return;
    }
    query9.next();
    QString mostPopularBreakfast = query9.value(0).toString();

    query10.prepare("SELECT name, COUNT(*) FROM meal_plan_info WHERE meal_type = 'lunch' GROUP BY meal_type ORDER BY COUNT(*) DESC LIMIT 1");
    if (!query10.exec()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve most popular lunch meal.");
        return;
    }
    query10.next();
    QString mostPopularLunch = query10.value(0).toString();

    query11.prepare("SELECT name, COUNT(*) FROM meal_plan_info WHERE meal_type = 'dinner' GROUP BY meal_type ORDER BY COUNT(*) DESC LIMIT 1");
    if (!query11.exec()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve most popular dinner meal.");
        return;
    }
    query11.next();
    QString mostPopularDinner = query11.value(0).toString();

    query12.prepare("SELECT name, COUNT(*) FROM meal_plan_info WHERE meal_type = 'drinks' GROUP BY meal_type ORDER BY COUNT(*) DESC LIMIT 1");
    if (!query12.exec()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve most popular drink meal.");
        return;
    }
    query12.next();
    QString mostPopularDrink = query12.value(0).toString();


    QString message = "Active Meal Plans: " + QString::number(activeMealPlans) + "\n";
    message += "Active Mess Cards: " + QString::number(activeMessCards) + "\n";
    message += "Total Meal Plans Purchased: " + QString::number(mealPlansPurchased) + "\n";
    message += "Total Mess Cards Purchased: " + QString::number(messCardsPurchased) + "\n";
    message += "Total Breakfast Meals Purchased: " + QString::number(totalBreakfastMeals) + "\n";
    message += "Total Lunch Meals Purchased: " + QString::number(totalLunchMeals) + "\n";
    message += "Total Dinner Meals Purchased: " + QString::number(totalDinnerMeals) + "\n";
    message += "Total Drink Meals Purchased: " + QString::number(totalDrinkMeals) + "\n";
    message += "Most Popular Breakfast Meal: " + mostPopularBreakfast + "\n";
    message += "Most Popular Lunch Meal: " + mostPopularLunch + "\n";
    message += "Most Popular Dinner Meal: " + mostPopularDinner + "\n";
    message += "Most Popular Drink Meal: " + mostPopularDrink;

    CustomMessageBox customMessageBox("User Data Statistics", message, this);
    customMessageBox.exec();
}

