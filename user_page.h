#ifndef USER_PAGE_H
#define USER_PAGE_H

#include <QDialog>
#include "db_handler.h"

namespace Ui {
class user_page;
}

class user_page : public QDialog
{
    Q_OBJECT

public:
    explicit user_page(QWidget *parent = nullptr);
    ~user_page();

private slots:
    void on_viewMenu_clicked();
    void on_addMealPlan_clicked();
    void on_addMeal_clicked();
    void on_viewHistory_clicked();


private:
    Ui::user_page *ui;
    db_handler dbHandler;
};

#endif // USER_PAGE_H
