#include "user_login.h"
#include "ui_user_login.h"
#include "user_page.h"
#include "globals.h"

#include <QMessageBox>
#include <QDebug>
#include <QVBoxLayout>
#include <QDialog>

user_login::user_login(QWidget *parent, db_handler& dbHandler)
    : QDialog(parent), ui(new Ui::user_login), dbHandler(dbHandler)
{
    ui->setupUi(this);
}

user_login::~user_login()
{
    delete ui;
}

class CustomMessageBox : public QDialog {
public:
    CustomMessageBox(const QString &title, const QString &message, QWidget *parent = nullptr)
        : QDialog(parent)
    {
        setWindowTitle(title);

        QVBoxLayout *layout = new QVBoxLayout(this);
        QLabel *label = new QLabel(message, this);

        layout->addWidget(label);

        setStyleSheet("background-color: white; color: black;");;
    }
};

void user_login::on_loginButton_clicked()
{
    QString userId = ui->id_lineEdit->text();
    QString enteredPassword = ui->password_lineEdit->text();

    if (dbHandler.isUserIdExists(userId)) {
        if (dbHandler.verifyUserPassword(userId, enteredPassword)) {
            currentUserID = userId;

            CustomMessageBox successMessageBox("Login Successful", "Login successful!", this);
            successMessageBox.exec();

            close();
            user_page userPage(this);
            userPage.exec();
        } else {
            CustomMessageBox errorMessageBox("Incorrect Password", "Incorrect password!", this);
            errorMessageBox.exec();
        }
    } else {
        CustomMessageBox errorMessageBox("User Not Found", "User not found in database!", this);
        errorMessageBox.exec();
    }
}


