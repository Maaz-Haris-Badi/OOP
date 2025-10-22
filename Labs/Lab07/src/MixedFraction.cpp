#include "MixedFraction.hpp"

/// @brief Computes the greatest common divisor of two integers.
/// @param a first integer
/// @param b second integer
/// @return The greatest common divisor of a and b.
int gcd(const int a, const int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

/// @brief Stream output operator for `MixedFraction`
/// @param os The output stream
/// @param mf The mixed fraction to output
/// @return The output stream
std::ostream& operator<<(std::ostream& os, const MixedFraction& mf) {
    os << "MixedFraction(" << mf.m_whole << " " << mf.m_numerator << "/"
       << mf.m_denominator << ")";
    return os;
}

int MixedFraction::getWhole() const { return this->m_whole; }

int MixedFraction::getNumerator() const { return this->m_numerator; }

int MixedFraction::getDenominator() const { return this->m_denominator; }

void MixedFraction::normalize() {
    if (m_denominator <= m_numerator) {
        m_whole += m_numerator / m_denominator;
        m_numerator = m_numerator % m_denominator;
    }
    if (m_numerator == 0) {
        m_denominator = 1;
    } else {
        for (int i = 2; i <= m_numerator && i <= m_denominator; i++) {
            while (m_numerator % i == 0 && m_denominator % i == 0) {
                m_numerator /= i;
                m_denominator /= i;
            }
        }
    }
}

MixedFraction::MixedFraction(const int whole, const int numerator,
                             const int denominator) {
    this->m_whole       = whole;
    this->m_numerator   = numerator;
    this->m_denominator = denominator;
    this->normalize();
}

MixedFraction MixedFraction::operator+(const MixedFraction& other) const {
    int new_numerator_1, new_numerator_2, new_denominator;

    new_numerator_1 =
        ((this->m_whole * this->m_denominator) + this->m_numerator);

    new_numerator_2 =
        ((other.m_whole * other.m_denominator) + other.m_numerator);

    if (this->m_denominator != other.m_denominator) {
        new_denominator = this->m_denominator * other.m_denominator;
        new_numerator_1 *= other.m_denominator;
        new_numerator_2 *= this->m_denominator;
    } else {
        new_denominator = this->m_denominator;
    }

    int new_num = new_numerator_1 + new_numerator_2;

    return MixedFraction(0, new_num, new_denominator);
}

MixedFraction MixedFraction::operator-(const MixedFraction& other) const {
    int new_numerator_1, new_numerator_2, new_denominator;

    new_numerator_1 =
        ((this->m_whole * this->m_denominator) + this->m_numerator);

    new_numerator_2 =
        ((other.m_whole * other.m_denominator) + other.m_numerator);

    if (this->m_denominator != other.m_denominator) {
        new_denominator = this->m_denominator * other.m_denominator;
        new_numerator_1 *= other.m_denominator;
        new_numerator_2 *= this->m_denominator;
    } else {
        new_denominator = this->m_denominator;
    }

    int new_num = new_numerator_1 - new_numerator_2;

    return MixedFraction(0, new_num, new_denominator);
}

MixedFraction MixedFraction::operator*(const MixedFraction& other) const {
    int new_numerator_1, new_numerator_2;

    new_numerator_1 =
        ((this->m_whole * this->m_denominator) + this->m_numerator);

    new_numerator_2 =
        ((other.m_whole * other.m_denominator) + other.m_numerator);

    int new_num         = new_numerator_1 * new_numerator_2;
    int new_denominator = this->m_denominator * other.m_denominator;

    return MixedFraction(0, new_num, new_denominator);
}

MixedFraction MixedFraction::operator/(const MixedFraction& other) const {
    int new_numerator_1, new_numerator_2;

    new_numerator_1 =
        ((this->m_whole * this->m_denominator) + this->m_numerator);

    new_numerator_2 =
        ((other.m_whole * other.m_denominator) + other.m_numerator);

    int new_num         = new_numerator_1 * other.m_denominator;
    int new_denominator = this->m_denominator * new_numerator_2;

    return MixedFraction(0, new_num, new_denominator);
}

MixedFraction& MixedFraction::operator+=(const MixedFraction& other) {
    *this = *this + other;
    return *this;
}

MixedFraction& MixedFraction::operator-=(const MixedFraction& other) {
    *this = *this - other;
    return *this;
}

MixedFraction& MixedFraction::operator*=(const MixedFraction& other) {
    *this = *this * other;
    return *this;
}

MixedFraction& MixedFraction::operator/=(const MixedFraction& other) {
    *this = *this / other;
    return *this;
}

bool MixedFraction::operator==(const MixedFraction& other) const {
    int num1 = this->m_whole * this->m_denominator + this->m_numerator;
    int num2 = other.m_whole * other.m_denominator + other.m_numerator;

    return (num1 * other.m_denominator) == (num2 * this->m_denominator);
}

bool MixedFraction::operator!=(const MixedFraction& other) const {
    int num1 = this->m_whole * this->m_denominator + this->m_numerator;
    int num2 = other.m_whole * other.m_denominator + other.m_numerator;

    return (num1 * other.m_denominator) != (num2 * this->m_denominator);
}
