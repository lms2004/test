#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <QMainWindow>
#include "ui_QtWidgetsApplication1.h" // 包含正确的文件名
#include "ui_mainwindow.h"

namespace Ui {
    class MainWindow; // 这里假设你的主窗口类名为 MainWindow
}

class Authentication : public QMainWindow
{
    Q_OBJECT

public:
    explicit Authentication(QWidget* parent = nullptr);
    ~Authentication();

private:
    Ui::MainWindow* ui; // 确保这个成员变量存在
};

#endif // AUTHENTICATION_H
