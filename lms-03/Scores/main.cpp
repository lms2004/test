#include <iostream>
#include "function.h"
#define _OUTPUT
#define size 10
int main() {
    std::vector<double> arr;
    input(arr, size);
#ifdef _OUTPUT
    std::cout << "max: " << max_num(arr) << std::endl;
    std::cout << "min: " << min_num(arr) << std::endl; 
    std::cout << "average:  " << average(arr) << std::endl;
#endif
    return 0;
}
