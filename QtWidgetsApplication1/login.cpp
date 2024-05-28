#include "login.h"

LoginWindow::LoginWindow(QWidget* parent)
    : QWidget(parent), ui(new Ui::LoginWindow), authService() {
    ui->setupUi(this);
    ui->login_success->hide();
    ui->login_failure->hide();
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
