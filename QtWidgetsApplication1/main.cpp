#include <QApplication>
#include <QWidget>
#include "login.h"
#include "register.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);


    LoginWindow window;
    window.show();


   /* RegisterWindow window;
    window.show();*/


    return a.exec();
}
