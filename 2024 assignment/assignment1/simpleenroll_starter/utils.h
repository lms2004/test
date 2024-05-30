// utils.h
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

// Structure for Course
struct Course {
    std::string title;
    std::string number_of_units;
    std::string quarter;
    bool operator==(const Course &other) const;
};

// Global variables declaration
extern std::string COURSES_OFFERED_CSV_PATH;
extern std::string COURSES_NOT_OFFERED_CSV_PATH;

// Function declarations
void parse_csv(std::string filename, std::vector<Course>& vector_of_courses);
void write_courses_offered(std::vector<Course>& vector_of_courses);
void write_courses_not_offered(std::vector<Course> vector_of_courses);
void delete_elem_from_vector(std::vector<Course> &v, Course &elem);
std::vector<std::string> split(std::string s, char delim);
void print_vector(std::vector<Course> vector_of_courses);
// Documentation comments should ideally be added above each declaration to describe the purpose and usage.

#endif // UTILS_H
