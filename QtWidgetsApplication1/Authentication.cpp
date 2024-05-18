// mainwindow.cpp
#include "Authentication.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButtonRegister, &QPushButton::clicked, this, &MainWindow::registerUser);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::registerUser() {
    // 获取用户名和密码输入框中的文本
    username = ui->lineEditUsername->text();
    password = ui->lineEditPassword->text();

    // 这里可以添加进一步的逻辑，比如验证用户名和密码的有效性，然后显示注册结果
    QString registrationResult = performRegistration(username, password);
    ui->labelRegistrationResult->setText(registrationResult);
}

QString MainWindow::performRegistration(const QString& username, const QString& password) {
    // 这里可以编写将用户名和密码存储到数据库或文件的代码
    // 假设这里只是简单返回一个注册成功的消息
    return "注册成功！";
}
