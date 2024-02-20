#ifndef USER_LOGIN_SCREEN_H
#define USER_LOGIN_SCREEN_H

#include <QWidget>

namespace Ui {
class user_login_screen;
}

class user_login_screen : public QWidget
{
    Q_OBJECT

public:
    explicit user_login_screen(QWidget *parent = nullptr);
    ~user_login_screen();

private:
    Ui::user_login_screen *ui;
};

#endif // USER_LOGIN_SCREEN_H
