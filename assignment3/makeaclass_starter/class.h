#ifndef _CLASS_H_
#define _CLASS_H_

#include <string>
#include <vector>

template<typename T>
class project {
private:
    std::string name;
    T score;
    int id;
public:
    project(std::string tname, T tscore,int tid) : name(tname), id(tid),score(tscore) {} // 构造函数实现
    project() : name("Unnamed"), score(0), id(-1) {}

    std::string getname() const { return name; } // 获取名称
    int getid()const {return id;};
    T getscore() const { return score; } // 获取ID

    void setname(const std::string& newName) { name = newName; }
    void setscore(const T& newScore) { score = newScore; }
    void setid(int newId) { id = newId; }
};

template<typename T>
class management {
private:
    std::vector<project<T>> projects;
public:
    void p_sort(); // 假设这个函数用于排序
    project<T> best_project();
    void p_insert(const project<T>& temp);
};

#endif // _CLASS_H_
