#ifndef CHANGEPASSWORD_H
#define CHANGEPASSWORD_H

#include <QWidget>
#include "ui_changePassword.h"
#include "authenticationservice.h"

class ChangePasswordWindow : public QWidget {
    Q_OBJECT
public:
    ChangePasswordWindow(QWidget* parent = nullptr);
    ~ChangePasswordWindow();

signals:
    void passwordChanged();
    void backToLogin();

private slots:
    void on_pushButtonChangePassword_clicked();

private:
    Ui::ChangePasswordWindow* ui;
    AuthenticationService authService;
};

#endif // CHANGEPASSWORD_H
