#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "user_login.h"
#include "admin_login.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

db_handler& MainWindow::getDbHandler()
{
    return dbHandler;
}

void MainWindow::on_userButton_clicked()
{
    user_login *loginForm = new user_login(this, dbHandler);
    loginForm->show();

}


void MainWindow::on_adminButton_clicked()
{
    admin_login *adminLogin = new admin_login(this,dbHandler);
    adminLogin->show();
}

