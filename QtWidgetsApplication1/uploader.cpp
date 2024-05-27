#include "uploader.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QHttpMultiPart>
#include <QProcess>
#include <iostream>
#include <algorithm>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QEventLoop>
#include <QDir>
#include <QFile>

uploader::uploader(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    // 连接信号和槽
    connect(ui.pushButtonUpload, &QPushButton::clicked, this, &uploader::onStartUploadClicked);
    connect(ui.pushButtonConfirmDelete, &QPushButton::clicked, this, &uploader::onConfirmDeleteClicked);
}

uploader::~uploader()
{}

void uploader::displayTopProjectDetails(const Project& project)
{
    // 显示最高成绩项目的详细信息
    ui.labelProjectName->setText(QString("Name: %1").arg(QString::fromStdString(project.name)));
    ui.labelProjectScore->setText(QString("Grade: %1").arg(QString::number(std::stoi(project.grade))));
}

QString uploader::getRepositoryName()
{
    // 获取用户输入的 GitHub 仓库名称
    return ui.lineEditRepositoryName->text();
}

QString uploader::getAccessToken()
{
    // 获取用户输入的 GitHub 个人访问令牌
    return ui.lineEditAccessToken->text();
}

void uploader::onStartUploadClicked()
{
    // 处理开始上传按钮点击事件，调用上传函数

    // 获取仓库名称和访问令牌
    QString repositoryName = getRepositoryName();
    QString accessToken = getAccessToken();

    // 检查输入是否为空
    if (repositoryName.isEmpty() || accessToken.isEmpty()) {
        QMessageBox::warning(this, tr("Warning"), tr("Please enter repository name and access token."));
        return;
    }

    // 获取最高成绩项目文件夹路径
    std::vector<Project> projects; // 从打分模块获取项目列表
    std::string topFolderPath = getTopGradedProjectFolder(projects);

    // 调用上传函数，并显示上传进度和状态
    bool uploadResult = uploadProjectFolderToGitHub(topFolderPath, repositoryName, accessToken);
    if (uploadResult) {
        ui.labelUploadStatus->setText("Upload Successful"); // 确认组件名称为 labelUploadStatus
    }
    else {
        ui.labelUploadStatus->setText("Upload Failed"); // 确认组件名称为 labelUploadStatus
    }
}

void uploader::updateUploadProgress(int value)
{
    // 更新上传进度
    ui.progressBarUpload->setValue(value);
}

void uploader::onConfirmDeleteClicked()
{
    // 处理确认删除按钮点击事件，调用删除函数

    // 获取最高成绩项目文件夹路径
    std::vector<Project> projects; // 从打分模块获取项目列表
    std::string topFolderPath = getTopGradedProjectFolder(projects);

    // 调用删除函数，并显示删除进度和状态
    bool deleteResult = deleteRemainingProjectFolders(projects, topFolderPath);
    if (deleteResult) {
        ui.labelDeleteStatus->setText("Delete Successful"); // 确认组件名称为 labelDeleteStatus
    }
    else {
        ui.labelDeleteStatus->setText("Delete Failed"); // 确认组件名称为 labelDeleteStatus
    }
}

void uploader::updateDeleteProgress(int value)
{
    // 更新删除进度
    ui.progressBarDelete->setValue(value);
}

std::string uploader::getTopGradedProjectFolder(const std::vector<Project>& projects)
{
    // 实现获取成绩最高的项目文件夹的逻辑
    // 找到最高成绩的项目
    if (projects.empty()) {
        // 如果项目列表为空，显示警告
        QMessageBox::warning(this, tr("Warning"), tr("No projects found."));
        return "";
    }

    const Project& topProject = *std::max_element(projects.begin(), projects.end(),
        [](const Project& a, const Project& b) {
            return std::stoi(a.grade) < std::stoi(b.grade);
        });

    // 利用函数 outputFolderPath 返回最高成绩项目的文件夹路径
    return outputFolderPath(topProject.name, topProject.type);
}

bool uploader::uploadProjectFolderToGitHub(const std::string& folderPath, const QString& repositoryName, const QString& accessToken)
{
    QDir directory(QString::fromStdString(folderPath));
    if (!directory.exists()) {
        QMessageBox::warning(this, tr("Error"), tr("The specified folder does not exist."));
        return false;
    }

    // 获取文件列表
    QStringList files = directory.entryList(QDir::Files);

    QNetworkAccessManager manager;
    bool allFilesUploaded = true;

    foreach(QString fileName, files) {
        QFile file(directory.filePath(fileName));
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(this, tr("Error"), tr("Unable to open file: %1").arg(fileName));
            allFilesUploaded = false;
            continue;
        }

        // 读取文件内容并进行 Base64 编码
        QByteArray fileContent = file.readAll().toBase64();

        // 构建 GitHub API 端点 URL
        QUrl apiUrl = QUrl("https://api.github.com/repos/" + repositoryName + "/contents/" + fileName);

        // 构建 JSON 数据
        QJsonObject json;
        json["message"] = "Upload " + fileName;
        json["content"] = QString(fileContent);
        json["branch"] = "main";

        QJsonDocument jsonDoc(json);

        // 创建网络请求
        QNetworkRequest request(apiUrl);
        request.setRawHeader("Authorization", QByteArray("token " + accessToken.toUtf8()));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        // 发送请求并等待回复
        QNetworkReply* reply = manager.put(request, jsonDoc.toJson());
        QEventLoop eventLoop;
        connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
        eventLoop.exec();

        // 处理回复
        if (reply->error() != QNetworkReply::NoError) {
            allFilesUploaded = false;
        }
        reply->deleteLater();
    }

    return allFilesUploaded;
}

bool uploader::deleteRemainingProjectFolders(const std::vector<Project>& projects, const std::string& topFolderPath)
{
    // 实现删除剩余项目文件夹的逻辑
    for (const auto& project : projects) {
        std::string folderPath = outputFolderPath(project.name, project.type);
        if (folderPath != topFolderPath) {
            QDir dir(QString::fromStdString(folderPath));
            if (dir.exists()) {
                dir.removeRecursively();
            }
        }
    }
    return true;
}

std::string uploader::outputFolderPath(const std::string& projectName, const std::string& projectType)
{
    // 实现生成项目文件夹路径的逻辑
    return "/path/to/projects/" + projectName + "_" + projectType;
}
