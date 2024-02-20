QT       += core gui sql
include (C:\Users\92310\Downloads\SQLiteStudio)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
include(C:\Users\92310\Desktop\qt course\qrcode\lib\Qt-QrCodeGenerator-main\Qt-QrCodeGenerator.pri)

SOURCES += \
    add_user.cpp \
    admin_add_points.cpp \
    admin_edit_menu.cpp \
    admin_login.cpp \
    admin_page.cpp \
    chains.cpp \
    db_handler.cpp \
    gen_id.cpp \
    globals.cpp \
    main.cpp \
    mainwindow.cpp \
    node.cpp \
    queue.cpp \
    stack.cpp \
    user_add_meal.cpp \
    user_add_meal_plan.cpp \
    user_login.cpp \
    user_page.cpp \
    user_view_menu.cpp

HEADERS += \
    add_user.h \
    admin_add_points.h \
    admin_edit_menu.h \
    admin_login.h \
    admin_page.h \
    chains.h \
    db_handler.h \
    gen_id.h \
    globals.h \
    mainwindow.h \
    node.h \
    queue.h \
    stack.h \
    user_add_meal.h \
    user_add_meal_plan.h \
    user_login.h \
    user_page.h \
    user_view_menu.h

FORMS += \
    add_user.ui \
    admin_add_points.ui \
    admin_edit_menu.ui \
    admin_login.ui \
    admin_page.ui \
    gen_id.ui \
    mainwindow.ui \
    user_add_meal.ui \
    user_add_meal_plan.ui \
    user_login.ui \
    user_page.ui \
    user_view_menu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc
