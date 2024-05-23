#include <QApplication>
#include <QWidget>
#include "login.h"
#include "register.h"
#include "ProjectScoreManage.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);


  /*  LoginWindow window;
    window.show();*/


  ///*  RegisterWindow window;
  //  window.show();*/

    ProjectScoreManage window;
    window.show();


    return a.exec();
}
