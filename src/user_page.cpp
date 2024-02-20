#include "user_page.h"
#include "ui_user_page.h"
#include "user_view_menu.h"
#include "user_add_meal_plan.h"
#include "user_add_meal.h"
#include "mainwindow.h"
#include "globals.h"
#include "stack.h"
#include <string>

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>

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
    }
};

user_page::user_page(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::user_page)
{
    ui->setupUi(this);
}

user_page::~user_page()
{
    delete ui;
}

void user_page::on_viewMenu_clicked()
{
    user_view_menu menuPage(this);
    menuPage.exec();
}


void user_page::on_addMealPlan_clicked()
{
    user_add_meal_plan mealPlan(this,dbHandler);
    mealPlan.exec();
}


void user_page::on_addMeal_clicked()
{
    user_add_meal addMeal(this);
    addMeal.exec();
}


void user_page::on_viewHistory_clicked()
{
    QSqlQuery mp_query, mc_query;
    mp_query.prepare("SELECT name, date FROM meal_plan_info WHERE user_id = :userId ORDER BY date");
    mp_query.bindValue(":userId", currentUserID);

    if (!mp_query.exec()) {
        qDebug() << "Failed to fetch user history:" << mp_query.lastError().text();
        return;
    }

    mc_query.prepare("SELECT name, date FROM mess_card_info WHERE user_id = :userId ORDER BY date");
    mc_query.bindValue(":userId", currentUserID);

    if (!mc_query.exec()) {
        qDebug() << "Failed to fetch user history:" << mc_query.lastError().text();
        return;
    }

    Stack mystack;
    QString message;

    while (mp_query.next()) {
        QString mName = mp_query.value(0).toString();
        QString date = mp_query.value(1).toString();

        std::string mNameStr = mName.toStdString();
        std::string dateStr = date.toStdString();

        mystack.push(mNameStr, dateStr);
    }

    while (mc_query.next()) {
        QString mName = mc_query.value(0).toString();
        QString date = mc_query.value(1).toString();

        std::string mNameStr = mName.toStdString();
        std::string dateStr = date.toStdString();

        mystack.push(mNameStr, dateStr);
    }

    message += QString("%1 %2\n").arg("Meal Name", -26).arg("Date", -10, QChar(' '));
    message += "-------------------------------------\n";

    while (!mystack.isEmpty()) {
        QString mealName = QString::fromStdString(mystack.getMeal());
        QString date = QString::fromStdString(mystack.getDate());

        mystack.pop();
        message += QString("%1 %2\n").arg(mealName, -26).arg(date, -10, QChar(' '));
    }

    CustomMessageBox customMessageBox("User History", message, this);
    customMessageBox.exec();
}





