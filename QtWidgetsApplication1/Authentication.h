#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <QMainWindow>
#include "ui_QtWidgetsApplication1.h" // ������ȷ���ļ���
#include "ui_mainwindow.h"

namespace Ui {
    class MainWindow; // ��������������������Ϊ MainWindow
}

class Authentication : public QMainWindow
{
    Q_OBJECT

public:
    explicit Authentication(QWidget* parent = nullptr);
    ~Authentication();

private:
    Ui::MainWindow* ui; // ȷ�������Ա��������
};

#endif // AUTHENTICATION_H
