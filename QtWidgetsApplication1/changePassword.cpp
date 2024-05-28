#include "changePassword.h"

ChangePasswordWindow::ChangePasswordWindow(QWidget* parent) : QWidget(parent), ui(new Ui::ChangePasswordWindow), authService() {
    ui->setupUi(this);
    ui->changePassword_success->hide();
    ui->changePassword_failure->hide();
}

ChangePasswordWindow::~ChangePasswordWindow() {
    delete ui;
}

void ChangePasswordWindow::on_pushButtonChangePassword_clicked() {
    QString usernameText = ui->lineEditUsername->text();
    QString oldPasswordText = ui->lineEditOldPassword->text();
    QString newPasswordText = ui->lineEditNewPassword->text();
    if (authService.changePassword(usernameText.toStdString(), oldPasswordText.toStdString(), newPasswordText.toStdString())) {
        ui->changePassword_success->show();
    }
    else {
        ui->changePassword_failure->show();
    }
}
