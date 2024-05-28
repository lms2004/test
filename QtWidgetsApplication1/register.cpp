#include "register.h"

RegisterWindow::RegisterWindow(QWidget* parent) : QWidget(parent), ui(new Ui::RegisterWindow), authService() {
    ui->setupUi(this);
    ui->register_success->hide();
    ui->register_failure->hide();
}

RegisterWindow::~RegisterWindow() {
    delete ui;
}

void RegisterWindow::on_pushButtonRegister_clicked() {
    QString username = ui->lineEditUsername->text();
    QString password = ui->lineEditPassword->text();
    if (authService.registerUser(username.toStdString(), password.toStdString())) {
        ui->register_success->show();
        emit registerSuccessful(); // 发送注册成功信号
    }
    else {
        ui->register_failure->show();
    }
}

