#define _CRT_SECURE_NO_WARNINGS

#include "uploader.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <QInputDialog>

uploader::uploader(QWidget* parent)
    : QWidget(parent), ui(new Ui::uploader) {
    ui->setupUi(this);
    projectPathLineEdit = ui->projectPathLineEdit;
    statusLabel = ui->statusLabel; // Assuming statusLabel is the name of your QLabel
}


void uploader::on_browseButton_clicked() {
    QString dir = QFileDialog::getExistingDirectory(this, "ѡ����ĿԴ·��", "");
    if (!dir.isEmpty()) {
        projectPathLineEdit->setText(dir);
    }
}

void uploader::on_pushButton_clicked() {
    std::string repoUrl = "git@github.com:lms2004/test.git";
    std::string branchName = "main";
    std::string projectSourcePath = makeLegalPath(projectPathLineEdit->text().toStdString());

    try {
        gitPush(repoUrl, branchName, projectSourcePath);
        statusLabel->setText(QString::fromLocal8Bit("�ɹ����͵� GitHub."));
    }
    catch (const std::runtime_error& e) {
        statusLabel->setText(QString::fromLocal8Bit(e.what()));
        if (std::string(e.what()).find("Permission denied (publickey)") != std::string::npos) {
            outputSSHKey();
        }
    }
}

std::string uploader::makeLegalPath(const std::string& path) {
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
    int result = std::system(command.c_str());
    if (result != 0) {
        throw std::runtime_error("����ִ��ʧ��: " + command);
    }
}

void uploader::generateSSHKey(const std::string& keyPath) {
    bool ok;
    QString passphrase = QInputDialog::getText(this, tr("���� SSH ��Կ"),
        tr("δ�ҵ� SSH ��Կ����������������������µ� SSH ��Կ:"), QLineEdit::Password, "", &ok);

    if (ok && !passphrase.isEmpty()) {
        std::string command = "ssh-keygen -t rsa -b 4096 -N \"" + passphrase.toStdString() + "\" -f " + keyPath;
        runCommand(command);
        statusLabel->setText(QString::fromLocal8Bit("SSH ��Կ���ɳɹ�."));
    }
}

bool uploader::isGitRepository(const std::string& path) {
    return fs::exists(path + "/.git");
}

void uploader::copyProjectFiles(const std::string& source, const std::string& destination) {
    try {
        fs::copy(source, destination, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
        statusLabel->setText(QString::fromLocal8Bit("��Ŀ�ļ��и��Ƴɹ�."));
    }
    catch (const std::exception& e) {
        statusLabel->setText(QString::fromLocal8Bit("������Ŀ�ļ���ʱ����: ") + QString::fromLocal8Bit(e.what()));
    }
}

void uploader::gitPush(const std::string& repoUrl, const std::string& branchName, const std::string& projectSourcePath) {
    try {
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

        std::string repoPath = "C:\\Users\\lms\\Desktop\\ll";

        if (!isGitRepository(repoPath)) {
            statusLabel->setText(QString::fromLocal8Bit("δ�ҵ� Git �ֿ⡣���ڿ�¡�ֿ�..."));
            runCommand("git clone " + repoUrl + " " + repoPath);
        }

        std::filesystem::current_path(repoPath);

        runCommand("git fetch origin");
        runCommand("git checkout " + branchName);
        runCommand("git pull origin " + branchName);

        int fetchResult = std::system("git fetch origin");
        if (fetchResult == 0) {
            statusLabel->setText(QString::fromLocal8Bit("��֧�������£�������¡�"));

            copyProjectFiles(projectSourcePath, repoPath);

            runCommand("git add .");
            runCommand("git commit -m \"�Զ��ύ\"");
            runCommand("git push origin " + branchName);

            statusLabel->setText(QString::fromLocal8Bit("�����ѳɹ����͵� GitHub."));
        }
    }
    catch (const std::exception& e) {
        statusLabel->setText(QString::fromLocal8Bit("����: ") + QString::fromLocal8Bit(e.what()));
    }
}

void uploader::outputSSHKey() {
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
    }
    else {
        statusLabel->setText(QString::fromLocal8Bit("δ�ҵ���Կ�ļ�: ") + QString::fromLocal8Bit(sshPubKeyPath.c_str()));
    }
}
