/********************************************************************************
** Form generated from reading UI file 'registerUser.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERUSER_H
#define UI_REGISTERUSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegisterWindow
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *register_failure;
    QLabel *register_success;
    QPushButton *pushButtonRegister;
    QPushButton *pushButton;
    QLineEdit *lineEditPassword;
    QLineEdit *lineEditUsername;

    void setupUi(QWidget *RegisterWindow)
    {
        if (RegisterWindow->objectName().isEmpty())
            RegisterWindow->setObjectName("RegisterWindow");
        RegisterWindow->resize(738, 645);
        label = new QLabel(RegisterWindow);
        label->setObjectName("label");
        label->setGeometry(QRect(130, 140, 101, 61));
        QFont font;
        font.setPointSize(20);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8(""));
        label_2 = new QLabel(RegisterWindow);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(160, 180, 81, 91));
        label_2->setFont(font);
        register_failure = new QLabel(RegisterWindow);
        register_failure->setObjectName("register_failure");
        register_failure->setGeometry(QRect(170, 370, 351, 31));
        register_failure->setFont(font);
        register_success = new QLabel(RegisterWindow);
        register_success->setObjectName("register_success");
        register_success->setGeometry(QRect(280, 370, 221, 31));
        register_success->setFont(font);
        pushButtonRegister = new QPushButton(RegisterWindow);
        pushButtonRegister->setObjectName("pushButtonRegister");
        pushButtonRegister->setGeometry(QRect(300, 290, 81, 31));
        QFont font1;
        font1.setPointSize(12);
        pushButtonRegister->setFont(font1);
        pushButton = new QPushButton(RegisterWindow);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(150, 290, 91, 31));
        lineEditPassword = new QLineEdit(RegisterWindow);
        lineEditPassword->setObjectName("lineEditPassword");
        lineEditPassword->setGeometry(QRect(240, 210, 291, 31));
        lineEditPassword->setEchoMode(QLineEdit::Password);
        lineEditUsername = new QLineEdit(RegisterWindow);
        lineEditUsername->setObjectName("lineEditUsername");
        lineEditUsername->setGeometry(QRect(240, 160, 291, 31));

        retranslateUi(RegisterWindow);
        QObject::connect(pushButton, SIGNAL(clicked()), RegisterWindow, SLOT(on_pushButtonBackToLogin_clicked()));

        QMetaObject::connectSlotsByName(RegisterWindow);
    } // setupUi

    void retranslateUi(QWidget *RegisterWindow)
    {
        RegisterWindow->setWindowTitle(QCoreApplication::translate("RegisterWindow", "Form", nullptr));
        label->setText(QCoreApplication::translate("RegisterWindow", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("RegisterWindow", "\345\257\206\347\240\201\357\274\232", nullptr));
        register_failure->setText(QCoreApplication::translate("RegisterWindow", "\346\263\250\345\206\214\345\244\261\350\264\245\357\274\201\350\257\245\347\224\250\346\210\267\345\220\215\345\267\262\345\255\230\345\234\250\357\274\201", nullptr));
        register_success->setText(QCoreApplication::translate("RegisterWindow", "\346\263\250\345\206\214\346\210\220\345\212\237\357\274\201", nullptr));
        pushButtonRegister->setText(QCoreApplication::translate("RegisterWindow", "\346\263\250\345\206\214", nullptr));
        pushButton->setText(QCoreApplication::translate("RegisterWindow", "\345\267\262\346\234\211\350\264\246\345\217\267\357\274\237\347\231\273\345\275\225", nullptr));
        lineEditPassword->setPlaceholderText(QCoreApplication::translate("RegisterWindow", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", nullptr));
        lineEditUsername->setPlaceholderText(QCoreApplication::translate("RegisterWindow", "\350\257\267\350\276\223\345\205\245\347\224\250\346\210\267\345\220\215", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterWindow: public Ui_RegisterWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERUSER_H
