#ifndef _UPLOADER_H
#define _UPLOADER_H

#include <QMainWindow>
#include "ui_uploader.h"
#include "ProjectScore.h"
#include "ProjectScoreManage.h" 
#include <QWidget>

class uploader : public QWidget
{
    Q_OBJECT

public:
    uploader(QWidget* parent = nullptr); // 构造函数
    ~uploader(); // 析构函数

    void displayTopProjectDetails(const Project& project); // 显示最高成绩项目的详细信息
    QString getRepositoryName(); // 获取用户输入的 GitHub 仓库名称
    QString getAccessToken(); // 获取用户输入的 GitHub 个人访问令牌
    void updateUploadProgress(int value); // 更新上传进度
    void displayDeleteConfirmation(const QString& topProjectName); // 显示删除确认信息
    void updateDeleteProgress(int value); // 更新删除进度

private slots:
    void onStartUploadClicked(); // 处理开始上传按钮点击事件的槽函数
    void onConfirmDeleteClicked(); // 处理确认删除按钮点击事件的槽函数

private:
    Ui::uploaderClass ui; // UI 对象

    ProjectScoreManage projectScoreManager; // 打分模块实例

    std::string getTopGradedProjectFolder(const std::vector<Project>& projects); // 获取最高成绩项目文件夹路径
    bool uploadProjectFolderToGitHub(const std::string& folderPath, const QString& repositoryName, const QString& accessToken); // 上传项目文件夹到 GitHub
    bool deleteRemainingProjectFolders(const std::vector<Project>& projects, const std::string& topFolderPath); // 删除剩余项目文件夹
    std::string outputFolderPath(const std::string& projectName, const std::string& projectType); // 生成项目文件夹路径
};

#endif  _UPLOADER_H
