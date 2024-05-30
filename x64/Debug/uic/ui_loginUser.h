/********************************************************************************
** Form generated from reading UI file 'loginUser.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINUSER_H
#define UI_LOGINUSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QPushButton *pushButtonChangePassword;
    QPushButton *pushButtonRegister;
    QLineEdit *lineEditPassword;
    QLabel *label_2;
    QLabel *label;
    QPushButton *pushButtonLogin;
    QLabel *login_success;
    QLineEdit *lineEditUsername;
    QLabel *login_failure;

    void setupUi(QWidget *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName("LoginWindow");
        LoginWindow->resize(723, 562);
        pushButtonChangePassword = new QPushButton(LoginWindow);
        pushButtonChangePassword->setObjectName("pushButtonChangePassword");
        pushButtonChangePassword->setGeometry(QRect(410, 310, 75, 24));
        QFont font;
        font.setPointSize(12);
        pushButtonChangePassword->setFont(font);
        pushButtonRegister = new QPushButton(LoginWindow);
        pushButtonRegister->setObjectName("pushButtonRegister");
        pushButtonRegister->setGeometry(QRect(120, 310, 75, 24));
        pushButtonRegister->setFont(font);
        lineEditPassword = new QLineEdit(LoginWindow);
        lineEditPassword->setObjectName("lineEditPassword");
        lineEditPassword->setGeometry(QRect(210, 210, 291, 31));
        lineEditPassword->setEchoMode(QLineEdit::Password);
        label_2 = new QLabel(LoginWindow);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(110, 210, 71, 31));
        QFont font1;
        font1.setPointSize(20);
        label_2->setFont(font1);
        label = new QLabel(LoginWindow);
        label->setObjectName("label");
        label->setGeometry(QRect(110, 150, 101, 41));
        label->setFont(font1);
        pushButtonLogin = new QPushButton(LoginWindow);
        pushButtonLogin->setObjectName("pushButtonLogin");
        pushButtonLogin->setGeometry(QRect(250, 270, 75, 24));
        pushButtonLogin->setFont(font);
        login_success = new QLabel(LoginWindow);
        login_success->setObjectName("login_success");
        login_success->setGeometry(QRect(230, 340, 471, 31));
        login_success->setFont(font1);
        lineEditUsername = new QLineEdit(LoginWindow);
        lineEditUsername->setObjectName("lineEditUsername");
        lineEditUsername->setGeometry(QRect(210, 160, 291, 31));
        login_failure = new QLabel(LoginWindow);
        login_failure->setObjectName("login_failure");
        login_failure->setGeometry(QRect(60, 340, 551, 31));
        login_failure->setFont(font1);

        retranslateUi(LoginWindow);
        QObject::connect(pushButtonRegister, SIGNAL(clicked()), LoginWindow, SLOT(on_pushButtonRegister_clicked()));
        QObject::connect(pushButtonChangePassword, SIGNAL(clicked()), LoginWindow, SLOT(on_pushButtonChangePassword_clicked()));

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QWidget *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "Form", nullptr));
        pushButtonChangePassword->setText(QCoreApplication::translate("LoginWindow", "\344\277\256\346\224\271\345\257\206\347\240\201", nullptr));
        pushButtonRegister->setText(QCoreApplication::translate("LoginWindow", "\346\263\250\345\206\214", nullptr));
        lineEditPassword->setPlaceholderText(QCoreApplication::translate("LoginWindow", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", nullptr));
        label_2->setText(QCoreApplication::translate("LoginWindow", "\345\257\206\347\240\201\357\274\232", nullptr));
        label->setText(QCoreApplication::translate("LoginWindow", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        pushButtonLogin->setText(QCoreApplication::translate("LoginWindow", "\347\231\273\345\275\225", nullptr));
        login_success->setText(QCoreApplication::translate("LoginWindow", "\347\231\273\345\275\225\346\210\220\345\212\237\357\274\201", nullptr));
        lineEditUsername->setPlaceholderText(QCoreApplication::translate("LoginWindow", "\350\257\267\350\276\223\345\205\245\347\224\250\346\210\267\345\220\215", nullptr));
        login_failure->setText(QCoreApplication::translate("LoginWindow", "\347\231\273\345\275\225\345\244\261\350\264\245\357\274\201\350\257\245\347\224\250\346\210\267\345\220\215\344\270\215\345\255\230\345\234\250\346\210\226\350\276\223\345\205\245\345\257\206\347\240\201\351\224\231\350\257\257\357\274\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINUSER_H
