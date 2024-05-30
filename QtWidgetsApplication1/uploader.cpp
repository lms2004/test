#define _CRT_SECURE_NO_WARNINGS

#include "uploader.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <QInputDialog>
#include <QCoreApplication>

uploader::uploader(QWidget* parent)
    : QWidget(parent), ui(new Ui::uploader) {
    ui->setupUi(this);
    projectPathLineEdit = ui->projectPathLineEdit;
    statusLabel = ui->statusLabel;
    ssh_Address = ui->SSh_Address;
    repoPath_ = ui->repoPath_;
}

void uploader::on_browseButton_clicked() {
    QString dir = QFileDialog::getExistingDirectory(this, "ѡ����ĿԴ·��", "");
    if (!dir.isEmpty()) {
        projectPathLineEdit->setText(dir);
        statusLabel->setText(QString::fromLocal8Bit("��Ŀ·����ѡ��: ") + dir);
        QCoreApplication::processEvents();
    }
    else {
        statusLabel->setText(QString::fromLocal8Bit("δѡ����Ŀ·��."));
        QCoreApplication::processEvents();
    }
}

void uploader::on_browseButton1_clicked() {
    QString dir = QFileDialog::getExistingDirectory(this, "ѡ����ĿԴ·��", "");
    if (!dir.isEmpty()) {
        repoPath_->setText(dir);
        repoPath = repoPath_->text().toStdString();
        statusLabel->setText(QString::fromLocal8Bit("��Ŀ·����ѡ��: ") + dir);
        QCoreApplication::processEvents();
    }
    else {
        statusLabel->setText(QString::fromLocal8Bit("δѡ����Ŀ·��."));
        QCoreApplication::processEvents();
    }
}


void uploader::on_pushButton_clicked() {
    statusLabel->setText(QString::fromLocal8Bit("��ʼ����"));
    QCoreApplication::processEvents();
    std::string branchName = "main";
    std::string projectSourcePath = makeLegalPath(projectPathLineEdit->text().toStdString());

    try {
        if (ssh_Address->text().toStdString() != "") {
            repoUrl = ssh_Address->text().toStdString();
        }
        gitPush(repoUrl, branchName, projectSourcePath);
        statusLabel->setText(QString::fromLocal8Bit("�ɹ����͵� GitHub."));
        QCoreApplication::processEvents();
    }
    catch (const std::runtime_error& e) {
        statusLabel->setText(QString::fromLocal8Bit(e.what()));
        QCoreApplication::processEvents();
        if (std::string(e.what()).find("Permission denied (publickey)") != std::string::npos) {
            outputSSHKey();
        }
    }
}

std::string uploader::makeLegalPath(const std::string& path) {
    statusLabel->setText(QString::fromLocal8Bit("���ڴ�����Ŀ·��..."));
    QCoreApplication::processEvents();
    fs::path p(path);
    fs::path legal_path;
    auto preferred_separator = fs::path::preferred_separator;

    for (const auto& part : p) {
        if (!part.empty() && part != std::string(1, preferred_separator)) {
            legal_path /= part;
        }
    }

    return legal_path.string();
}

void uploader::runCommand(const std::string& command) {
    statusLabel->setText(QString::fromLocal8Bit("����ִ������: ") + QString::fromStdString(command));
    QCoreApplication::processEvents();
    int result = std::system(command.c_str());
    if (result != 0) {
        throw std::runtime_error("����ִ��ʧ��: " + command);
    }
}

void uploader::generateSSHKey(const std::string& keyPath) {
    statusLabel->setText(QString::fromLocal8Bit("�������� SSH ��Կ..."));
    QCoreApplication::processEvents();
    bool ok;
    QString passphrase = QInputDialog::getText(this, tr("���� SSH ��Կ"),
        tr("δ�ҵ� SSH ��Կ����������������������µ� SSH ��Կ:"), QLineEdit::Password, "", &ok);

    if (ok && !passphrase.isEmpty()) {
        std::string command = "ssh-keygen -t rsa -b 4096 -N \"" + passphrase.toStdString() + "\" -f " + keyPath;
        runCommand(command);
        statusLabel->setText(QString::fromLocal8Bit("SSH ��Կ���ɳɹ�."));
        QCoreApplication::processEvents();
    }
    else {
        statusLabel->setText(QString::fromLocal8Bit("SSH ��Կ����ȡ��."));
        QCoreApplication::processEvents();
    }
}

bool uploader::isGitRepository(const std::string& path) {
    statusLabel->setText(QString::fromLocal8Bit("���ڼ�� Git �ֿ�..."));
    QCoreApplication::processEvents();
    return fs::exists(path + "/.git");
}

