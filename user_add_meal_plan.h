#ifndef USER_ADD_MEAL_PLAN_H
#define USER_ADD_MEAL_PLAN_H

#include <QDialog>
#include "db_handler.h"

namespace Ui {
class user_add_meal_plan;
}

class user_add_meal_plan : public QDialog
{
    Q_OBJECT

public:
    explicit user_add_meal_plan(QWidget *parent, db_handler& dbHandler);
    ~user_add_meal_plan();

private slots:
    void on_addMealPlan_clicked();

    void on_backButton_clicked();

private:
    Ui::user_add_meal_plan *ui;
    db_handler& dbHandler;
};

#endif // USER_ADD_MEAL_PLAN_H
