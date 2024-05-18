#include "mainwindow.h"
#include "authenticationservice.h"
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    AuthenticationService authService;

    return a.exec();
}