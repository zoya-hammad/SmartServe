#ifndef ADMIN_PAGE_H
#define ADMIN_PAGE_H

#include <QDialog>
#include "db_handler.h"
#include "chains.h"

namespace Ui {
class admin_page;
}

class admin_page : public QDialog
{
    Q_OBJECT

public:
    explicit admin_page(QWidget *parent = nullptr);
    //explicit admin_page(QWidget *parent = nullptr, db_handler& dbHandler);
    //explicit admin_page(QWidget *parent = nullptr);
    ~admin_page();

private slots:
    void on_addUser_clicked();

    void on_addMealPlan_clicked();

    void on_viewMenu_clicked();

    void on_addMessPoints_clicked();

    void on_userData_clicked();

private:
    Ui::admin_page *ui;
    db_handler dbHandler;   //new addition
    HashTable hashTable;
};

#endif // ADMIN_PAGE_H
