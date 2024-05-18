#include "Authentication.h"
#include "login.h"
#include <QApplication>
#include <mysql.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>

//×¢²á/µÇÂ¼½çÃæ
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

