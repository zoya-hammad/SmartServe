#ifndef USER_ADD_MEAL_H
#define USER_ADD_MEAL_H

#include <QDialog>

namespace Ui {
class user_add_meal;
}

class user_add_meal : public QDialog
{
    Q_OBJECT

public:
    explicit user_add_meal(QWidget *parent = nullptr);
    ~user_add_meal();

private slots:


    void on_addMealPlan_clicked();
    void setupModel();

    void on_menu_clicked();

    void on_addCard_clicked();
    void displayQRCode(const QString& mealName, const QDate& date);

    void on_backButton_clicked();

private:
    Ui::user_add_meal *ui;
};

#endif // USER_ADD_MEAL_H
