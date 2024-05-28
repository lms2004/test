#include "login.h"

LoginWindow::LoginWindow(QWidget* parent)
    : QWidget(parent), ui(new Ui::LoginWindow), authService() {
    ui->setupUi(this);
    ui->login_success->hide();
    ui->login_failure->hide();

    connect(ui->pushButtonLogin, &QPushButton::clicked, this, &LoginWindow::on_pushButtonLogin_clicked);
    connect(ui->pushButtonChangePassword, &QPushButton::clicked, this, &LoginWindow::on_pushButtonChangePassword_clicked);
    connect(ui->pushButtonRegister, &QPushButton::clicked, this, &LoginWindow::on_pushButtonRegister_clicked);
}

LoginWindow::~LoginWindow() {
    delete ui;
}

void LoginWindow::on_pushButtonLogin_clicked() {
    QString username = ui->lineEditUsername->text();
    QString password = ui->lineEditPassword->text();
    if (authService.login(username.toStdString(), password.toStdString())) {
        ui->login_success->show();
        emit loginSuccessful(); // Emit loginSuccessful signal
    }
    else {
        ui->login_failure->show();
    }
}

void LoginWindow::on_pushButtonChangePassword_clicked() {
    emit changePasswordRequested(); // Emit changePasswordRequested signal
}

void LoginWindow::on_pushButtonRegister_clicked() {
    emit switchToRegister(); // Emit switchToRegister signal
}
