#ifndef ADD_USER_H
#define ADD_USER_H

#include <QDialog>
#include <cstring>
#include "db_handler.h"


using namespace std;

namespace Ui {
class add_user;
}

class add_user : public QDialog
{
    Q_OBJECT
    int random_num, random_index, random_ascii;
    int pass_iter = 8;
    string user_pass = "";
    char symbols[20] = {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '+', '{', '}', '/', '[', ']', '?', '<', '>'};

public:
    //explicit add_user(QWidget *parent = nullptr, db_handler& dbHandler = db_handler());
    explicit add_user(QWidget *parent, db_handler& dbHandler);
    //db_handler& getDbHandler();
    //PageHistory pageHistory;
    ~add_user();

private slots:
    void on_generatePassword_clicked();
    void on_addUserDB_clicked();
    bool isNumeric(QString);

    void on_backButton_clicked();

private:
    Ui::add_user *ui;
    db_handler& dbHandler;
    //const db_handler& dbHandler;
   // db_handler &dbHandler;


};

#endif // ADD_USER_H
