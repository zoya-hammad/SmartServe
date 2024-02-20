#ifndef USER_VIEW_MENU_H
#define USER_VIEW_MENU_H

#include <QDialog>
#include "queue.h"

namespace Ui {
class user_view_menu;
}

class user_view_menu : public QDialog
{
    Q_OBJECT

public:
    explicit user_view_menu(QWidget *parent = nullptr);
    ~user_view_menu();
    Queue breakfastQueue, lunchQueue, dinnerQueue, drinksQueue;

private slots:
    void on_displayMenu_clicked();

   // void on_priceSlider_actionTriggered(int action);

    void on_priceSlider_sliderReleased();



    void on_backButton_clicked();

private:
    Ui::user_view_menu *ui;
    void loadData();
};

#endif // USER_VIEW_MENU_H
