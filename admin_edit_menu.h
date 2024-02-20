#ifndef ADMIN_EDIT_MENU_H
#define ADMIN_EDIT_MENU_H

#include <QDialog>
#include "db_handler.h"
#include <QSqlTableModel>

namespace Ui {
class admin_edit_menu;
}

class admin_edit_menu : public QDialog
{
    Q_OBJECT

public:
    explicit admin_edit_menu(QWidget *parent, db_handler& dbHandler);
    ~admin_edit_menu();

private slots:
    void on_loadTable_clicked();
    void on_deleteItem_clicked();
    void on_updatePrice_clicked();

    void on_addItem_clicked();

    void on_backButton_clicked();

private:
    Ui::admin_edit_menu *ui;
    db_handler& dbHandler;
    void setupModel();
    QSqlTableModel *menuModel;
};

#endif // ADMIN_EDIT_MENU_H
