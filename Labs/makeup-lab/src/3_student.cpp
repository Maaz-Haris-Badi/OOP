#ifndef STUDENT
#define STUDENT

#include <iostream>
#include <string>

class Student {
public:

    // Constructor
    Student(const std::string&);

    // Get the student's name
    std::string get_name() const;

    // Add a quiz score
    void add_quiz(const int);

    // Get the total score
    int get_total_score() const;

    // Get the average score
    double get_average_score() const;

private:

    std::string name;
    int         total_score;
    int         quiz_count;
};

Student::Student(const std::string& naam) { name = naam; }

std::string Student::get_name() const { return name; }

void Student::add_quiz(const int score) {
    quiz_count += 1;
    total_score += score;
}

int Student::get_total_score() const { return total_score; }

double Student::get_average_score() const {
    double average = static_cast<double>(total_score) / quiz_count;
    return average;
}
#endif
