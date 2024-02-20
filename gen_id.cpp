#include "gen_id.h"
#include "ui_gen_id.h"

#include "chains.h"

#include <QMessageBox>
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>

gen_id::gen_id(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gen_id)
{
    ui->setupUi(this);
}

gen_id::~gen_id()
{
    delete ui;
}

void gen_id::on_genId_clicked()
{
    int u_id = ui->userId->text().toInt();
    int m_id = generate_id();

    while (hashTable.found(m_id))
        m_id = generate_id();


    hashTable.insert(m_id);

    QMessageBox msgBox;

    msgBox.setText("User ID: " + QString::number(u_id) + "\nMeal Plan UUID: " + QString::number(m_id));

    QString styleSheet = "QMessageBox { background-color: black; color: white; }"
                             "QMessageBox QLabel { color: #cccccc; }";
    msgBox.setStyleSheet(styleSheet);
    msgBox.exec();

    //data
    QSqlQuery query;
    query.prepare("INSERT INTO meal_plan (meal_plan_id, date, user_id) VALUES (:meal_plan_id, :date, :user_id)");
    query.bindValue(":meal_plan_id", m_id);
    query.bindValue(":user_id", u_id);

    // current date
    QDate currentDate = QDate::currentDate();
    query.bindValue(":date", currentDate);

    if (query.exec()) {
        // Insertion successful
        qDebug() << "Data inserted into meal_plan table successfully.";
    }
    else {
        // Insertion failed, handle the error
        qDebug() << "Error inserting data into meal_plan table:" << query.lastError().text();
    }
}

#include "admin_page.h"
void gen_id::on_backButton_clicked()
{
    admin_page aPage(this);
    this->hide();
    aPage.show();
}

