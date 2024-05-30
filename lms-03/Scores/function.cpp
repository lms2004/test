#include "function.h"

double max_num(const std::vector<double>& arr) {
    double max_num = arr[0];
    for (const auto& num : arr) {
        max_num = std::max(max_num, num);
    }
    return max_num;
}
double min_num(const std::vector<double>& arr) {
    double min_num = arr[0];
    for (const auto& num : arr) {
        min_num = std::min(min_num, num);
    }
    return min_num;
}
double average(const std::vector<double>& arr) {
    double sum = 0.0;
    for (const auto& num : arr) {
        sum += num;
    }
    return sum / arr.size();
}
void input(std::vector<double>& arr, int size) {
    std::cout << "ÇëÊä³ö" << size << "¸ö³É¼¨\n";
    for (int i = 0; i < size; i++) {
        double temp;
        std::cin >> temp;
        arr.push_back(temp);
    }
}

