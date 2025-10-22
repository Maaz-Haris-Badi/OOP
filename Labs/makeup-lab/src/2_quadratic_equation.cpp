#ifndef QUADRATIC_EQUATION
#define QUADRATIC_EQUATION

#include <cmath>
#include <iostream>

class QuadraticEquation {
public:

    // Constructor
    QuadraticEquation(const double a, const double b, const double c);

    // Check if real solutions exist
    bool has_solutions() const;

    // Get the smaller root
    double get_solution1() const;

    // Get the larger root
    double get_solution2() const;

private:

    double a, b, c;
};

QuadraticEquation::QuadraticEquation(const double a_, const double b_,
                                     const double c_) {
    a = a_;
    b = b_;
    c = c;
}

bool QuadraticEquation::has_solutions() const {
    if (((pow(b, 2)) - (4 * a * c)) < 0) {
        return false;
    } else
        return true;
}

double QuadraticEquation::get_solution1() const {
    if (has_solutions() == true) {
        double output = (pow(b, 2) - (4 * a * c)) / (2 * a);
    } else
        std::cout << "There are no real solutions of this equation";
}

double QuadraticEquation::get_solution2() const {
    if (has_solutions() == true) {
        double output = (pow(b, 2) + (4 * a * c)) / (2 * a);
    } else
        std::cout << "There are no real solutions of this equation";
}

#endif
