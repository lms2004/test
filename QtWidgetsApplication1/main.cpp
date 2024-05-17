#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtWidgetsApplication1 w;
    w.show();
    return a.exec();
}
//#include "Authentication.h"
//#include <QtWidgets/QApplication>
//
//
//MainWindow::MainWindow(QWidget* parent)
//    : QMainWindow(parent)
//    , ui(new Ui::MainWindow)
//{
//    ui->setupUi(this);
//
//    // 设置UI元素
//    QLabel* usernameLabel = new QLabel(this);
//    usernameLabel->setText("用户名");
//    usernameLabel->setGeometry(10, 10, 60, 30);
//
//    QLineEdit* usernameLineEdit = new QLineEdit(this);
//    usernameLineEdit->setGeometry(80, 10, 200, 30);
//
//    QLabel* passwordLabel = new QLabel(this);
//    passwordLabel->setText("密码");
//    passwordLabel->setGeometry(10, 50, 60, 30);
//
//    QLineEdit* passwordLineEdit = new QLineEdit(this);
//    passwordLineEdit->setGeometry(80, 50, 200, 30);
//    passwordLineEdit->setEchoMode(QLineEdit::Password);
//
//    QPushButton* pushButton = new QPushButton(this);
//    pushButton->setText("注册");
//    pushButton->setGeometry(80, 90, 80, 30);
//    connect(pushButton, &QPushButton::clicked, this, &MainWindow::input);
//
//    QLabel* labelResult = new QLabel(this);
//    labelResult->setGeometry(10, 130, 280, 30);
//}
//
//MainWindow::~MainWindow()
//{
//    delete ui;
//}
//
//void MainWindow::input()
//{
//    QString username = ui->usernameLineEdit->text();
//    QString password = ui->passwordLineEdit->text();
//
//    if (username.isEmpty() || password.isEmpty()) {
//        ui->labelResult->setText("注册失败，用户名或密码不能为空");
//    }
//    else if (username == "admin") {
//        ui->labelResult->setText("注册失败，用户名已存在");
//    }
//    else if (password.length() < 6) {
//        ui->labelResult->setText("注册失败，密码长度至少为6个字符");
//    }
//    else {
//        // 模拟注册成功
//        ui->labelResult->setText("注册成功");
//    }
//}