void uploader::copyProjectFiles(const std::string& source, const std::string& destination) {
    try {
        statusLabel->setText(QString::fromLocal8Bit("���ڸ�����Ŀ�ļ�..."));
        QCoreApplication::processEvents();
        // ��ȡԴĿ¼����
        std::string sourceDirName = fs::path(source).filename().string();
        // ����������Ŀ��·��
        std::string fullDestination = destination + "/" + sourceDirName;

        // ����Ŀ��Ŀ¼
        fs::create_directory(fullDestination);

        // ����ԴĿ¼���ݵ�Ŀ��Ŀ¼
        fs::copy(source, fullDestination, fs::copy_options::recursive | fs::copy_options::overwrite_existing);

        statusLabel->setText(QString::fromLocal8Bit("��Ŀ�ļ��и��Ƴɹ�."));
        QCoreApplication::processEvents();
    }
    catch (const std::exception& e) {
        statusLabel->setText(QString::fromLocal8Bit("������Ŀ�ļ���ʱ����: ") + QString::fromLocal8Bit(e.what()));
        QCoreApplication::processEvents();
    }
}

void uploader::gitPush(const std::string& repoUrl, const std::string& branchName, const std::string& projectSourcePath) {
    try {
        statusLabel->setText(QString::fromLocal8Bit("��ʼ���͵� GitHub..."));
        QCoreApplication::processEvents();
        const char* homeEnv = std::getenv("HOME");
        std::string envHome;

        if (!homeEnv) {
            bool ok;
            QString homeDir = QInputDialog::getText(this, tr("������Ŀ¼"),
                tr("������������Ŀ¼ (����, C:\\Users\\lms)"), QLineEdit::Normal, "", &ok);

            if (ok && !homeDir.isEmpty()) {
                envHome = homeDir.toStdString();
                homeEnv = envHome.c_str();
            }
        }

        std::string sshKeyPath = (fs::path(homeEnv) / ".ssh/id_rsa").string();
        if (!fs::exists(sshKeyPath)) {
            generateSSHKey(sshKeyPath);
        }


        if (!isGitRepository(repoPath)) {
            statusLabel->setText(QString::fromLocal8Bit("δ�ҵ� Git �ֿ⡣���ڿ�¡�ֿ�..."));
            QCoreApplication::processEvents();
            runCommand("git clone " + repoUrl + " " + repoPath);
        }

        std::filesystem::current_path(repoPath);

        runCommand("git fetch origin");
        runCommand("git checkout " + branchName);
        runCommand("git pull origin " + branchName);

        int fetchResult = std::system("git fetch origin");
        if (fetchResult == 0) {
            statusLabel->setText(QString::fromLocal8Bit("��֧�������£�������¡�"));
            QCoreApplication::processEvents();

            copyProjectFiles(projectSourcePath, repoPath);

            runCommand("git add .");
            runCommand("git commit -m \"�Զ��ύ\"");
            runCommand("git push origin " + branchName);

            statusLabel->setText(QString::fromLocal8Bit("�����ѳɹ����͵� GitHub."));
            QCoreApplication::processEvents();
        }
    }
    catch (const std::exception& e) {
        statusLabel->setText(QString::fromLocal8Bit("����: ") + QString::fromLocal8Bit(e.what()));
        QCoreApplication::processEvents();
    }
}

void uploader::outputSSHKey() {
    statusLabel->setText(QString::fromLocal8Bit("������� SSH ��Կ..."));
    QCoreApplication::processEvents();
    const char* homeEnv = std::getenv("HOME");
    std::string envHome;

    if (!homeEnv) {
        bool ok;
        QString homeDir = QInputDialog::getText(this, tr("������Ŀ¼"),
            tr("������������Ŀ¼ (����, C:\\Users\\lms)"), QLineEdit::Normal, "", &ok);

        if (ok && !homeDir.isEmpty()) {
            envHome = homeDir.toStdString();
            homeEnv = envHome.c_str();
        }
    }

    std::string sshPubKeyPath = (fs::path(homeEnv) / ".ssh/id_rsa.pub").string();
    if (fs::exists(sshPubKeyPath)) {
        std::ifstream pubKeyFile(sshPubKeyPath);
        std::string pubKey((std::istreambuf_iterator<char>(pubKeyFile)), std::istreambuf_iterator<char>());

        statusLabel->setText(QString::fromLocal8Bit("�뽫���¹�Կ��ӵ����� GitHub �˻����������֤:\n") + QString::fromLocal8Bit(pubKey.c_str()));
        QCoreApplication::processEvents();
    }
    else {
        statusLabel->setText(QString::fromLocal8Bit("δ�ҵ���Կ�ļ�: ") + QString::fromLocal8Bit(sshPubKeyPath.c_str()));
        QCoreApplication::processEvents();
    }
}
