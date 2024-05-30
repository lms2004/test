/* 
Assignment 4: Weather Forecast

This assignment works with template functions and lambdas to become the best weather forecaster
at the Stanford Daily. Be sure to read the assignment details in the PDF.

Submit to Paperless by 11:59pm on 2/16/2024.
*/

// TODO: import anything from the STL that might be useful!
#include <iostream>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip> 
// TODO: write convert_f_to_c function here. Remember it must be a template function that always returns
// a double.
// [function definition here]
template<typename T>
double convert_f_to_c(T Fahrenheit){
    return static_cast<double>(Fahrenheit - 32) * 5/9;
}



template<typename Function>
std::vector<double> get_forecast(std::vector<std::vector<int>> readings, Function fn) {
    std::vector<double> forecast;
    for(const auto day:readings){
        forecast.push_back(fn(day));
    }
    return forecast;
}

int main() {
    std::vector<std::vector<int>> readings = {
        {70, 75, 80, 85, 90},
        {60, 65, 70, 75, 80},
        {50, 55, 60, 65, 70},
        {40, 45, 50, 55, 60},
        {30, 35, 40, 45, 50},
        {50, 55, 61, 65, 70},
        {40, 45, 50, 55, 60}
    };
    std::vector<std::vector<double>> Celsius_reading;
    std::fstream fs;
    fs.open("output.txt");
    // TODO: Convert temperatures to Celsius and output to output.txt
    for(auto d:readings){ 
        std::vector<double> day;
        for( auto t:d){
            double Celsius=convert_f_to_c(t);
            day.push_back(Celsius);
            fs << std::fixed << std::setprecision(2) << Celsius << "  ";
        }fs<<std::endl;
        Celsius_reading.push_back(day);
    }
    // TODO: Find the maximum temperature for each day and output to output.txt
    fs<<"max:"<<std::endl;
    std::vector<double> max_days=get_forecast(readings,[](std::vector<int> day){double max=-1;  for(auto t:day){if(max<t) max=t;};return max;});
    for(auto day:max_days){
        fs << std::fixed << std::setprecision(2) << day << "  ";
    };fs<<std::endl;

    // TODO: Find the minimum temperature for each day and output to output.txt
    fs<<"min:"<<std::endl;
    std::vector<double> min_days=get_forecast(readings,[](std::vector<int> day){double min=10000;  for(auto t:day){if(min>t) min=t;}return min;});
    for(auto day:min_days){
        fs << std::fixed << std::setprecision(2) << day << "  ";
    };fs<<std::endl;

    // TODO: Find the average temperature for each day and output to output.txt
    fs<<"avg:"<<std::endl;
    std::vector<double> avg_days=get_forecast(readings,[](std::vector<int> day){double avg=0;  for(auto t:day){avg+=t;}return avg/day.size();});
    for(auto day:avg_days){
        fs << std::fixed << std::setprecision(2) << day << "  ";
    };fs<<std::endl;
    return 0;
}