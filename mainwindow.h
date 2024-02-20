#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "db_handler.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    db_handler& getDbHandler();

private slots:
    void on_userButton_clicked();

    void on_adminButton_clicked();

private:
    Ui::MainWindow *ui;
    db_handler dbHandler;
};
#endif // MAINWINDOW_H
