/********************************************************************************
** Form generated from reading UI file 'changePassword.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGEPASSWORD_H
#define UI_CHANGEPASSWORD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChangePasswordWindow
{
public:
    QLabel *label_3;
    QLabel *changePassword_success;
    QLineEdit *lineEditUsername;
    QLineEdit *lineEditNewPassword;
    QPushButton *pushButtonChangePassword;
    QLineEdit *lineEditOldPassword;
    QLabel *label_2;
    QLabel *changePassword_failure;
    QLabel *label;

    void setupUi(QWidget *ChangePasswordWindow)
    {
        if (ChangePasswordWindow->objectName().isEmpty())
            ChangePasswordWindow->setObjectName("ChangePasswordWindow");
        ChangePasswordWindow->resize(742, 540);
        label_3 = new QLabel(ChangePasswordWindow);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(130, 230, 91, 31));
        QFont font;
        font.setPointSize(20);
        label_3->setFont(font);
        changePassword_success = new QLabel(ChangePasswordWindow);
        changePassword_success->setObjectName("changePassword_success");
        changePassword_success->setGeometry(QRect(260, 350, 471, 31));
        changePassword_success->setFont(font);
        lineEditUsername = new QLineEdit(ChangePasswordWindow);
        lineEditUsername->setObjectName("lineEditUsername");
        lineEditUsername->setGeometry(QRect(230, 120, 291, 31));
        lineEditNewPassword = new QLineEdit(ChangePasswordWindow);
        lineEditNewPassword->setObjectName("lineEditNewPassword");
        lineEditNewPassword->setGeometry(QRect(230, 230, 291, 31));
        lineEditNewPassword->setEchoMode(QLineEdit::Password);
        pushButtonChangePassword = new QPushButton(ChangePasswordWindow);
        pushButtonChangePassword->setObjectName("pushButtonChangePassword");
        pushButtonChangePassword->setGeometry(QRect(300, 300, 75, 24));
        QFont font1;
        font1.setPointSize(12);
        pushButtonChangePassword->setFont(font1);
        lineEditOldPassword = new QLineEdit(ChangePasswordWindow);
        lineEditOldPassword->setObjectName("lineEditOldPassword");
        lineEditOldPassword->setGeometry(QRect(230, 170, 291, 31));
        lineEditOldPassword->setEchoMode(QLineEdit::Password);
        label_2 = new QLabel(ChangePasswordWindow);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(130, 170, 101, 31));
        label_2->setFont(font);
        changePassword_failure = new QLabel(ChangePasswordWindow);
        changePassword_failure->setObjectName("changePassword_failure");
        changePassword_failure->setGeometry(QRect(90, 350, 551, 31));
        changePassword_failure->setFont(font);
        label = new QLabel(ChangePasswordWindow);
        label->setObjectName("label");
        label->setGeometry(QRect(130, 110, 101, 41));
        label->setFont(font);

        retranslateUi(ChangePasswordWindow);

        QMetaObject::connectSlotsByName(ChangePasswordWindow);
    } // setupUi

    void retranslateUi(QWidget *ChangePasswordWindow)
    {
        ChangePasswordWindow->setWindowTitle(QCoreApplication::translate("ChangePasswordWindow", "Form", nullptr));
        label_3->setText(QCoreApplication::translate("ChangePasswordWindow", "\346\226\260\345\257\206\347\240\201\357\274\232", nullptr));
        changePassword_success->setText(QCoreApplication::translate("ChangePasswordWindow", "\344\277\256\346\224\271\345\257\206\347\240\201\346\210\220\345\212\237\357\274\201", nullptr));
        lineEditUsername->setPlaceholderText(QCoreApplication::translate("ChangePasswordWindow", "\350\257\267\350\276\223\345\205\245\347\224\250\346\210\267\345\220\215", nullptr));
        lineEditNewPassword->setPlaceholderText(QCoreApplication::translate("ChangePasswordWindow", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", nullptr));
        pushButtonChangePassword->setText(QCoreApplication::translate("ChangePasswordWindow", "\344\277\256\346\224\271\345\257\206\347\240\201", nullptr));
        lineEditOldPassword->setPlaceholderText(QCoreApplication::translate("ChangePasswordWindow", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", nullptr));
        label_2->setText(QCoreApplication::translate("ChangePasswordWindow", "\346\227\247\345\257\206\347\240\201\357\274\232", nullptr));
        changePassword_failure->setText(QCoreApplication::translate("ChangePasswordWindow", "\344\277\256\346\224\271\345\244\261\350\264\245\357\274\201\350\257\245\347\224\250\346\210\267\345\220\215\344\270\215\345\255\230\345\234\250\346\210\226\350\276\223\345\205\245\346\227\247\345\257\206\347\240\201\351\224\231\350\257\257\357\274\201", nullptr));
        label->setText(QCoreApplication::translate("ChangePasswordWindow", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChangePasswordWindow: public Ui_ChangePasswordWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGEPASSWORD_H
