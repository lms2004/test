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
    uploader(QWidget* parent = nullptr); // ���캯��
    ~uploader(); // ��������

    void displayTopProjectDetails(const Project& project); // ��ʾ��߳ɼ���Ŀ����ϸ��Ϣ
    QString getRepositoryName(); // ��ȡ�û������ GitHub �ֿ�����
    QString getAccessToken(); // ��ȡ�û������ GitHub ���˷�������
    void updateUploadProgress(int value); // �����ϴ�����
    void displayDeleteConfirmation(const QString& topProjectName); // ��ʾɾ��ȷ����Ϣ
    void updateDeleteProgress(int value); // ����ɾ������

private slots:
    void onStartUploadClicked(); // ����ʼ�ϴ���ť����¼��Ĳۺ���
    void onConfirmDeleteClicked(); // ����ȷ��ɾ����ť����¼��Ĳۺ���

private:
    Ui::uploaderClass ui; // UI ����

    ProjectScoreManage projectScoreManager; // ���ģ��ʵ��

    std::string getTopGradedProjectFolder(const std::vector<Project>& projects); // ��ȡ��߳ɼ���Ŀ�ļ���·��
    bool uploadProjectFolderToGitHub(const std::string& folderPath, const QString& repositoryName, const QString& accessToken); // �ϴ���Ŀ�ļ��е� GitHub
    bool deleteRemainingProjectFolders(const std::vector<Project>& projects, const std::string& topFolderPath); // ɾ��ʣ����Ŀ�ļ���
    std::string outputFolderPath(const std::string& projectName, const std::string& projectType); // ������Ŀ�ļ���·��
};

#endif  _UPLOADER_H
