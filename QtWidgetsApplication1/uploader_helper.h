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
        throw std::runtime_error("����ִ��ʧ��: " + command);
    }
}

void generate_ssh_key(const std::string& key_path) {
    std::string passphrase;
    std::cout << "δ�ҵ�SSH��Կ��������һ����������������µ�SSH��Կ: ";
    std::getline(std::cin, passphrase);

    std::string command = "ssh-keygen -t rsa -b 4096 -N \"" + passphrase + "\" -f " + key_path;
    run_command(command);

    std::cout << "SSH��Կ���ɳɹ���" << std::endl;
}

bool is_git_repository(const std::string& path) {
    return fs::exists(path + "/.git");
}

void copy_project_files(const std::string& source, const std::string& destination) {
    try {
        fs::copy(source, destination, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
        std::cout << "��Ŀ�ļ��и��Ƴɹ���" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "������Ŀ�ļ���ʱ����: " << e.what() << std::endl;
    }
}

void output_ssh_key() {
    char* home_env = nullptr;
    size_t len = 0;

    if (_dupenv_s(&home_env, &len, "HOME") != 0 || home_env == nullptr) {
        std::string envHome;
        std::cout << "������homeĿ¼ �����ƣ�C:\\Users\\lms��";
        std::getline(std::cin, envHome);
        home_env = _strdup(envHome.c_str());
    }

    std::string ssh_pub_key_path = (fs::path(home_env) / ".ssh/id_rsa.pub").string();
    if (fs::exists(ssh_pub_key_path)) {
        std::ifstream pub_key_file(ssh_pub_key_path);
        std::string pub_key((std::istreambuf_iterator<char>(pub_key_file)), std::istreambuf_iterator<char>());
        std::cout << "�뽫���¹�Կ��ӵ�����GitHub�˻����Խ��������֤: " << std::endl;
        std::cout << pub_key << std::endl;
    }
    else {
        std::cerr << "δ�ҵ���Կ�ļ�: " << ssh_pub_key_path << std::endl;
    }

    free(home_env); // �ͷŷ�����ڴ�
}

void git_push(const std::string& repo_url, const std::string& branch_name, const std::string& project_source_path) {
    try {
        char* home_env = nullptr;
        size_t len = 0;

        if (_dupenv_s(&home_env, &len, "HOME") != 0 || home_env == nullptr) {
            std::string envHome;
            std::cout << "������homeĿ¼ �����ƣ�C:\\Users\\lms��";
            std::getline(std::cin, envHome);
            home_env = _strdup(envHome.c_str());
        }

        std::string ssh_key_path = (fs::path(home_env) / ".ssh/id_rsa").string();
        if (!fs::exists(ssh_key_path)) {
            generate_ssh_key(ssh_key_path);
        }

        std::string repo_path = "C:\\Users\\lms\\Desktop\\ll";

        // ���Ŀ¼�Ƿ�Ϊgit�ֿ�
        if (!is_git_repository(repo_path)) {
            std::cout << "δ�ҵ�git�ֿ⡣���ڿ�¡�ֿ�..." << std::endl;
            run_command("git clone " + repo_url + " " + repo_path);
        }

        // �л����ֿ�Ŀ¼
        std::filesystem::current_path(repo_path);

        // ��ȡ���¸��Ĳ����ָ����֧
        run_command("git fetch origin");
        run_command("git checkout " + branch_name);
        run_command("git pull origin " + branch_name);

        // ������Ŀ�ļ��м�����������ļ�����Ŀ¼
        copy_project_files(project_source_path, repo_path);

        // ������и��ĵ��ֿ�
        run_command("git add .");

        // �ύ����
        run_command("git commit -m \"�Զ��ύ\"");

        // ���͸��ĵ��ֿ�
        run_command("git push origin " + branch_name);

        std::cout << "�����ѳɹ����͵�GitHub��" << std::endl;

        free(home_env); // �ͷŷ�����ڴ�
    }
    catch (const std::exception& e) {
        std::cerr << "����: " << e.what() << std::endl;
        if (std::string(e.what()).find("Permission denied (publickey)") != std::string::npos) {
            output_ssh_key();
        }
    }
}
#endif