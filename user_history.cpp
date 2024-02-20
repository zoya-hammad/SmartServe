#include "user_history.h"
#include "ui_user_history.h"

user_history::user_history(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::user_history)
{
    ui->setupUi(this);
}

user_history::~user_history()
{
    delete ui;
}

