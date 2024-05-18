#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_loginUser.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void login();

private:
    Ui::MainWindow* ui;
    QString username;
    QString password;

    QString performLogin(const QString& username, const QString& password);
};

#endif // MAINWINDOW_H

