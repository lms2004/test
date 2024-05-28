#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "ui_loginUser.h"
#include "authenticationservice.h"

class LoginWindow : public QWidget {
    Q_OBJECT
public:
    LoginWindow(QWidget* parent = nullptr);
    ~LoginWindow();

signals:
    void loginSuccessful();

private slots:
    void on_pushButtonLogin_clicked();

private:
    Ui::LoginWindow* ui;
    AuthenticationService authService;
};

#endif // LOGIN_H
