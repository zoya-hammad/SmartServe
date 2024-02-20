#include "admin_login.h"
#include "ui_admin_login.h"
#include "admin_page.h"
#include "globals.h"
#include <QMessageBox>
#include <QDialog>
#include <QVBoxLayout>

admin_login::admin_login(QWidget *parent, db_handler& dbHandler) :
    QDialog(parent),
    ui(new Ui::admin_login),
    dbHandler(dbHandler)
{
    ui->setupUi(this);
}

admin_login::~admin_login()
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

void admin_login::on_loginButton_clicked()
{
    QString userId = ui->id_lineEdit->text();
    QString enteredPassword = ui->password_lineEdit->text();

    if (dbHandler.isAdminIdExists(userId)) {
        if (dbHandler.verifyAdminPassword(userId, enteredPassword)) {
            // password is correct
            CustomMessageBox successMessageBox("Login Successful", "Login successful!", this);
            successMessageBox.exec();

            close();
            admin_page adminPage(this);
            adminPage.exec();
        } else {
            // password is incorrect
            CustomMessageBox errorMessageBox("Incorrect Password", "Incorrect password!", this);
            errorMessageBox.exec();
        }
    } else {
        // id does not exist
        CustomMessageBox errorMessageBox("User Not Found", "User not found in database!", this);
        errorMessageBox.exec();
    }
}



