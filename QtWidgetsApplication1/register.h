#ifndef REGISTER_H
#define REGISTER_H

#include <QMainWindow>
#include "ui_registerUser.h"
#include "authenticationservice.h"

class RegisterWindow : public QMainWindow {
    Q_OBJECT
public:
    RegisterWindow(QWidget* parent = nullptr);
    ~RegisterWindow();

private slots:
    void on_pushButtonRegister_clicked();

private:
    Ui::RegisterWindow* ui;
    QString username;
    QString password;
    QString performRegistration(const QString& username, const QString& password);
};

#endif // REGISTER_H
