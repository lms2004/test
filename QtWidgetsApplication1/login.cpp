#include "login.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButtonLogin, &QPushButton::clicked, this, &MainWindow::login);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::login() {
    // 获取用户名和密码输入框中的文本
    username = ui->lineEditUsername->text();
    password = ui->lineEditPassword->text();

    // 这里可以添加进一步的逻辑，比如验证用户名和密码的有效性，然后显示登录结果
    QString loginResult = performLogin(username, password);
    ui->labelLoginResult->setText(loginResult);
}

QString MainWindow::performLogin(const QString& username, const QString& password) {
    // 这里可以编写验证用户名和密码的逻辑
    // 假设这里只是简单返回一个登录成功的消息
    if (username == "admin" && password == "password") {
        return "登录成功！";
    }
    else {
        return "用户名或密码错误！";
    }
}
