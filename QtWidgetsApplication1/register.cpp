#include "register.h"

RegisterWindow::RegisterWindow(QWidget* parent) : QWidget(parent), ui(new Ui::RegisterWindow) {
    ui->setupUi(this);
    connect(ui->pushButtonRegister, &QPushButton::clicked, this, &RegisterWindow::on_pushButtonRegister_clicked);
}

RegisterWindow::~RegisterWindow() {
    delete ui;
}

void RegisterWindow::on_pushButtonRegister_clicked() {
    username = ui->lineEditUsername->text();
    password = ui->lineEditPassword->text();
    QString registrationResult = performRegistration(username, password);
    ui->labelRegistrationResult->setText(registrationResult);
}

QString RegisterWindow::performRegistration(const QString& username, const QString& password) {
    AuthenticationService authService;
    if (authService.registerUser(username.toStdString(), password.toStdString())) {
        return "注册成功！";
    }
    else {
        return "注册失败，用户名可能已存在。";
    }
}
