/********************************************************************************
** Form generated from reading UI file 'uploader.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPLOADER_H
#define UI_UPLOADER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_uploader
{
public:
    QLineEdit *projectPathLineEdit;
    QPushButton *browseButton;
    QPushButton *pushButton;
    QLabel *statusLabel;
    QLabel *label;
    QLineEdit *SSh_Address;
    QLabel *label_2;
    QLineEdit *repoPath_;
    QLabel *label_3;
    QPushButton *browseButton1;

    void setupUi(QWidget *uploader)
    {
        if (uploader->objectName().isEmpty())
            uploader->setObjectName("uploader");
        uploader->resize(600, 400);
        projectPathLineEdit = new QLineEdit(uploader);
        projectPathLineEdit->setObjectName("projectPathLineEdit");
        projectPathLineEdit->setGeometry(QRect(70, 90, 391, 41));
        browseButton = new QPushButton(uploader);
        browseButton->setObjectName("browseButton");
        browseButton->setGeometry(QRect(470, 100, 81, 31));
        pushButton = new QPushButton(uploader);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(220, 320, 91, 31));
        statusLabel = new QLabel(uploader);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setGeometry(QRect(60, 20, 461, 101));
        label = new QLabel(uploader);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 30, 231, 20));
        SSh_Address = new QLineEdit(uploader);
        SSh_Address->setObjectName("SSh_Address");
        SSh_Address->setGeometry(QRect(70, 250, 391, 41));
        label_2 = new QLabel(uploader);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(60, 220, 261, 20));
        repoPath_ = new QLineEdit(uploader);
        repoPath_->setObjectName("repoPath_");
        repoPath_->setGeometry(QRect(70, 170, 391, 41));
        label_3 = new QLabel(uploader);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(60, 140, 271, 16));
        browseButton1 = new QPushButton(uploader);
        browseButton1->setObjectName("browseButton1");
        browseButton1->setGeometry(QRect(470, 180, 81, 31));

        retranslateUi(uploader);

        QMetaObject::connectSlotsByName(uploader);
    } // setupUi

    void retranslateUi(QWidget *uploader)
    {
        uploader->setWindowTitle(QCoreApplication::translate("uploader", "uploader", nullptr));
        projectPathLineEdit->setText(QString());
        browseButton->setText(QCoreApplication::translate("uploader", "\346\265\217\350\247\210", nullptr));
        pushButton->setText(QCoreApplication::translate("uploader", "\346\217\220\344\272\244", nullptr));
        statusLabel->setText(QCoreApplication::translate("uploader", "\350\257\267\351\200\211\346\213\251\345\245\275\351\234\200\350\246\201\344\270\212\344\274\240\347\232\204\346\226\207\344\273\266\345\244\271", nullptr));
        label->setText(QCoreApplication::translate("uploader", "\345\267\262\351\200\211\346\213\251\347\232\204\351\241\271\347\233\256\346\226\207\344\273\266\345\244\271\350\267\257\345\276\204", nullptr));
        label_2->setText(QCoreApplication::translate("uploader", "\350\257\267\350\276\223\345\205\245\345\257\271\345\272\224\347\232\204SSH\344\273\223\345\272\223\345\234\260\345\235\200\357\274\210\345\220\246\345\210\231\345\217\226\351\273\230\350\256\244\345\200\274\357\274\211", nullptr));
        label_3->setText(QCoreApplication::translate("uploader", "\350\257\267\350\276\223\345\205\245\345\257\271\345\272\224\347\232\204\346\234\254\345\234\260\345\255\230\345\202\250\344\273\223\345\272\223\345\234\260\345\235\200\357\274\210\345\220\246\345\210\231\345\217\226\351\273\230\350\256\244\345\200\274\357\274\211", nullptr));
        browseButton1->setText(QCoreApplication::translate("uploader", "\346\265\217\350\247\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class uploader: public Ui_uploader {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPLOADER_H
