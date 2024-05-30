/********************************************************************************
** Form generated from reading UI file 'ProjectScoreManage.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTSCOREMANAGE_H
#define UI_PROJECTSCOREMANAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProjectScoreManage
{
public:
    QLabel *label_2;
    QLabel *label;
    QPushButton *ProjectPath;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *ViewProjects;
    QLabel *label_6;
    QPushButton *pushButton;
    QDialogButtonBox *SetProjectYorN;
    QTableWidget *Widget1;
    QLabel *label_7;
    QLineEdit *deleteproject;
    QPushButton *pushButton_2;
    QLabel *deletefalse_1;
    QLabel *deleteproject_true;
    QLabel *deletefalse_2;
    QLabel *projectpaixu;

    void setupUi(QWidget *ProjectScoreManage)
    {
        if (ProjectScoreManage->objectName().isEmpty())
            ProjectScoreManage->setObjectName("ProjectScoreManage");
        ProjectScoreManage->resize(598, 341);
        label_2 = new QLabel(ProjectScoreManage);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(220, 10, 101, 41));
        label = new QLabel(ProjectScoreManage);
        label->setObjectName("label");
        label->setGeometry(QRect(160, 60, 91, 20));
        ProjectPath = new QPushButton(ProjectScoreManage);
        ProjectPath->setObjectName("ProjectPath");
        ProjectPath->setGeometry(QRect(290, 60, 161, 24));
        label_3 = new QLabel(ProjectScoreManage);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(160, 90, 121, 20));
        label_4 = new QLabel(ProjectScoreManage);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(160, 110, 151, 16));
        ViewProjects = new QPushButton(ProjectScoreManage);
        ViewProjects->setObjectName("ViewProjects");
        ViewProjects->setGeometry(QRect(300, 90, 80, 31));
        label_6 = new QLabel(ProjectScoreManage);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(160, 140, 131, 20));
        pushButton = new QPushButton(ProjectScoreManage);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(290, 140, 131, 24));
        SetProjectYorN = new QDialogButtonBox(ProjectScoreManage);
        SetProjectYorN->setObjectName("SetProjectYorN");
        SetProjectYorN->setGeometry(QRect(250, 220, 166, 24));
        SetProjectYorN->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        Widget1 = new QTableWidget(ProjectScoreManage);
        if (Widget1->columnCount() < 4)
            Widget1->setColumnCount(4);
        QBrush brush(QColor(255, 170, 0, 255));
        brush.setStyle(Qt::NoBrush);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setForeground(brush);
        Widget1->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QBrush brush1(QColor(255, 0, 0, 255));
        brush1.setStyle(Qt::NoBrush);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setForeground(brush1);
        Widget1->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QBrush brush2(QColor(255, 0, 0, 255));
        brush2.setStyle(Qt::NoBrush);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setForeground(brush2);
        Widget1->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QBrush brush3(QColor(255, 0, 0, 255));
        brush3.setStyle(Qt::NoBrush);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setForeground(brush3);
        Widget1->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        Widget1->setObjectName("Widget1");
        Widget1->setGeometry(QRect(130, 10, 401, 201));
        label_7 = new QLabel(ProjectScoreManage);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 40, 261, 51));
        deleteproject = new QLineEdit(ProjectScoreManage);
        deleteproject->setObjectName("deleteproject");
        deleteproject->setGeometry(QRect(10, 90, 113, 23));
        pushButton_2 = new QPushButton(ProjectScoreManage);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(30, 130, 80, 24));
        deletefalse_1 = new QLabel(ProjectScoreManage);
        deletefalse_1->setObjectName("deletefalse_1");
        deletefalse_1->setGeometry(QRect(40, 170, 54, 16));
        deleteproject_true = new QLabel(ProjectScoreManage);
        deleteproject_true->setObjectName("deleteproject_true");
        deleteproject_true->setGeometry(QRect(40, 170, 54, 16));
        deletefalse_2 = new QLabel(ProjectScoreManage);
        deletefalse_2->setObjectName("deletefalse_2");
        deletefalse_2->setGeometry(QRect(40, 170, 54, 16));
        projectpaixu = new QLabel(ProjectScoreManage);
        projectpaixu->setObjectName("projectpaixu");
        projectpaixu->setGeometry(QRect(260, 270, 131, 20));

        retranslateUi(ProjectScoreManage);
        QObject::connect(ProjectPath, SIGNAL(clicked()), ProjectScoreManage, SLOT(slot1()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), ProjectScoreManage, SLOT(deleteproject()));
        QObject::connect(SetProjectYorN, SIGNAL(accepted()), ProjectScoreManage, SLOT(ProjectsPathAccept()));
        QObject::connect(SetProjectYorN, SIGNAL(rejected()), ProjectScoreManage, SLOT(ProjectsPathReject()));
        QObject::connect(ViewProjects, SIGNAL(clicked()), ProjectScoreManage, SLOT(viewprojects()));
        QObject::connect(pushButton, SIGNAL(clicked()), ProjectScoreManage, SLOT(selectproject()));

        QMetaObject::connectSlotsByName(ProjectScoreManage);
    } // setupUi

    void retranslateUi(QWidget *ProjectScoreManage)
    {
        ProjectScoreManage->setWindowTitle(QCoreApplication::translate("ProjectScoreManage", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("ProjectScoreManage", "<html><head/><body><p><span style=\" font-size:18pt;\">\346\210\220\347\273\251\347\256\241\347\220\206</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("ProjectScoreManage", "1.\350\256\276\347\275\256\351\241\271\347\233\256\346\210\220\347\273\251", nullptr));
        ProjectPath->setText(QCoreApplication::translate("ProjectScoreManage", "\347\202\271\345\207\273\346\214\221\351\200\211\351\241\271\347\233\256\346\211\200\345\234\250\347\232\204\350\267\257\345\276\204", nullptr));
        label_3->setText(QCoreApplication::translate("ProjectScoreManage", "2.\346\237\245\347\234\213\347\216\260\346\234\211\351\241\271\347\233\256\345\217\212\346\210\220\347\273\251", nullptr));
        label_4->setText(QCoreApplication::translate("ProjectScoreManage", "\344\277\256\346\224\271\351\241\271\347\233\256(\345\210\240\351\231\244,\344\277\256\346\224\271\346\210\220\347\273\251)", nullptr));
        ViewProjects->setText(QCoreApplication::translate("ProjectScoreManage", "\346\237\245\347\234\213\351\241\271\347\233\256", nullptr));
        label_6->setText(QCoreApplication::translate("ProjectScoreManage", "3.\351\241\271\347\233\256\346\216\222\345\272\217\345\217\212\345\216\273\351\207\215", nullptr));
        pushButton->setText(QCoreApplication::translate("ProjectScoreManage", "\351\241\271\347\233\256\346\216\222\345\272\217\345\217\212\345\216\273\351\207\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem = Widget1->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ProjectScoreManage", "file(name)", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = Widget1->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ProjectScoreManage", "type", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = Widget1->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ProjectScoreManage", "score", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = Widget1->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ProjectScoreManage", "path", nullptr));
        label_7->setText(QCoreApplication::translate("ProjectScoreManage", "<html><head/><body><p><span style=\" font-size:7pt;\">\350\257\267\350\276\223\345\205\245\351\234\200\350\246\201\345\210\240\351\231\244\347\232\204\351\241\271\347\233\256\347\232\204\350\241\214\345\217\267</span></p></body></html>", nullptr));
        pushButton_2->setText(QCoreApplication::translate("ProjectScoreManage", "\345\210\240\351\231\244\351\241\271\347\233\256", nullptr));
        deletefalse_1->setText(QCoreApplication::translate("ProjectScoreManage", "\350\276\223\345\205\245\351\235\236\346\263\225!", nullptr));
        deleteproject_true->setText(QCoreApplication::translate("ProjectScoreManage", "\345\210\240\351\231\244\346\210\220\345\212\237!", nullptr));
        deletefalse_2->setText(QCoreApplication::translate("ProjectScoreManage", "\346\227\240\346\255\244\350\241\214!", nullptr));
        projectpaixu->setText(QCoreApplication::translate("ProjectScoreManage", "<html><head/><body><p><span style=\" font-size:12pt;\">\351\241\271\347\233\256\346\216\222\345\272\217\345\216\273\351\207\215\346\210\220\345\212\237</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProjectScoreManage: public Ui_ProjectScoreManage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTSCOREMANAGE_H
