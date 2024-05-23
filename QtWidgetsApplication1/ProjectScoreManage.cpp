#include "ProjectScoreManage.h"
#include "ProjectScore.h"
#include<iostream>
#include <string>
#include <QDebug>
#include <QtWidgets/QItemDelegate>
ProjectScoreManage::ProjectScoreManage(QWidget* parent)
    : QWidget(parent)
{

    ui.setupUi(this);

    ui.Widget1->hide();
    /* QString text = QString::fromLocal8Bit("点击下方按钮挑选项目所在路径并设置项目的成绩(score)和类型(type) ");
     ui.lineEdit->setText(text);*/
    ui.SetProjectYorN->hide();
    ui.deletefalse_1->hide();
    ui.deletefalse_2->hide();
    ui.deleteproject_true->hide();
    ui.deleteproject->hide();
    ui.label_7->hide();
    ui.pushButton_2->hide();
    ui.projectpaixu->hide();
    ProjectMysql w;
    w.OutputProject(projects);
    ui.deleteproject->setInputMask("99999");
}

ProjectScoreManage::~ProjectScoreManage()
{}

//用户挑选文件所在路径
void ProjectScoreManage::slot1() {
    QString directory = QFileDialog::getExistingDirectory(this, tr("Selected directory "), QDir::homePath(), QFileDialog::ShowDirsOnly);
    if (!directory.isEmpty()) {
        slot2(directory);
    }
    ui.projectpaixu->hide();
}

//展现
void ProjectScoreManage::slot2(const QString& directoryPath) {
    QDir dir(directoryPath);
    QStringList filename;
    QStringList results;


    // 将文件名添加到QTableWidget中
    QStringList columnNames;
    ui.Widget1->setRowCount(0);
    for (const QString& fileName : dir.entryList()) {
        int row = ui.Widget1->rowCount();
        ui.Widget1->insertRow(row);
        QTableWidgetItem* item = new QTableWidgetItem(fileName);
        ui.Widget1->setItem(row, 0, item);
        item = new QTableWidgetItem(directoryPath);
        ui.Widget1->setItem(row, 3, item);
    }

    ui.label->hide();
    ui.label_2->hide();
    ui.label_3->hide();
    ui.ProjectPath->hide();
    ui.ViewProjects->hide();
    ui.Widget1->show();
    ui.SetProjectYorN->show();
}


void ProjectScoreManage::ProjectsPathReject() {
    ui.label->show();
    ui.label_2->show();
    ui.label_3->show();
    ui.ProjectPath->show();
    ui.ViewProjects->show();
    ui.Widget1->hide();
    ui.SetProjectYorN->hide();
    ui.pushButton_2->hide();
    ui.deleteproject->hide();
    ui.label_7->hide();
    ui.deletefalse_1->hide();
    ui.deletefalse_2->hide();
    ui.deleteproject_true->hide();
    ui.projectpaixu->hide();
}


void ProjectScoreManage::ProjectsPathAccept() {
    ui.label->show();
    ui.label_2->show();
    ui.label_3->show();
    ui.ProjectPath->show();
    ui.ViewProjects->show();
    ui.Widget1->hide();
    ui.SetProjectYorN->hide();
    ui.projectpaixu->hide();

    // 遍历所有单元格并获取数据
    projects.clear();
    INPUTWidget1();
    ProjectMysql w;
    w.InputProject(projects);
    ui.pushButton_2->hide();
    ui.deleteproject->hide();
    ui.label_7->hide();
    ui.deletefalse_1->hide();
    ui.deletefalse_2->hide();
    ui.deleteproject_true->hide();
    ui.projectpaixu->hide();

}




void ProjectScoreManage::viewprojects() {
    ui.Widget1->setRowCount(0);
    std::vector <Project>::iterator project = projects.begin();
    int row = 0;
    for (auto project = projects.begin(); project != projects.end(); ++project, ++row) {
        ui.Widget1->insertRow(row);
        qDebug() << project->path;

        QString name_str = QString(QString::fromLocal8Bit(project->name.data()));
        QString type_str = QString(QString::fromLocal8Bit(project->type.data()));
        QString score_str = QString(QString::fromLocal8Bit(project->grade.data()));
        QString path_str = QString(QString::fromLocal8Bit(project->path.data()));

        // 将数据设置为 QTableWidgetItem 对象，并添加到 QTableWidget 中
        ui.Widget1->setItem(row, 0, new QTableWidgetItem(name_str));
        ui.Widget1->setItem(row, 1, new QTableWidgetItem(type_str));
        ui.Widget1->setItem(row, 2, new QTableWidgetItem(score_str));
        ui.Widget1->setItem(row, 3, new QTableWidgetItem(path_str));
    }
    ui.Widget1->show();
    ui.SetProjectYorN->show();
    ui.label_7->show();
    ui.deleteproject->show();
    ui.pushButton_2->show();
    ui.projectpaixu->hide();
}



void ProjectScoreManage::deleteproject() {
    ui.deletefalse_1->hide();
    ui.deletefalse_2->hide();
    ui.deleteproject_true->hide();
    QString number = ui.deleteproject->text();
    bool ok;
    int num = number.toInt(&ok); // 转换为整型
    if (ok) {
        int rowCount = ui.Widget1->rowCount();
        if (rowCount < num - 1) {
            ui.deletefalse_2->show();
        }
        else {
            projects.clear();
            INPUTWidget1(num);
            viewprojects();
        }
        ui.deleteproject->clear();

    }

    else {
        ui.deletefalse_1->show();
    }
    ui.projectpaixu->show();
}


void ProjectScoreManage::INPUTWidget1(int a) {
    a = a - 1;
    int rowCount = ui.Widget1->rowCount();
    int columnCount = ui.Widget1->columnCount();
    for (int row = 0; row < rowCount; ++row) {
        if (ui.Widget1->item(row, 0) != nullptr && ui.Widget1->item(row, 1) != nullptr && ui.Widget1->item(row, 2) != nullptr && ui.Widget1->item(row, 3) != nullptr && row != a)
        {
            QString name = ui.Widget1->item(row, 0)->text();
            QString type = ui.Widget1->item(row, 1)->text();
            QString path = ui.Widget1->item(row, 2)->text();
            QString score = ui.Widget1->item(row, 3)->text();
            qDebug() << path;

            std::string str;
            std::string str1;
            std::string str2;
            std::string str3;

            str = name.toLocal8Bit();
            str1 = type.toLocal8Bit();
            str2 = path.toLocal8Bit();
            str3 = score.toLocal8Bit();

            std::string namestr = std::string(str);
            std::string typestr = std::string(str1);
            std::string pathstr = std::string(str2);
            std::string scorestr = std::string(str3);
            QString  str_1 = QString(QString::fromLocal8Bit(namestr.data()));
            Project project(namestr, typestr, pathstr, scorestr);
            projects.push_back(project);
            //  qDebug() << projects[0].name << projects[0].path<<projects[0].grade;
        }

    }
    if (a != -2) {
        ui.deleteproject_true->show();
    }
}

void ProjectScoreManage::selectproject() {
    ProjectSorting k;
    k.deduplicateByTypeAndGrade(projects);
    ui.projectpaixu->show();
}