#include "login.h"

LoginWindow::LoginWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::LoginWindow) {
    ui->setupUi(this);
    connect(ui->pushButtonLogin, &QPushButton::clicked, this, &LoginWindow::on_pushButtonLogin_clicked);
}

LoginWindow::~LoginWindow() {
    delete ui;
}

void LoginWindow::on_pushButtonLogin_clicked() {
    username = ui->lineEditUsername->text();
    password = ui->lineEditPassword->text();
    QString loginResult = performLogin(username, password);
    ui->labelLoginResult->setText(loginResult);
}

QString LoginWindow::performLogin(const QString& username, const QString& password) {
    AuthenticationService authService;
    if (authService.login(username.toStdString(), password.toStdString())) {
        return "��¼�ɹ���";
    }
    else {
        return "�û������������";
    }
}

