#include <iostream>

#include "q1_numbers.h"

class NumWhole : public NumInterface {
private:

    int value;

public:

    NumWhole(int val);
    int      getval() const;
    void     setval(int val);
    void     display() const override;
    void     increment() override;
    NumWhole operator+(const NumWhole &other) const;
};

class NumComplex : public NumInterface {
private:

    int m_real;
    int m_imag;

public:

    NumComplex(int rel, int ima);
    int        getreal() const;
    int        getimag() const;
    void       setreal(int real);
    void       setimag(int imag);
    void       display() const override;
    void       increment() override;
    NumComplex operator+(const NumComplex &other) const;
};

NumWhole::NumWhole(int val) : value(val) {}

int NumWhole::getval() const { return value; }

void NumWhole::setval(int val) { value = val; }

void NumWhole::display() const {
    int val = getval();
    std::cout << val;
}

void NumWhole::increment() { value = value + 1; }

NumWhole NumWhole::operator+(const NumWhole &other) const {
    int sum = this->value + other.value;
    return NumWhole(sum);
}

NumComplex::NumComplex(int rel, int ima) : m_real(rel), m_imag(ima) {}

int NumComplex::getreal() const { return m_real; }

int NumComplex::getimag() const { return m_imag; }

void NumComplex::setreal(int real) { m_real = real; }

void NumComplex::setimag(int imag) { m_imag = imag; }

void NumComplex::display() const {
    int real = getreal();
    int imag = getimag();
    if (imag >= 0)
        std::cout << "(" << real << "+" << imag << "i)";
    else
        std::cout << "(" << real << imag << "i)";
}

void NumComplex::increment() {
    m_real = m_real + 1;
    m_imag = m_imag + 1;
}

NumComplex NumComplex::operator+(const NumComplex &other) const {
    int real_sum = this->m_real + other.m_real;
    int imag_sum = this->m_imag + other.m_imag;
    return NumComplex(real_sum, imag_sum);
}