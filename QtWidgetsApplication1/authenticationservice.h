#ifndef AUTHENTICATIONSERVICE_H
#define AUTHENTICATIONSERVICE_H

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
    bool registerUser(const std::string& username, const std::string& password);
    bool login(const std::string& username, const std::string& password);
    std::string hashPassword(const std::string& password);

private:
    std::unordered_map<std::string, std::string> users;
    const unsigned char salt[50] = "Gk4^r8@qF0o!Z3Vb2y10$V5F9zgYjZLZ1%sZ3Zq5u8Nw8e";
};

#endif // AUTHENTICATIONSERVICE_H