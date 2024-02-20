#ifndef USER_LOGIN_H
#define USER_LOGIN_H

#include <QDialog>
#include "db_handler.h"

namespace Ui {
class user_login;
}

class user_login : public QDialog
{
    Q_OBJECT

public:
    explicit user_login(QWidget *parent, db_handler& dbHandler);
    ~user_login();

private slots:
    void on_loginButton_clicked();

private:
    Ui::user_login *ui;
    db_handler& dbHandler;  // Store a reference to the dbHandler
};
#endif // USER_LOGIN_H
