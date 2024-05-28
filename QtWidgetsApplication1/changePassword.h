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

private slots:
    void on_pushButtonChangePassword_clicked();

private:
    Ui::ChangePasswordWindow* ui;
    AuthenticationService authService;
    //std::string username;
};

#endif // CHANGEPASSWORD_H




