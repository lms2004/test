// Blank cpp file
#include"class.h"
#include<algorithm>
template<typename T>
void management<T>::p_insert(const project<T>& temp) {
    auto it = std::find_if(projects.begin(), projects.end(), [&](const project<T>& proj) {
        return proj.getname() == temp.getname();
    });

    if (it == projects.end()) { // If not found, then insert
        projects.push_back(temp);
    }
}
template<typename T>
void management<T>::p_sort(){
    sort(projects.begin(),projects.back(),[&](const project& a1,const project &a2){
        return a1.getscore()>a2.getscore();
    })
}
template<typename T>
project<T> management<T>::best_project() {
    return *std::max_element(projects.begin(), projects.end(), [&](const project<T>& a, const project<T>& b) {
        return a.getscore() < b.getscore();
    });
}