#define _CRT_SECURE_NO_WARNINGS

#include "uploader.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <QInputDialog>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <chrono>
#include <ctime>

#include <windows.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include <vector>


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

        if (repoPath_->text().toStdString() != "") {
            repoPath = repoPath_->text().toStdString();
        }
        gitPush(repoUrl, branchName, projectSourcePath);
    }
    catch (const std::runtime_error& e) {
        statusLabel->setText(QString::fromLocal8Bit(e.what()));
        QCoreApplication::processEvents();
        logError(e.what());
        logError("sss");
        if (std::string(e.what()).find("Permission denied (publickey)") != std::string::npos) {
            outputSSHKey();
        }
        return; // �����һ��
    }
    statusLabel->setText(QString::fromLocal8Bit("�ɹ����͵� GitHub: ") + QString::fromStdString(repoUrl));
    QCoreApplication::processEvents();
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

    SECURITY_ATTRIBUTES saAttr;
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;

    HANDLE hStdOutRead, hStdOutWrite;
    if (!CreatePipe(&hStdOutRead, &hStdOutWrite, &saAttr, 0)) {
        std::string errorMsg = "StdoutRd CreatePipe failed";
        logError(errorMsg);
        throw std::runtime_error(errorMsg);
    }

    if (!SetHandleInformation(hStdOutRead, HANDLE_FLAG_INHERIT, 0)) {
        std::string errorMsg = "Stdout SetHandleInformation failed";
        logError(errorMsg);
        throw std::runtime_error(errorMsg);
    }

    PROCESS_INFORMATION piProcInfo;
    STARTUPINFOA siStartInfo;
    ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));
    ZeroMemory(&siStartInfo, sizeof(STARTUPINFOA));
    siStartInfo.cb = sizeof(STARTUPINFOA);
    siStartInfo.hStdError = hStdOutWrite;
    siStartInfo.hStdOutput = hStdOutWrite;
    siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

    std::vector<char> commandVec(command.begin(), command.end());
    commandVec.push_back('\0');
    if (!CreateProcessA(NULL, commandVec.data(), NULL, NULL, TRUE, 0, NULL, NULL, &siStartInfo, &piProcInfo)) {
        std::string errorMsg = "CreateProcess failed (" + std::to_string(GetLastError()) + ")";
        logError(errorMsg);
        throw std::runtime_error(errorMsg);
    }

    CloseHandle(hStdOutWrite);

    DWORD dwRead;
    CHAR chBuf[4096];
    std::string result;
    while (ReadFile(hStdOutRead, chBuf, sizeof(chBuf), &dwRead, NULL) && dwRead > 0) {
        result.append(chBuf, dwRead);
    }

    WaitForSingleObject(piProcInfo.hProcess, INFINITE);

    DWORD exitCode;
    if (!GetExitCodeProcess(piProcInfo.hProcess, &exitCode)) {
        std::string errorMsg = "GetExitCodeProcess failed";
        logError(errorMsg);
        throw std::runtime_error(errorMsg);
    }

    CloseHandle(piProcInfo.hProcess);
    CloseHandle(piProcInfo.hThread);
    CloseHandle(hStdOutRead);

    if (exitCode != 0) {
        std::string errorMsg = "command:  " + command + "\nerror:\n" + result;
        logError(errorMsg);
        throw std::runtime_error(errorMsg);
    }
    else {
        statusLabel->setText(QString::fromLocal8Bit("����ִ�гɹ�: ") + QString::fromStdString(command));
    }
}

void uploader::generateSSHKey(const std::string& keyPath) {
    statusLabel->setText(QString::fromLocal8Bit("�������� SSH ��Կ..."));
    QCoreApplication::processEvents();
    bool ok;
    QString passphrase = QInputDialog::getText(this, QString::fromLocal8Bit("���� SSH ��Կ"),
        QString::fromLocal8Bit("δ�ҵ� SSH ��Կ����������������������µ� SSH ��Կ:"), QLineEdit::Password, "", &ok);

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
        std::string sourceDirName = fs::path(source).filename().string();
        std::string fullDestination = destination + "/" + sourceDirName;

        fs::create_directory(fullDestination);
        fs::copy(source, fullDestination, fs::copy_options::recursive | fs::copy_options::overwrite_existing);

        statusLabel->setText(QString::fromLocal8Bit("��Ŀ�ļ��и��Ƴɹ�."));
        QCoreApplication::processEvents();
    }
    catch (const std::exception& e) {
        std::string errorMsg = "������Ŀ�ļ���ʱ����: " + std::string(e.what());
        statusLabel->setText(QString::fromLocal8Bit(errorMsg.c_str()));
        QCoreApplication::processEvents();
        logError(errorMsg);
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
            QString homeDir = QInputDialog::getText(this, QString::fromLocal8Bit("������Ŀ¼"),
                QString::fromLocal8Bit("������������Ŀ¼ (����, C:\\Users\\lms)"), QLineEdit::Normal, "", &ok);

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

        copyProjectFiles(projectSourcePath, repoPath);

        runCommand("git add .");
        runCommand("git commit -m \"�Զ��ύ\"");
        runCommand("git push origin " + branchName);

        statusLabel->setText(QString::fromLocal8Bit("�����ѳɹ����͵� GitHub."));
        QCoreApplication::processEvents();
    }
    catch (const std::runtime_error& e) {
        std::string errorMsg = "error: " + std::string(e.what());
        statusLabel->setText(QString::fromLocal8Bit(errorMsg.c_str()));
        QCoreApplication::processEvents();
        logError(errorMsg);
        if (std::string(e.what()).find("Permission denied (publickey)") != std::string::npos) {
            outputSSHKey();
        }
    }
}

void uploader::outputSSHKey() {
    statusLabel->setText(QString::fromLocal8Bit("������� SSH ��Կ..."));
    QCoreApplication::processEvents();
    const char* homeEnv = std::getenv("HOME");
    std::string envHome;

    if (!homeEnv) {
        bool ok;
        QString homeDir = QInputDialog::getText(this, QString::fromLocal8Bit("������Ŀ¼"),
            QString::fromLocal8Bit("������������Ŀ¼ (����, C:\\Users\\lms)"), QLineEdit::Normal, "", &ok);

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

        // ʹ��QInputDialog����ʾ��Կ��Ϣ��������
        bool ok;
        QString inputText = QInputDialog::getMultiLineText(this, QString::fromLocal8Bit("��Կ��Ϣ"),
            QString::fromLocal8Bit("�뽫���¹�Կ��ӵ����� GitHub �˻����������֤:\n"),
            QString::fromLocal8Bit(pubKey.c_str()), &ok);
    }
    else {
        std::string errorMsg = "δ�ҵ���Կ�ļ�: " + sshPubKeyPath;
        statusLabel->setText(QString::fromLocal8Bit(errorMsg.c_str()));
        QCoreApplication::processEvents();
        logError(errorMsg);
    }
}



void uploader::logError(const std::string& errorMsg) {
    QFile file("error_log.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        auto now = std::chrono::system_clock::now();
        auto now_time = std::chrono::system_clock::to_time_t(now);
        out << "[" << QString::fromStdString(std::ctime(&now_time)).trimmed() << "] " << QString::fromStdString(errorMsg) << "\n";
        file.close();
    }
}
