#include "add_user.h"
#include "ui_add_user.h"

#include "user_page.h"
#include <cstdlib>
#include <ctime>
#include <cstring>

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QCryptographicHash>
#include <QMainWindow>


add_user::add_user(QWidget *parent, db_handler& dbHandler) :
    QDialog(parent),
    ui(new Ui::add_user),
    dbHandler(dbHandler)
{
    ui->setupUi(this);
}

add_user::~add_user()
{
    delete ui;
}

// Function used to generate a password, adds ascii values, numbers and symbols based on modular arithmetics
void add_user::on_generatePassword_clicked()
{
    srand(time(NULL));
    user_pass.clear();

    for (int i=0;i<pass_iter;i++){

        if (i%3==0){
        random_num = rand() % 10 + 1;
        random_index = rand() % 20 + 1;
        random_ascii = rand() % (90-65+1) + 65;

        user_pass += char(random_ascii);
        user_pass += symbols[random_index];

        }
        else if (i%3==1){
        random_num = rand() % 10 + 1;
        random_index = rand() % 20 + 1;
        random_ascii = rand() % (122-97+1) + 97;

        user_pass += char(random_ascii);
        user_pass += symbols[random_index];

        }
        else{
        random_num = rand() % 100 + 1;
        }

        user_pass += to_string(random_num);
    }

    ui->password->setText("Password is: " + QString::fromStdString(user_pass));

}


void add_user::on_addUserDB_clicked()
{

    QString userId = ui->id_lineEdit->text().trimmed();
    QString password = QString::fromStdString(user_pass);

    if (userId.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Empty Fields", "Please enter both ID and Password.");
        return;
    }

    if (!isNumeric(userId)) {
        QMessageBox::warning(this, "ID Non Numeric", "Please enter numeric ID.");
        return;
    }

    QString passHash = dbHandler.hashPassword(password);
    dbHandler.addUser(userId,passHash);
}

bool add_user::isNumeric(QString str) {
    int unicode;
    for (int i = 0; i < str.length(); i++) {
        unicode = str[i].unicode();
        if (unicode < 48 || unicode > 57)
            return false;
    }
    return true;
}



#include "admin_page.h"
void add_user::on_backButton_clicked()
{
    admin_page aPage(this);
    this->hide();
    aPage.show();
}
