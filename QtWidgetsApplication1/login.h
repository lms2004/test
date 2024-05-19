#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "ui_loginUser.h"
#include "authenticationservice.h"

class LoginWindow : public QWidget {
    Q_OBJECT
public:
    LoginWindow(QWidget* parent = nullptr);
    ~LoginWindow();

private slots:
    void on_pushButtonLogin_clicked();

private:
    Ui::LoginWindow* ui;
    QString username;
    QString password;
    QString performLogin(const QString& username, const QString& password);
};

#endif // LOGIN_H

