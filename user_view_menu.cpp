#include "user_view_menu.h"
#include "ui_user_view_menu.h"
#include "user_page.h"
#include "queue.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>

user_view_menu::user_view_menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::user_view_menu)
{
    ui->setupUi(this);
    loadData();
}

user_view_menu::~user_view_menu()
{
    delete ui;
}

void user_view_menu::loadData(){
    QSqlQuery query("SELECT name, price, meal_type FROM menu");

    if (query.exec()) {
        while (query.next()) {
            QString name = query.value(0).toString();
            int price = query.value(1).toInt();

            if (query.value(2).toString() == "breakfast")
                this->breakfastQueue.enqueue(name.toStdString(), price);
            else if (query.value(2).toString() == "lunch")
                this->lunchQueue.enqueue(name.toStdString(), price);
            else if (query.value(2).toString() == "dinner")
                this->dinnerQueue.enqueue(name.toStdString(), price);
            else if (query.value(2).toString() == "drinks")
                this->drinksQueue.enqueue(name.toStdString(), price);
        }}

    else
        qDebug() << "Error executing query: " << query.lastError().text();

}

void user_view_menu::on_displayMenu_clicked() {
    int lowestPrice = ui->priceSlider->value();

    bool breakfastChecked = ui->breakfastCheckBox->isChecked();
    bool lunchChecked = ui->lunchCheckBox->isChecked();
    bool dinnerChecked = ui->dinnerCheckBox->isChecked();
    bool drinksChecked = ui->drinksCheckBox->isChecked();

    if (ui->priceSlider->value() < lowestPrice) {
        QMessageBox::information(this, "Invalid Price Range", "Please select a higher price range.");
        return;
    }

    int priceLimit = ui->priceSlider->value();

    QString result;
    if (breakfastChecked) {
        result += "Breakfast:\n";

        Node* temp = breakfastQueue.front;
        while (temp) {
            QString mealName =  QString::fromStdString(temp->meal_name);
            int mealPrice = temp->price;
            if (mealPrice <= priceLimit)
                result += mealName + " - Rs." + QString::number(mealPrice) + "\n";
            temp = temp->next;
        }
    }

    if (lunchChecked) {
        result += "Lunch:\n";

        Node* temp = lunchQueue.front;
        while (temp) {
            QString mealName =  QString::fromStdString(temp->meal_name);
            int mealPrice = temp->price;
            if (mealPrice <= priceLimit)
                result += mealName + " - Rs." + QString::number(mealPrice) + "\n";
            temp = temp->next;
        }
    }

    if (dinnerChecked) {
        result += "Dinner:\n";

        Node* temp = dinnerQueue.front;
        while (temp) {
            QString mealName =  QString::fromStdString(temp->meal_name);
            int mealPrice = temp->price;
            if (mealPrice <= priceLimit)
                result += mealName + " - Rs." + QString::number(mealPrice) + "\n";
            temp = temp->next;
        }
    }

    if (drinksChecked) {
        result += "Drinks:\n";

        Node* temp = drinksQueue.front;
        while (temp) {
            QString mealName =  QString::fromStdString(temp->meal_name);
            int mealPrice = temp->price;
            if (mealPrice <= priceLimit)
                result += mealName + " - Rs." + QString::number(mealPrice) + "\n";
            temp = temp->next;
        }
    }

    // display results
    if (result.isEmpty()) {
        QMessageBox::information(this, "No Items Selected", "Please select at least one item.");
    }
    else {
        QMessageBox::information(this, "Menu Results", result);
    }

    qDebug() << "Result: " << result;
}

void user_view_menu::on_priceSlider_sliderReleased()
{
    int currentValue = ui->priceSlider->value();
    ui->priceLabel->setText("Selected Price: Rs." + QString::number(currentValue));
}



#include "user_page.h"
void user_view_menu::on_backButton_clicked()
{
    user_page uPage(this);
    this->hide();
    uPage.show();
}


