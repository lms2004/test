#define _CRT_SECURE_NO_WARNINGS

#include "uploader.h"
#include <fstream>
#include <cstdlib>
#include <iostream>

uploader::uploader(QWidget* parent)
    : QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel* label = new QLabel("��������ĿԴ·��:", this);
    mainLayout->addWidget(label);

    projectPathLineEdit = new QLineEdit(this);
    mainLayout->addWidget(projectPathLineEdit);

    QHBoxLayout* buttonLayout = new QHBoxLayout();

    QPushButton* browseButton = new QPushButton("���...", this);
    connect(browseButton, &QPushButton::clicked, this, &uploader::onBrowseButtonClicked);
    buttonLayout->addWidget(browseButton);

    QPushButton* pushButton = new QPushButton("���͵�GitHub", this);
    connect(pushButton, &QPushButton::clicked, this, &uploader::onPushButtonClicked);
    buttonLayout->addWidget(pushButton);

    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

void uploader::onBrowseButtonClicked() {
    QString dir = QFileDialog::getExistingDirectory(this, "ѡ����ĿԴ·��", "");
    if (!dir.isEmpty()) {
        projectPathLineEdit->setText(dir);
    }
}

void uploader::onPushButtonClicked() {
    std::string repoUrl = "git@github.com:lms2004/test.git";
    std::string branchName = "main";
    std::string projectSourcePath = makeLegalPath(projectPathLineEdit->text().toStdString());

    try {
        gitPush(repoUrl, branchName, projectSourcePath);
        QMessageBox::information(this, "�ɹ�", "�����ѳɹ����͵�GitHub��");
    }
    catch (const std::runtime_error& e) {
        QMessageBox::critical(this, "����", e.what());
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
    std::string passphrase;
    std::cout << "δ�ҵ�SSH��Կ��������һ����������������µ�SSH��Կ: ";
    std::getline(std::cin, passphrase);

    std::string command = "ssh-keygen -t rsa -b 4096 -N \"" + passphrase + "\" -f " + keyPath;
    runCommand(command);

    std::cout << "SSH��Կ���ɳɹ���" << std::endl;
}

bool uploader::isGitRepository(const std::string& path) {
    return fs::exists(path + "/.git");
}

void uploader::copyProjectFiles(const std::string& source, const std::string& destination) {
    try {
        fs::copy(source, destination, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
        std::cout << "��Ŀ�ļ��и��Ƴɹ���" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "������Ŀ�ļ���ʱ����: " << e.what() << std::endl;
    }
}

void uploader::gitPush(const std::string& repoUrl, const std::string& branchName, const std::string& projectSourcePath) {
    try {
        const char* homeEnv = std::getenv("HOME");
        std::string envHome;

        if (!homeEnv) {
            std::cout << "������homeĿ¼ �����ƣ�C:\\Users\\lms��";
            std::getline(std::cin, envHome);
            homeEnv = envHome.c_str();
        }

        std::string sshKeyPath = (fs::path(homeEnv) / ".ssh/id_rsa").string();
        if (!fs::exists(sshKeyPath)) {
            generateSSHKey(sshKeyPath);
        }

        std::string repoPath = "C:\\Users\\lms\\Desktop\\ll";

        if (!isGitRepository(repoPath)) {
            std::cout << "δ�ҵ�git�ֿ⡣���ڿ�¡�ֿ�..." << std::endl;
            runCommand("git clone " + repoUrl + " " + repoPath);
        }

        std::filesystem::current_path(repoPath);

        runCommand("git fetch origin");
        runCommand("git checkout " + branchName);
        runCommand("git pull origin " + branchName);

        int fetchResult = std::system("git fetch origin");
        if (fetchResult == 0) {
            std::cout << "��֧�������£�������¡�" << std::endl;

            copyProjectFiles(projectSourcePath, repoPath);

            runCommand("git add .");
            runCommand("git commit -m \"�Զ��ύ\"");
            runCommand("git push origin " + branchName);

            std::cout << "�����ѳɹ����͵�GitHub��" << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "����: " << e.what() << std::endl;
    }
}

void uploader::outputSSHKey() {
    const char* homeEnv = std::getenv("HOME");
    std::string envHome;

    if (!homeEnv) {
        std::cout << "������homeĿ¼ �����ƣ�C:\\Users\\lms��";
        std::getline(std::cin, envHome);
        homeEnv = envHome.c_str();
    }

    std::string sshPubKeyPath = (fs::path(homeEnv) / ".ssh/id_rsa.pub").string();
    if (fs::exists(sshPubKeyPath)) {
        std::ifstream pubKeyFile(sshPubKeyPath);
        std::string pubKey((std::istreambuf_iterator<char>(pubKeyFile)), std::istreambuf_iterator<char>());
        std::cout << "�뽫���¹�Կ��ӵ�����GitHub�˻����Խ��������֤: " << std::endl;
        std::cout << pubKey << std::endl;
    }
    else {
        std::cerr << "δ�ҵ���Կ�ļ�: " << sshPubKeyPath << std::endl;
    }
}
