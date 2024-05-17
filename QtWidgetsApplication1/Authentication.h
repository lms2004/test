#ifndef AUTHENTICATION_SERVICE_H
#define AUTHENTICATION_SERVICE_H

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication1.h"
#include "h.h"
#include <iostream>
#include <unordered_map>

// 引入MySQL数据库库
#include <mysql.h>

// 引入OpenSSL库，用于密码加密
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>


// 认证服务类
class AuthenticationService : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication1(QWidget* parent = Q_NULLPTR);

private:
    Ui::QtWidgetsApplication1Class ui;
private slots:
    //构造函数
    AuthenticationService();
    //析构函数
    ~AuthenticationService();

    // 登录函数
    bool login(const std::string& username, const std::string& password);
    // 注册函数
    bool registerUser(const std::string& username, const std::string& password);

    // 本地缓存的用户信息
    std::unordered_map<std::string, std::string> users;
    // 密码哈希处理函数
    std::string hashPassword(const std::string& password);
};

#endif // AUTHENTICATION_SERVICE_H
