
// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_registerUser.h"
#include <QMainWindow>

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
    void registerUser();

private:
    Ui::MainWindow* ui;
    QString username;
    QString password;

    QString performRegistration(const QString& username, const QString& password);
};

#endif // MAINWINDOW_H
