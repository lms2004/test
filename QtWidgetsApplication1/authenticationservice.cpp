#include "authenticationservice.h"

AuthenticationService::AuthenticationService() {
    checkAndCreateDatabase();
    loadUsersFromDB();
}

AuthenticationService::~AuthenticationService() {
    saveUsersToDB();
}

void AuthenticationService::checkAndCreateDatabase() {
    MYSQL* conn = mysql_init(nullptr);
    if (!mysql_real_connect(conn, "127.0.0.1", "root", database_password, nullptr, 3306, nullptr, 0)) {
        std::cerr << "Error: Unable to connect to the database." << std::endl;
        return;
    }
    if (mysql_query(conn, "CREATE DATABASE IF NOT EXISTS user_db")) {
        std::cerr << "Error: Unable to create the database." << std::endl;
    }
    else {
        std::cerr << "Database created successfully." << std::endl;
    }
    mysql_close(conn);

    // 创建 users 表
    conn = mysql_init(nullptr);
    if (!mysql_real_connect(conn, "127.0.0.1", "root", database_password, "user_db", 3306, nullptr, 0)) {
        std::cerr << "Error: Unable to connect to the database." << std::endl;
        return;
    }
    if (mysql_query(conn, "CREATE TABLE IF NOT EXISTS users (username VARCHAR(20) PRIMARY KEY, hashed_password VARCHAR(255), salt VARCHAR(255));")) {
        std::cerr << "Error: Unable to create the users table." << std::endl;
    }
    else {
        std::cerr << "Users table created successfully." << std::endl;
    }
    mysql_close(conn);
}


void AuthenticationService::loadUsersFromDB() {
    MYSQL* conn = connectDB();
    if (!conn) return;
    if (mysql_query(conn, "SELECT username, hashed_password, salt FROM users;")) {
        std::cerr << "Error: Unable to query the database." << std::endl;
        return;
    }
    MYSQL_RES* res = mysql_store_result(conn);
    if (res) {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            users[row[0]] = std::string(row[1]) + ":" + std::string(row[2]);
        }
        mysql_free_result(res);
    }
    mysql_close(conn);
}

void AuthenticationService::saveUsersToDB() {
    MYSQL* conn = connectDB();
    if (!conn) return;
    mysql_query(conn, "DELETE FROM users;");
    for (const auto& pair : users) {
        size_t delimiterPos = pair.second.find(':');
        std::string hashedPassword = pair.second.substr(0, delimiterPos);
        std::string salt = pair.second.substr(delimiterPos + 1);
        std::string query = "INSERT INTO users (username, hashed_password, salt) VALUES ('" + pair.first + "', '" + hashedPassword + "', '" + salt + "');";
        mysql_query(conn, query.c_str());
    }
    mysql_close(conn);
}

bool AuthenticationService::login(const std::string& username, const std::string& password) {
    auto it = users.find(username);
    if (it == users.end()) {
        std::cout << "用户不存在\\n";
        return false;
    }
    std::string hashedPasswordWithSalt = it->second;
    size_t delimiterPos = hashedPasswordWithSalt.find(':');
    if (delimiterPos == std::string::npos) {
        std::cout << "无效的哈希格式\\n";
        return false;
    }
    std::string hashedPassword = hashedPasswordWithSalt.substr(0, delimiterPos);
    std::string saltString = hashedPasswordWithSalt.substr(delimiterPos + 1);
    unsigned char salt[SHA256_DIGEST_LENGTH];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        std::string byteString = saltString.substr(i * 2, 2);
        salt[i] = (unsigned char)strtol(byteString.c_str(), nullptr, 16);
    }
    unsigned char hash[SHA256_DIGEST_LENGTH];
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    EVP_DigestInit(ctx, EVP_sha256());
    EVP_DigestUpdate(ctx, (const unsigned char*)password.c_str(), password.length());
    EVP_DigestUpdate(ctx, salt, sizeof(salt));
    EVP_DigestFinal(ctx, hash, nullptr);
    EVP_MD_CTX_free(ctx);
    std::string computedHashedPassword;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        char buf[3];
        sprintf_s(buf, "%02x", hash[i]);
        computedHashedPassword += buf;
    }
    std::cout << "computedHashedPassword: " << computedHashedPassword << "\\n";
    std::cout << "stored hashedPassword: " << hashedPassword << "\\n";
    return computedHashedPassword == hashedPassword;
}

