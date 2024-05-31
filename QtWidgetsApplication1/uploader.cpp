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

std::string convertToBackSlash(const std::string& path) {
    std::string result = path;
    for (char& c : result) {
        if (c == '/') {
            c = '\\';
        }
    }
    return "\"" + result + "\"";
}

std::string string_To_UTF8(const std::string& str)
{
    int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

    wchar_t* pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴
    ZeroMemory(pwBuf, nwLen * 2 + 2);

    ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

    int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

    char* pBuf = new char[nLen + 1];
    ZeroMemory(pBuf, nLen + 1);

    ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

    std::string retStr(pBuf);

    delete[]pwBuf;
    delete[]pBuf;

    pwBuf = NULL;
    pBuf = NULL;

    return retStr;
}

void copyDirectory(const fs::path& source, const fs::path& destination) {
    try {
        // 检查源目录是否存在并且是一个目录
        std::cout << "检查源目录是否存在: " << source << std::endl;
        if (fs::exists(source) && fs::is_directory(source)) {
            std::cout << "源目录存在且是一个目录: " << source << std::endl;

            // 创建目标目录
            if (!fs::exists(destination)) {
                std::cout << "目标目录不存在，正在创建: " << destination << std::endl;
                fs::create_directory(destination);
            }
            else {
                std::cout << "目标目录已存在: " << destination << std::endl;
            }

            // 递归遍历源目录
            for (const auto& entry : fs::recursive_directory_iterator(source)) {
                const auto& path = entry.path();
                auto relativePathStr = path.lexically_relative(source);
                fs::path targetPath = destination / relativePathStr;

                // 如果是目录则创建目录
                if (fs::is_directory(path)) {
                    std::cout << "创建目录: " << targetPath << std::endl;
                    fs::create_directory(targetPath);
                }
                // 如果是文件则复制文件
                else if (fs::is_regular_file(path)) {
                    std::cout << "复制文件: " << path << " 到 " << targetPath << std::endl;
                    fs::copy(path, targetPath);
                }
                // 跳过非常规文件
                else {
                    std::cerr << "跳过非常规文件: " << path << std::endl;
                }
            }
        }
        else {
            std::cerr << "源目录不存在或不是目录。" << std::endl;
        }
    }
    catch (fs::filesystem_error& e) {
        std::cerr << "文件系统错误: " << e.what() << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "一般错误: " << e.what() << std::endl;
    }
}



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

    // 原始路径
    std::string projectSourcePath = projectPathLineEdit->text().toLocal8Bit().data();

    try {
        if (ssh_Address->text().toStdString() != "") {
            repoUrl = ssh_Address->text().toStdString();
        }

        if (repoPath_->text().toStdString() != "") {
            repoPath = repoPath_->text().toLocal8Bit().data();
        }
        gitPush(repoUrl, branchName, projectSourcePath);
 /*       statusLabel->setText(QString::fromLocal8Bit("成功推送到 GitHub: ") + QString::fromStdString(repoUrl));*/
        QCoreApplication::processEvents();
    }
    catch (const std::runtime_error& e) {
        statusLabel->setText(QString::fromLocal8Bit(e.what()));
        QCoreApplication::processEvents();
        logError(e.what());
        if (std::string(e.what()).find("Permission denied (publickey)") != std::string::npos) {
            outputSSHKey(projectSourcePath);
        }
        return; // 添加这一行
    }
}

void uploader::runCommand(const std::string& command) {
    statusLabel->setText(QString::fromLocal8Bit("正在执行命令:\n ") + QString::fromStdString(command));
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
        statusLabel->setText(QString::fromLocal8Bit("命令执行成功: ") + QString::fromStdString(command));
    }
}

