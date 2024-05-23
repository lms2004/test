#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")// 该指令仅支持VS环境
#endif

#pragma once
#pragma execution_character_set("utf-8")
#include  <iostream>
#include <QMainWindow>
#include <QtWidgets/QMainWindow>
#include "ui_ProjectScoreManage.h"
#include "ProjectScore.h"
#include <QApplication>
#include <QFileDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
class ProjectScoreManage : public QWidget
{
    Q_OBJECT
public:
    ProjectScoreManage(QWidget* parent = nullptr);
    ~ProjectScoreManage();

private:
    Ui::ProjectScoreManage ui;
    std::vector<Project> projects;
private slots:
    void slot1();
    void slot2(const QString& directoryPath);
    void ProjectsPathReject();
    void ProjectsPathAccept();
    void viewprojects();
    void deleteproject();
    void INPUTWidget1(int a = -1);
    //void OUTPUTWidget1();
    void selectproject();
};