bool AuthenticationService::registerUser(const std::string& username, const std::string& password) {
    if (users.find(username) == users.end()) {
        std::string hashedPassword = hashPassword(password);
        users[username] = hashedPassword;
        MYSQL* conn = connectDB();
        if (!conn) return false;
        size_t delimiterPos = hashedPassword.find(':');
        std::string hashed = hashedPassword.substr(0, delimiterPos);
        std::string salt = hashedPassword.substr(delimiterPos + 1);
        std::string query = "INSERT INTO users (username, hashed_password, salt) VALUES ('" + username + "', '" + hashed + "', '" + salt + "');";
        if (mysql_query(conn, query.c_str()) != 0) {
            std::cerr << "插入数据失败: " << mysql_error(conn) << std::endl;
            mysql_close(conn);
            return false;
        }
        mysql_close(conn);
        return true;
    }
    return false;
}

bool AuthenticationService::changePassword(const std::string& username, const std::string& oldPassword, const std::string& newPassword) {
    auto it = users.find(username);
    if (it == users.end()) {
        std::cout << "用户不存在" << std::endl;
        return false;
    }
    std::string hashedPasswordWithSalt = it->second;
    size_t delimiterPos = hashedPasswordWithSalt.find(':');
    if (delimiterPos == std::string::npos) {
        std::cout << "无效的哈希模式" << std::endl;
        return false;
    }
    std::string hashedPassword = hashedPasswordWithSalt.substr(0, delimiterPos);
    std::string saltString = hashedPasswordWithSalt.substr(delimiterPos + 1);
    unsigned char salt[SHA256_DIGEST_LENGTH];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        std::string byteString = saltString.substr(i * 2, 2);
        salt[i] = (unsigned char)strtol(byteString.c_str(), nullptr, 16);
    }
    unsigned char hash[SHA256_DIGEST_LENGTH];
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    EVP_DigestInit(ctx, EVP_sha256());
    EVP_DigestUpdate(ctx, (const unsigned char*)oldPassword.c_str(), oldPassword.length());
    EVP_DigestUpdate(ctx, salt, sizeof(salt));
    EVP_DigestFinal(ctx, hash, nullptr);
    EVP_MD_CTX_free(ctx);
    std::string computedHashedPassword;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        char buf[3];
        sprintf_s(buf, "%02x", hash[i]);
        computedHashedPassword += buf;
    }
    if (computedHashedPassword == hashedPassword) {
        std::string newHashedPassword = hashPassword(newPassword);
        users[username] = newHashedPassword;
        MYSQL* conn = connectDB();
        if (!conn) return false;
        size_t delimiterPos = newHashedPassword.find(':');
        std::string newHashed = newHashedPassword.substr(0, delimiterPos);
        std::string newSalt = newHashedPassword.substr(delimiterPos + 1);
        std::string query = "UPDATE users SET hashed_password = '" + newHashed + "', salt = '" + newSalt + "' WHERE username = '" + username + "';";
        if (mysql_query(conn, query.c_str()) != 0) {
            std::cerr << "更新密码失败: " << mysql_error(conn) << std::endl;
            mysql_close(conn);
            return false;
        }
        mysql_close(conn);
        return true;
    }
    return false;
}



std::string AuthenticationService::hashPassword(const std::string& password) {
    unsigned char salt[SHA256_DIGEST_LENGTH];
    RAND_bytes(salt, sizeof(salt));
    unsigned char hash[SHA256_DIGEST_LENGTH];
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    EVP_DigestInit(ctx, EVP_sha256());
    EVP_DigestUpdate(ctx, (const unsigned char*)password.c_str(), password.length());
    EVP_DigestUpdate(ctx, salt, sizeof(salt));
    EVP_DigestFinal(ctx, hash, nullptr);
    EVP_MD_CTX_free(ctx);
    std::string hashedPassword;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        char buf[3];
        sprintf_s(buf, "%02x", hash[i]);
        hashedPassword += buf;
    }
    std::string saltString;
    for (int i = 0; i < sizeof(salt); i++) {
        char buf[3];
        sprintf_s(buf, "%02x", salt[i]);
        saltString += buf;
    }
    std::string hashedPasswordWithSalt = hashedPassword + ":" + saltString;
    std::cout << "hashedPassword: " << hashedPasswordWithSalt << "\\n";
    return hashedPasswordWithSalt;
}

MYSQL* AuthenticationService::connectDB() {
    MYSQL* conn = mysql_init(nullptr);
    if (!mysql_real_connect(conn, "127.0.0.1", "root", database_password, "user_db", 3306, nullptr, 0)) {
        std::cerr << "Error: Unable to connect to the database." << std::endl;
        return nullptr;
    }
    return conn;
}