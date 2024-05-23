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
    std::string name; // ��Ŀ����
    std::string type; // ��Ŀ����
    std::string grade; // ��Ŀ�ɼ�
    std::string path;//·��

    Project(const std::string name, const std::string& type, const std::string& grade, const std::string& path) :name(name), type(type), grade(grade), path(path) {} // ���캯��;

    //���������,��������;
    bool operator>(const Project a) {

        if (type == a.type) {
            if (grade == a.grade)
                return name < a.name;
            else
                return grade > a.grade;
        }//�Ȱ���������ĸ��С��������,�ٰ��ɼ��ɴ�С����;
        else
            return type < a.type; //�����Ͳ�������������;
    }
    //���������,����ȥ��;
    bool operator==(const Project a) {
        if (type == a.type)
            return grade > a.grade;
        else
            return 0;
    }
};


class ProjectSorting {

public:
    //ȥ�غ���,����ÿ����Ŀ�ɼ���õ�;���ɼ����,�������е��ڸóɼ�����Ŀ;
    void deduplicateByTypeAndGrade(std::vector<Project>& projects);
};

class ProjectMysql {
    MYSQL mysql;//���ݿ���
    MYSQL_RES* res;//��ѯ�����
    MYSQL_ROW row;//��¼�ṹ��
    char database_password[20] = "123456";
public:
    ProjectMysql();//��ʼ�����ݿ�
    //��������;
    ~ProjectMysql() {
        //�ͷŽ����
        mysql_free_result(res);
        //�ر����ݿ�
        mysql_close(&mysql);
    }

    //��mysql����ȡ����;
    void OutputProject(std::vector<Project>& projects);
    //��mysql��д������
    void InputProject(std::vector<Project>& projects);

};
#endif
