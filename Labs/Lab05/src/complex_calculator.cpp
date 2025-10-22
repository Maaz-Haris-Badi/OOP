#ifndef COMPLEX_CALCULATOR
#define COMPLEX_CALCULATOR

/*
Write your solution here.
*/
#include <iostream>

class Complex {
private:

    double real;
    double imag;

public:

    Complex() : real(0), imag(0) {}

    Complex(double r, double i) {
        real = r;
        imag = i;
    }

    Complex add(Complex& other) {
        const double r = real + other.real;
        const double i = imag + other.imag;

        return Complex(r, i);
    }

    Complex add(double& other) {
        double r = real + other;
        double i = imag;

        return Complex(r, i);
    }

    Complex subtract(Complex& other) {
        double r = real - other.real;
        double i = imag - other.imag;

        return Complex(r, i);
    }

    Complex subtract(double& other) {
        double r = real - other;
        double i = imag;

        return Complex(r, i);
    }

    Complex multiply(Complex& other) {
        double r = (real * other.real) - (imag * other.imag);
        double i = (real * other.imag) + (imag * other.real);

        return Complex(r, i);
    }

    Complex multiply(double& other) {
        double r = other * real;
        double i = imag * other;

        return Complex(r, i);
    }

    void show() { std::cout << real << " + " << imag << "i" << std::endl; }
};

int main() {
    double real, imag;
    std::cin >> real >> imag;
    Complex c1 = {real, imag};
    std::cin >> real >> imag;
    Complex c2 = {real, imag};
    double  d1;
    std::cin >> d1;
    Complex result;
    // showing the numbers :
    std::cout << "c1: ";
    c1.show();
    std::cout << "c2: ";
    c2.show();
    std::cout << "d1: " << d1 << std::endl;
    // Check the opertions where both operands are complex
    result = c1.add(c2);
    std::cout << "c1+c2: ";
    result.show();
    result = c1.subtract(c2);
    std::cout << "c1 -c2: ";
    result.show();
    result = c1.multiply(c2);
    std::cout << "c1*c2: ";
    result.show();
    // Check the opertions where one operator is complex , other is double
    result = c1.add(d1);
    std::cout << "c1+d1: ";
    result.show();
    result = c1.subtract(d1);
    std::cout << "c1 -d1: ";
    result.show();
    result = c1.multiply(d1);
    std::cout << "c1*d1: ";
    result.show();
    return 0;
}

#endif  // COMPLEX_CALCULATOR