void uploader::generateSSHKey(const std::string& keyPath) {
    statusLabel->setText(QString::fromLocal8Bit("正在生成 SSH 密钥..."));
    QCoreApplication::processEvents();

    bool ok;
    QString passphrase = QInputDialog::getText(this, QString::fromLocal8Bit("生成 SSH 密钥"),
        QString::fromLocal8Bit("未找到 SSH 密钥。请输入密码短语以生成新的 SSH 密钥:"), QLineEdit::Password, "", &ok);

    if (ok && !passphrase.isEmpty()) {
        // 构建命令行，适应Windows环境       
        std::string command = "ssh-keygen -t rsa -f \"" + keyPath + "\" -N \"\"";

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

        std::string sourceDirName = fs::u8path(string_To_UTF8(source)).filename().string();
        std::string fullDestination = destination + "/" + sourceDirName;


        // Create a filesystem path using the UTF-8 encoded source path
        fs::path sourcePath = fs::u8path(string_To_UTF8(source));

        fs::path destinationPath = fs::u8path(string_To_UTF8(fullDestination)); // 使用UTF-8编码的路径

        
        copyDirectory(sourcePath, destinationPath);
        statusLabel->setText(QString::fromLocal8Bit("项目文件夹复制成功."));

        QCoreApplication::processEvents();
    }
    catch (const std::exception& e) {
        std::string errorMsg = "复制项目文件夹时出错: " + std::string(e.what());
        statusLabel->setText(QString::fromLocal8Bit(errorMsg.c_str()));
        QCoreApplication::processEvents();
        logError(errorMsg);
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
            QString homeDir = QInputDialog::getText(this, QString::fromLocal8Bit("输入主目录"),
                QString::fromLocal8Bit("请输入您的主目录 (例如, C:\\Users\\lms)"), QLineEdit::Normal, "", &ok);

            if (ok && !homeDir.isEmpty()) {
                envHome = homeDir.toStdString();
                homeEnv = envHome.c_str();
            }
        }
        
        fs::path destinationPath = fs::u8path(string_To_UTF8(homeEnv)); // 使用UTF-8编码的路径
        std::string sshKeyPath = (destinationPath / ".ssh" / "id_rsa").string();
        std::string sshDir = (destinationPath / ".ssh").string();

        if (!fs::exists(sshKeyPath)) {
            generateSSHKey(sshKeyPath);
        }

        if (!isGitRepository(repoPath)) {
            statusLabel->setText(QString::fromLocal8Bit("未找到 Git 仓库。正在克隆仓库..."));
            QCoreApplication::processEvents();

            runCommand("git clone " + repoUrl + " \"" + repoPath + "\"");
        }

        std::filesystem::current_path(repoPath);

        runCommand("git fetch origin");
        runCommand("git checkout " + branchName);
        runCommand("git pull origin " + branchName);

        copyProjectFiles(projectSourcePath, repoPath);

        runCommand("git add .");
        runCommand("git commit -m \"自动提交\"");
        runCommand("git push origin " + branchName);

        statusLabel->setText(QString::fromLocal8Bit("更改已成功推送到 GitHub."));
        QCoreApplication::processEvents();
    }
    catch (const std::runtime_error& e) {
        std::string errorMsg = "error: " + std::string(e.what());
        statusLabel->setText(QString::fromLocal8Bit(errorMsg.c_str()));
        QCoreApplication::processEvents();
        logError(errorMsg);
        if (std::string(e.what()).find("Permission denied (publickey)") != std::string::npos) {
            outputSSHKey(projectSourcePath);
        }
    }
}

void uploader::outputSSHKey(std::string ssh) {
    statusLabel->setText(QString::fromLocal8Bit("正在输出 SSH 公钥..."));
    QCoreApplication::processEvents();
    const char* homeEnv = std::getenv("HOME");
    std::string envHome;

    if (!homeEnv) {
        bool ok;
        QString homeDir = QInputDialog::getText(this, QString::fromLocal8Bit("输入主目录"),
            QString::fromLocal8Bit("请输入您的主目录 (例如, C:\\Users\\lms)"), QLineEdit::Normal, "", &ok);

        if (ok && !homeDir.isEmpty()) {
            envHome = homeDir.toStdString();
            homeEnv = envHome.c_str();
        }
    }

    fs::path destinationPath = fs::u8path(string_To_UTF8(homeEnv)); // 使用UTF-8编码的路径

    std::string sshPubKeyPath = (destinationPath / ".ssh" / "id_rsa.pub").string();

    if (fs::exists(sshPubKeyPath)) {
        std::ifstream pubKeyFile(sshPubKeyPath);
        std::string pubKey((std::istreambuf_iterator<char>(pubKeyFile)), std::istreambuf_iterator<char>());

        statusLabel->setText(QString::fromLocal8Bit("请将以下公钥添加到您的 GitHub 账户进行身份验证:\n") + QString::fromLocal8Bit(pubKey.c_str()));
        QCoreApplication::processEvents();

        // 使用QInputDialog来显示公钥信息并允许复制
        bool ok;
        QString inputText = QInputDialog::getMultiLineText(this, QString::fromLocal8Bit("公钥信息"),
            QString::fromLocal8Bit("请将以下公钥添加到您的 GitHub 账户进行身份验证:\n"),
            QString::fromLocal8Bit(pubKey.c_str()), &ok);
    }
    else {
        std::string errorMsg = "未找到公钥文件: " + sshPubKeyPath;
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
