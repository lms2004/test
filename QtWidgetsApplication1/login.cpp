#include "login.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButtonLogin, &QPushButton::clicked, this, &MainWindow::login);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::login() {
    // ��ȡ�û���������������е��ı�
    username = ui->lineEditUsername->text();
    password = ui->lineEditPassword->text();

    // ���������ӽ�һ�����߼���������֤�û������������Ч�ԣ�Ȼ����ʾ��¼���
    QString loginResult = performLogin(username, password);
    ui->labelLoginResult->setText(loginResult);
}

QString MainWindow::performLogin(const QString& username, const QString& password) {
    // ������Ա�д��֤�û�����������߼�
    // ��������ֻ�Ǽ򵥷���һ����¼�ɹ�����Ϣ
    if (username == "admin" && password == "password") {
        return "��¼�ɹ���";
    }
    else {
        return "�û������������";
    }
}
