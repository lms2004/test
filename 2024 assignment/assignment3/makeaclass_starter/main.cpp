

/*
 * Assigment 3: Make a class!
 * Requirements:
 * Must have a custom constructor 
 * Must have a default constructor ❌
    - i.e. constructor overloading
 * Must have private members (functions and/or variables) ❌
 * Must have public members (functions) ❌
 * Must have at least one getter function ❌
 * Must have at least one setter function ❌
 */

#include "class.h"
#include <iostream>

int main() {
    // Using the custom constructor
    project<int> project1("Project Alpha", 85, 1);
    project<int> project2("Project Beta", 95, 2);
    
    // Using the default constructor and setter functions
    project<int> project3;
    project3.setname("Project Gamma");
    project3.setscore(75);
    project3.setid(3);

    management<int> myManagement;

    // Insert projects into management
    myManagement.p_insert(project1);
    myManagement.p_insert(project2);
    myManagement.p_insert(project3);

    // Sort projects by score
    myManagement.p_sort();

    // Displaying the best project
    project<int> best = myManagement.best_project();
    std::cout << "Best Project: " << best.getname() << " with score " << best.getscore() << std::endl;

    return 0;
}
