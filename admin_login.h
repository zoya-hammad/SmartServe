#ifndef ADMIN_LOGIN_H
#define ADMIN_LOGIN_H

#include <QDialog>
#include "db_handler.h"

namespace Ui {
class admin_login;
}

class admin_login : public QDialog
{
    Q_OBJECT

public:
    explicit admin_login(QWidget *parent, db_handler& dbHandler);
    ~admin_login();

private slots:
    void on_loginButton_clicked();

private:
    Ui::admin_login *ui;
    db_handler& dbHandler;
};

#endif // ADMIN_LOGIN_H
