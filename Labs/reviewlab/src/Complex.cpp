#include "Complex.hpp"

#include <cmath>
#include <iostream>

Complex::Complex(double real, double imag) {
    this->m_real = real;
    m_imag       = imag;
}

Complex Complex::operator+(const Complex& other) const {
    double real = this->m_real + other.m_real;
    double imag = this->m_imag + other.m_imag;
    return Complex(real, imag);
}

Complex Complex::operator-(const Complex& other) const {
    double real = this->m_real - other.m_real;
    double imag = m_imag - other.m_imag;
    return Complex(real, imag);
}

Complex Complex::operator*(const Complex& other) const {
    double real = (this->m_real * other.m_real) - (this->m_imag * other.m_imag);
    double imag = (this->m_real * other.m_imag) + (this->m_imag * other.m_real);
    return Complex(real, imag);
}

Complex Complex::operator/(const Complex& other) const {
    double denominator = std::pow(other.m_real, 2) + std::pow(other.m_imag, 2);
    double real =
        ((this->m_real * other.m_real) + (this->m_imag * other.m_imag)) /
        denominator;
    double imag =
        ((this->m_imag * other.m_real) - (this->m_real * other.m_imag)) /
        denominator;

    if (denominator == 0) {
        real = NAN;
        imag = NAN;
    }
    return Complex(real, imag);
}

double Complex::getReal() const { return this->m_real; }

double Complex::getImag() const { return this->m_imag; }
