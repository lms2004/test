#ifndef  _UPLOADER_HELPER_
#define _UPLOADER_HELPER_

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <QString>

namespace fs = std::filesystem;

std::string make_legal_path(const std::string& path) {
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

void run_command(const std::string& command) {
    int result = std::system(command.c_str());
    if (result != 0) {
        throw std::runtime_error("命令执行失败: " + command);
    }
}

void generate_ssh_key(const std::string& key_path) {
    std::string passphrase;
    std::cout << "未找到SSH密钥。请输入一个密码短语以生成新的SSH密钥: ";
    std::getline(std::cin, passphrase);

    std::string command = "ssh-keygen -t rsa -b 4096 -N \"" + passphrase + "\" -f " + key_path;
    run_command(command);

    std::cout << "SSH密钥生成成功。" << std::endl;
}

bool is_git_repository(const std::string& path) {
    return fs::exists(path + "/.git");
}

void copy_project_files(const std::string& source, const std::string& destination) {
    try {
        fs::copy(source, destination, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
        std::cout << "项目文件夹复制成功。" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "复制项目文件夹时出错: " << e.what() << std::endl;
    }
}

void output_ssh_key() {
    char* home_env = nullptr;
    size_t len = 0;

    if (_dupenv_s(&home_env, &len, "HOME") != 0 || home_env == nullptr) {
        std::string envHome;
        std::cout << "输出你的home目录 （类似：C:\\Users\\lms）";
        std::getline(std::cin, envHome);
        home_env = _strdup(envHome.c_str());
    }

    std::string ssh_pub_key_path = (fs::path(home_env) / ".ssh/id_rsa.pub").string();
    if (fs::exists(ssh_pub_key_path)) {
        std::ifstream pub_key_file(ssh_pub_key_path);
        std::string pub_key((std::istreambuf_iterator<char>(pub_key_file)), std::istreambuf_iterator<char>());
        std::cout << "请将以下公钥添加到您的GitHub账户中以进行身份验证: " << std::endl;
        std::cout << pub_key << std::endl;
    }
    else {
        std::cerr << "未找到公钥文件: " << ssh_pub_key_path << std::endl;
    }

    free(home_env); // 释放分配的内存
}

void git_push(const std::string& repo_url, const std::string& branch_name, const std::string& project_source_path) {
    try {
        char* home_env = nullptr;
        size_t len = 0;

        if (_dupenv_s(&home_env, &len, "HOME") != 0 || home_env == nullptr) {
            std::string envHome;
            std::cout << "输出你的home目录 （类似：C:\\Users\\lms）";
            std::getline(std::cin, envHome);
            home_env = _strdup(envHome.c_str());
        }

        std::string ssh_key_path = (fs::path(home_env) / ".ssh/id_rsa").string();
        if (!fs::exists(ssh_key_path)) {
            generate_ssh_key(ssh_key_path);
        }

        std::string repo_path = "C:\\Users\\lms\\Desktop\\ll";

        // 检查目录是否为git仓库
        if (!is_git_repository(repo_path)) {
            std::cout << "未找到git仓库。正在克隆仓库..." << std::endl;
            run_command("git clone " + repo_url + " " + repo_path);
        }

        // 切换到仓库目录
        std::filesystem::current_path(repo_path);

        // 获取最新更改并检出指定分支
        run_command("git fetch origin");
        run_command("git checkout " + branch_name);
        run_command("git pull origin " + branch_name);

        // 复制项目文件夹及其包含的子文件和子目录
        copy_project_files(project_source_path, repo_path);

        // 添加所有更改到仓库
        run_command("git add .");

        // 提交更改
        run_command("git commit -m \"自动提交\"");

        // 推送更改到仓库
        run_command("git push origin " + branch_name);

        std::cout << "更改已成功推送到GitHub。" << std::endl;

        free(home_env); // 释放分配的内存
    }
    catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
        if (std::string(e.what()).find("Permission denied (publickey)") != std::string::npos) {
            output_ssh_key();
        }
    }
}
#endif