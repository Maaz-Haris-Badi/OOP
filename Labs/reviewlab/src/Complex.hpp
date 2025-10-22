#ifndef COMPLEX_HPP
#define COMPLEX_HPP

class Complex {
public:

    Complex(const double real, const double imag);

    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;

    double getReal() const;
    double getImag() const;

private:

    double m_real, m_imag;
};

#endif  // COMPLEX_HPP