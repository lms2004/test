/* 
Assignment 2: Marriage Pact

This assignment asks you to discover your one true love using containers and pointers.
There are two parts: implement get_applicants and find_matches.

Submit to Paperless by 11:59pm on 2/1/2024.
*/
#include<fstream>
#include <iostream>
#include <string>
#include <queue>
#include <unordered_set>
#include<algorithm>
#include<memory>
#include<random>

std::unordered_set<std::string> get_applicants(std::string filename) {
    // TODO: Implement this function. Feel free to change std::set to std::unordered_set if you wish!
    std::fstream fs;
    fs.open(filename);
    if(!fs.is_open()){
        std::logic_error("文件未能打开");
        //std::cerr << "Failed to open file: "<<filename  << std::endl;
        return {};
    }
    std::string line;
    std::unordered_set<std::string> myset;
    while(getline(fs,line)){
        myset.insert(line);
        std::cout<<line<<std::endl;
    }
    fs.close();
    return myset;
}

std::queue<std::shared_ptr<std::string>> find_matches(const std::unordered_set<std::string>& students, const std::string& initials) {
    std::queue<std::shared_ptr<std::string>> myqueue;
    for (const auto& student : students) {
        if (student[0] == initials[0] && student[student.find(' ') + 1] == initials[1]) {
            myqueue.push(std::make_shared<std::string>(student));
        }
    }
    return myqueue;
}


int main() {
    // Your code goes here. Don't forget to print your true love!
    std::unordered_set students=get_applicants("students.txt");
    std::queue<std::shared_ptr<std::string>> myqueue=find_matches(students,"MM");
    if(myqueue.empty()){
        std::cout<<"NO STUDENTFOUND."<<std::endl;
    }else{
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(0,myqueue.size());
        int randomIndex=dis(gen);
        // 将队列中的元素循环移动 randomIndex 次
        for(int i = 0; i < randomIndex; ++i) {
            std::shared_ptr<std::string> frontElement = myqueue.front();
            myqueue.pop();  
            myqueue.push(frontElement); // 将这个元素放到队列的后面
        }
        std::shared_ptr<std::string> tlove =myqueue.front();
        myqueue.pop();
        std::cout<<"tlove:"<<*tlove<<std::endl;
    }
    return 0;
}
