#ifndef ADMIN_ADD_POINTS_H
#define ADMIN_ADD_POINTS_H

#include <QDialog>

namespace Ui {
class admin_add_points;
}

class admin_add_points : public QDialog
{
    Q_OBJECT

public:
    explicit admin_add_points(QWidget *parent = nullptr);
    ~admin_add_points();

private slots:
    void on_updateUserData_clicked();

    void on_backButton_clicked();

private:
    Ui::admin_add_points *ui;
};

#endif // ADMIN_ADD_POINTS_H
