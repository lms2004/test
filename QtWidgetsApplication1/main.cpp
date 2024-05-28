#include <QApplication>
#include <QWidget>
#include "login.h"
#include "register.h"
#include "ProjectScoreManage.h"
#include "uploader.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    LoginWindow window1;
    RegisterWindow window2;
    uploader window3;

    QObject::connect(&window1, &LoginWindow::loginSuccessful, [&]() {
        window1.close();
        window2.show();
        });

    QObject::connect(&window2, &RegisterWindow::registerSuccessful, [&]() {
        window2.close();
        window3.show();
        });

    window2.show();

    return a.exec();
}