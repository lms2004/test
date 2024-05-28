#ifndef AUTHENTICATION_SERVICE_H
#define AUTHENTICATION_SERVICE_H
#include <iostream>
#include <unordered_map>
#include <mysql.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>

class AuthenticationService {
public:
    AuthenticationService();
    ~AuthenticationService();
    bool login(const std::string& username, const std::string& password);
    bool registerUser(const std::string& username, const std::string& password);
    bool changePassword(const std::string& username, const std::string& oldPassword, const std::string& newPassword);

private:
    std::unordered_map<std::string, std::string> users;
    void loadUsersFromDB();
    void saveUsersToDB();
    std::string hashPassword(const std::string& password);
    MYSQL* connectDB();
    void checkAndCreateDatabase();
    char database_password[20] = "123456";
};
#endif // AUTHENTICATION_SERVICE_H