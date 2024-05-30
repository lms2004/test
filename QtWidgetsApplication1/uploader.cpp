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
    QString dir = QFileDialog::getExistingDirectory(this, "选择项目源路径", "");
    if (!dir.isEmpty()) {
        projectPathLineEdit->setText(dir);
        statusLabel->setText(QString::fromLocal8Bit("项目路径已选择: ") + dir);
        QCoreApplication::processEvents();
    }
    else {
        statusLabel->setText(QString::fromLocal8Bit("未选择项目路径."));
        QCoreApplication::processEvents();
    }
}

void uploader::on_browseButton1_clicked() {
    QString dir = QFileDialog::getExistingDirectory(this, "选择项目源路径", "");
    if (!dir.isEmpty()) {
        repoPath_->setText(dir);
        repoPath = repoPath_->text().toStdString();
        statusLabel->setText(QString::fromLocal8Bit("项目路径已选择: ") + dir);
        QCoreApplication::processEvents();
    }
    else {
        statusLabel->setText(QString::fromLocal8Bit("未选择项目路径."));
        QCoreApplication::processEvents();
    }
}


void uploader::on_pushButton_clicked() {
    statusLabel->setText(QString::fromLocal8Bit("开始推送"));
    QCoreApplication::processEvents();
    std::string branchName = "main";
    std::string projectSourcePath = makeLegalPath(projectPathLineEdit->text().toStdString());

    try {
        if (ssh_Address->text().toStdString() != "") {
            repoUrl = ssh_Address->text().toStdString();
        }
        gitPush(repoUrl, branchName, projectSourcePath);
        statusLabel->setText(QString::fromLocal8Bit("成功推送到 GitHub."));
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
    statusLabel->setText(QString::fromLocal8Bit("正在处理项目路径..."));
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
    statusLabel->setText(QString::fromLocal8Bit("正在执行命令: ") + QString::fromStdString(command));
    QCoreApplication::processEvents();
    int result = std::system(command.c_str());
    if (result != 0) {
        throw std::runtime_error("命令执行失败: " + command);
    }
}

void uploader::generateSSHKey(const std::string& keyPath) {
    statusLabel->setText(QString::fromLocal8Bit("正在生成 SSH 密钥..."));
    QCoreApplication::processEvents();
    bool ok;
    QString passphrase = QInputDialog::getText(this, tr("生成 SSH 密钥"),
        tr("未找到 SSH 密钥。请输入密码短语以生成新的 SSH 密钥:"), QLineEdit::Password, "", &ok);

    if (ok && !passphrase.isEmpty()) {
        std::string command = "ssh-keygen -t rsa -b 4096 -N \"" + passphrase.toStdString() + "\" -f " + keyPath;
        runCommand(command);
        statusLabel->setText(QString::fromLocal8Bit("SSH 密钥生成成功."));
        QCoreApplication::processEvents();
    }
    else {
        statusLabel->setText(QString::fromLocal8Bit("SSH 密钥生成取消."));
        QCoreApplication::processEvents();
    }
}

bool uploader::isGitRepository(const std::string& path) {
    statusLabel->setText(QString::fromLocal8Bit("正在检查 Git 仓库..."));
    QCoreApplication::processEvents();
    return fs::exists(path + "/.git");
}

void uploader::copyProjectFiles(const std::string& source, const std::string& destination) {
    try {
        statusLabel->setText(QString::fromLocal8Bit("正在复制项目文件..."));
        QCoreApplication::processEvents();
        // 获取源目录名称
        std::string sourceDirName = fs::path(source).filename().string();
        // 构造完整的目标路径
        std::string fullDestination = destination + "/" + sourceDirName;

        // 创建目标目录
        fs::create_directory(fullDestination);

        // 复制源目录内容到目标目录
        fs::copy(source, fullDestination, fs::copy_options::recursive | fs::copy_options::overwrite_existing);

        statusLabel->setText(QString::fromLocal8Bit("项目文件夹复制成功."));
        QCoreApplication::processEvents();
    }
    catch (const std::exception& e) {
        statusLabel->setText(QString::fromLocal8Bit("复制项目文件夹时出错: ") + QString::fromLocal8Bit(e.what()));
        QCoreApplication::processEvents();
    }
}

void uploader::gitPush(const std::string& repoUrl, const std::string& branchName, const std::string& projectSourcePath) {
    try {
        statusLabel->setText(QString::fromLocal8Bit("开始推送到 GitHub..."));
        QCoreApplication::processEvents();
        const char* homeEnv = std::getenv("HOME");
        std::string envHome;

        if (!homeEnv) {
            bool ok;
            QString homeDir = QInputDialog::getText(this, tr("输入主目录"),
                tr("请输入您的主目录 (例如, C:\\Users\\lms)"), QLineEdit::Normal, "", &ok);

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
            statusLabel->setText(QString::fromLocal8Bit("未找到 Git 仓库。正在克隆仓库..."));
            QCoreApplication::processEvents();
            runCommand("git clone " + repoUrl + " " + repoPath);
        }

        std::filesystem::current_path(repoPath);

        runCommand("git fetch origin");
        runCommand("git checkout " + branchName);
        runCommand("git pull origin " + branchName);

        int fetchResult = std::system("git fetch origin");
        if (fetchResult == 0) {
            statusLabel->setText(QString::fromLocal8Bit("分支已是最新，无需更新。"));
            QCoreApplication::processEvents();

            copyProjectFiles(projectSourcePath, repoPath);

            runCommand("git add .");
            runCommand("git commit -m \"自动提交\"");
            runCommand("git push origin " + branchName);

            statusLabel->setText(QString::fromLocal8Bit("更改已成功推送到 GitHub."));
            QCoreApplication::processEvents();
        }
    }
    catch (const std::exception& e) {
        statusLabel->setText(QString::fromLocal8Bit("错误: ") + QString::fromLocal8Bit(e.what()));
        QCoreApplication::processEvents();
    }
}

void uploader::outputSSHKey() {
    statusLabel->setText(QString::fromLocal8Bit("正在输出 SSH 公钥..."));
    QCoreApplication::processEvents();
    const char* homeEnv = std::getenv("HOME");
    std::string envHome;

    if (!homeEnv) {
        bool ok;
        QString homeDir = QInputDialog::getText(this, tr("输入主目录"),
            tr("请输入您的主目录 (例如, C:\\Users\\lms)"), QLineEdit::Normal, "", &ok);

        if (ok && !homeDir.isEmpty()) {
            envHome = homeDir.toStdString();
            homeEnv = envHome.c_str();
        }
    }

    std::string sshPubKeyPath = (fs::path(homeEnv) / ".ssh/id_rsa.pub").string();
    if (fs::exists(sshPubKeyPath)) {
        std::ifstream pubKeyFile(sshPubKeyPath);
        std::string pubKey((std::istreambuf_iterator<char>(pubKeyFile)), std::istreambuf_iterator<char>());

        statusLabel->setText(QString::fromLocal8Bit("请将以下公钥添加到您的 GitHub 账户进行身份验证:\n") + QString::fromLocal8Bit(pubKey.c_str()));
        QCoreApplication::processEvents();
    }
    else {
        statusLabel->setText(QString::fromLocal8Bit("未找到公钥文件: ") + QString::fromLocal8Bit(sshPubKeyPath.c_str()));
        QCoreApplication::processEvents();
    }
}
