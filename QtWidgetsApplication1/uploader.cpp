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

    // �����źźͲ�
    connect(ui.pushButtonUpload, &QPushButton::clicked, this, &uploader::onStartUploadClicked);
    connect(ui.pushButtonConfirmDelete, &QPushButton::clicked, this, &uploader::onConfirmDeleteClicked);
}

uploader::~uploader()
{}

void uploader::displayTopProjectDetails(const Project& project)
{
    // ��ʾ��߳ɼ���Ŀ����ϸ��Ϣ
    ui.labelProjectName->setText(QString("Name: %1").arg(QString::fromStdString(project.name)));
    ui.labelProjectScore->setText(QString("Grade: %1").arg(QString::number(std::stoi(project.grade))));
}

QString uploader::getRepositoryName()
{
    // ��ȡ�û������ GitHub �ֿ�����
    return ui.lineEditRepositoryName->text();
}

QString uploader::getAccessToken()
{
    // ��ȡ�û������ GitHub ���˷�������
    return ui.lineEditAccessToken->text();
}

void uploader::onStartUploadClicked()
{
    // ����ʼ�ϴ���ť����¼��������ϴ�����

    // ��ȡ�ֿ����ƺͷ�������
    QString repositoryName = getRepositoryName();
    QString accessToken = getAccessToken();

    // ��������Ƿ�Ϊ��
    if (repositoryName.isEmpty() || accessToken.isEmpty()) {
        QMessageBox::warning(this, tr("Warning"), tr("Please enter repository name and access token."));
        return;
    }

    // ��ȡ��߳ɼ���Ŀ�ļ���·��
    std::vector<Project> projects; // �Ӵ��ģ���ȡ��Ŀ�б�
    std::string topFolderPath = getTopGradedProjectFolder(projects);

    // �����ϴ�����������ʾ�ϴ����Ⱥ�״̬
    bool uploadResult = uploadProjectFolderToGitHub(topFolderPath, repositoryName, accessToken);
    if (uploadResult) {
        ui.labelUploadStatus->setText("Upload Successful"); // ȷ���������Ϊ labelUploadStatus
    }
    else {
        ui.labelUploadStatus->setText("Upload Failed"); // ȷ���������Ϊ labelUploadStatus
    }
}

void uploader::updateUploadProgress(int value)
{
    // �����ϴ�����
    ui.progressBarUpload->setValue(value);
}

void uploader::onConfirmDeleteClicked()
{
    // ����ȷ��ɾ����ť����¼�������ɾ������

    // ��ȡ��߳ɼ���Ŀ�ļ���·��
    std::vector<Project> projects; // �Ӵ��ģ���ȡ��Ŀ�б�
    std::string topFolderPath = getTopGradedProjectFolder(projects);

    // ����ɾ������������ʾɾ�����Ⱥ�״̬
    bool deleteResult = deleteRemainingProjectFolders(projects, topFolderPath);
    if (deleteResult) {
        ui.labelDeleteStatus->setText("Delete Successful"); // ȷ���������Ϊ labelDeleteStatus
    }
    else {
        ui.labelDeleteStatus->setText("Delete Failed"); // ȷ���������Ϊ labelDeleteStatus
    }
}

void uploader::updateDeleteProgress(int value)
{
    // ����ɾ������
    ui.progressBarDelete->setValue(value);
}

std::string uploader::getTopGradedProjectFolder(const std::vector<Project>& projects)
{
    // ʵ�ֻ�ȡ�ɼ���ߵ���Ŀ�ļ��е��߼�
    // �ҵ���߳ɼ�����Ŀ
    if (projects.empty()) {
        // �����Ŀ�б�Ϊ�գ���ʾ����
        QMessageBox::warning(this, tr("Warning"), tr("No projects found."));
        return "";
    }

    const Project& topProject = *std::max_element(projects.begin(), projects.end(),
        [](const Project& a, const Project& b) {
            return std::stoi(a.grade) < std::stoi(b.grade);
        });

    // ���ú��� outputFolderPath ������߳ɼ���Ŀ���ļ���·��
    return outputFolderPath(topProject.name, topProject.type);
}

bool uploader::uploadProjectFolderToGitHub(const std::string& folderPath, const QString& repositoryName, const QString& accessToken)
{
    QDir directory(QString::fromStdString(folderPath));
    if (!directory.exists()) {
        QMessageBox::warning(this, tr("Error"), tr("The specified folder does not exist."));
        return false;
    }

    // ��ȡ�ļ��б�
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

        // ��ȡ�ļ����ݲ����� Base64 ����
        QByteArray fileContent = file.readAll().toBase64();

        // ���� GitHub API �˵� URL
        QUrl apiUrl = QUrl("https://api.github.com/repos/" + repositoryName + "/contents/" + fileName);

        // ���� JSON ����
        QJsonObject json;
        json["message"] = "Upload " + fileName;
        json["content"] = QString(fileContent);
        json["branch"] = "main";

        QJsonDocument jsonDoc(json);

        // ������������
        QNetworkRequest request(apiUrl);
        request.setRawHeader("Authorization", QByteArray("token " + accessToken.toUtf8()));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        // �������󲢵ȴ��ظ�
        QNetworkReply* reply = manager.put(request, jsonDoc.toJson());
        QEventLoop eventLoop;
        connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
        eventLoop.exec();

        // ����ظ�
        if (reply->error() != QNetworkReply::NoError) {
            allFilesUploaded = false;
        }
        reply->deleteLater();
    }

    return allFilesUploaded;
}

bool uploader::deleteRemainingProjectFolders(const std::vector<Project>& projects, const std::string& topFolderPath)
{
    // ʵ��ɾ��ʣ����Ŀ�ļ��е��߼�
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
    // ʵ��������Ŀ�ļ���·�����߼�
    return "/path/to/projects/" + projectName + "_" + projectType;
}
