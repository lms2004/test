#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtWidgetsApplication1 w;
    w.show();
    return a.exec();
}
//#include "Authentication.h"
//#include <QtWidgets/QApplication>
//
//
//MainWindow::MainWindow(QWidget* parent)
//    : QMainWindow(parent)
//    , ui(new Ui::MainWindow)
//{
//    ui->setupUi(this);
//
//    // ����UIԪ��
//    QLabel* usernameLabel = new QLabel(this);
//    usernameLabel->setText("�û���");
//    usernameLabel->setGeometry(10, 10, 60, 30);
//
//    QLineEdit* usernameLineEdit = new QLineEdit(this);
//    usernameLineEdit->setGeometry(80, 10, 200, 30);
//
//    QLabel* passwordLabel = new QLabel(this);
//    passwordLabel->setText("����");
//    passwordLabel->setGeometry(10, 50, 60, 30);
//
//    QLineEdit* passwordLineEdit = new QLineEdit(this);
//    passwordLineEdit->setGeometry(80, 50, 200, 30);
//    passwordLineEdit->setEchoMode(QLineEdit::Password);
//
//    QPushButton* pushButton = new QPushButton(this);
//    pushButton->setText("ע��");
//    pushButton->setGeometry(80, 90, 80, 30);
//    connect(pushButton, &QPushButton::clicked, this, &MainWindow::input);
//
//    QLabel* labelResult = new QLabel(this);
//    labelResult->setGeometry(10, 130, 280, 30);
//}
//
//MainWindow::~MainWindow()
//{
//    delete ui;
//}
//
//void MainWindow::input()
//{
//    QString username = ui->usernameLineEdit->text();
//    QString password = ui->passwordLineEdit->text();
//
//    if (username.isEmpty() || password.isEmpty()) {
//        ui->labelResult->setText("ע��ʧ�ܣ��û��������벻��Ϊ��");
//    }
//    else if (username == "admin") {
//        ui->labelResult->setText("ע��ʧ�ܣ��û����Ѵ���");
//    }
//    else if (password.length() < 6) {
//        ui->labelResult->setText("ע��ʧ�ܣ����볤������Ϊ6���ַ�");
//    }
//    else {
//        // ģ��ע��ɹ�
//        ui->labelResult->setText("ע��ɹ�");
//    }
//}
