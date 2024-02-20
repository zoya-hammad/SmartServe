#include "user_login_screen.h"
#include "ui_user_login_screen.h"

user_login_screen::user_login_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::user_login_screen)
{
    ui->setupUi(this);
}

user_login_screen::~user_login_screen()
{
    delete ui;
}
