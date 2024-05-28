#ifndef REGISTER_H
#define REGISTER_H
#include <QWidget>
#include "ui_registerUser.h"
#include "authenticationservice.h"

class RegisterWindow : public QWidget {
    Q_OBJECT
public:
    RegisterWindow(QWidget* parent = nullptr);
    ~RegisterWindow();

signals:
    void registerSuccessful();
    void ToLogin();

private slots:
    void on_pushButtonRegister_clicked();

private:
    Ui::RegisterWindow* ui;
    AuthenticationService authService;
};
#endif // REGISTER_H
