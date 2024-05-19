#include "QtWidgetsApplication1.h"
#include "authenticationservice.h"
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    /*QtWidgetsApplication1 w;
    w.show();*/

    AuthenticationService authService;

    return a.exec();
}