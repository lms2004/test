#pragma once
#ifndef PROJECT_SORTING_H
#define PROJECT_SORTING_H
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include<string>
#include<mysql.h>
class Project {
public:
    std::string name; // 项目名称
    std::string type; // 项目类型
    std::string grade; // 项目成绩
    std::string path;//路径

    Project(const std::string name, const std::string& type, const std::string& grade, const std::string& path) :name(name), type(type), grade(grade), path(path) {} // 构造函数;

    //运算符重载,用于排序;
    bool operator>(const Project a) {

        if (type == a.type) {
            if (grade == a.grade)
                return name < a.name;
            else
                return grade > a.grade;
        }//先按类型首字母由小到大排序,再按成绩由大到小排序;
        else
            return type < a.type; //若类型不等则按类型排序;
    }
    //运算符重载,用于去重;
    bool operator==(const Project a) {
        if (type == a.type)
            return grade > a.grade;
        else
            return 0;
    }
};


class ProjectSorting {

public:
    //去重函数,保留每个项目成绩最好的;若成绩相等,则保留所有等于该成绩的项目;
    void deduplicateByTypeAndGrade(std::vector<Project>& projects);
};

class ProjectMysql {
    MYSQL mysql;//数据库句柄
    MYSQL_RES* res;//查询结果集
    MYSQL_ROW row;//记录结构体
    char database_password[20] = "123456";
public:
    ProjectMysql();//初始化数据库
    //析构函数;
    ~ProjectMysql() {
        //释放结果集
        mysql_free_result(res);
        //关闭数据库
        mysql_close(&mysql);
    }

    //从mysql中提取数据;
    void OutputProject(std::vector<Project>& projects);
    //向mysql中写入数据
    void InputProject(std::vector<Project>& projects);

};
#endif
