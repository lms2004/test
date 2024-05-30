#include <QApplication>
#include <QWidget>
#include "login.h"
#include "register.h"
#include "ProjectScoreManage.h"
#include "uploader.h"
#include"changePassword.h"


int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    LoginWindow loginWindow;
    RegisterWindow registerWindow;
    ChangePasswordWindow changePasswordWindow;
    ProjectScoreManage projectScoreManageWindow;
    uploader uploaderWindow;

    // 连接信号和槽，处理窗口之间的切换
    QObject::connect(&loginWindow, &LoginWindow::loginSuccessful, [&]() {
        loginWindow.close();
        projectScoreManageWindow.show();
        });

    QObject::connect(&loginWindow, &LoginWindow::changePasswordRequested, [&]() {
        loginWindow.close();
        changePasswordWindow.show();
        });

    QObject::connect(&loginWindow, &LoginWindow::switchToRegister, [&]() {
        loginWindow.close();
        registerWindow.show();
        });

    QObject::connect(&registerWindow, &RegisterWindow::registerSuccessful, [&]() {
        registerWindow.close();
        loginWindow.show();
        });

    QObject::connect(&registerWindow, &RegisterWindow::switchToLogin, [&]() {
        registerWindow.close();
        loginWindow.show();
        });

    QObject::connect(&changePasswordWindow, &ChangePasswordWindow::passwordChanged, [&]() {
        changePasswordWindow.close();
        loginWindow.show();
        });

    QObject::connect(&changePasswordWindow, &ChangePasswordWindow::backToLogin, [&]() {
        changePasswordWindow.close();
        loginWindow.show();
        });

    QObject::connect(&projectScoreManageWindow, &ProjectScoreManage::doneManaging, [&]() {
        projectScoreManageWindow.close();
        uploaderWindow.show();
        });

    uploaderWindow.show();

    return a.exec();
}