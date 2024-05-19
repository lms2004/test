#include <QApplication>
#include <QWidget>
#include "AuthenticationService.h"
#include "login.h"


int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    LoginWindow window;
    window.show();

    return a.exec();
}
