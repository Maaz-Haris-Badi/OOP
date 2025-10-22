#include "Vector2D.hpp"

/// @brief Stream output operator for `Vector2D`
/// @param os The output stream
/// @param v The vector to output
/// @return The output stream
std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
    os << "Vector2D(" << v.m_x << ", " << v.m_y << ")";
    return os;
}

Vector2D::Vector2D(const double x, const double y) {
    m_x = x;
    m_y = y;
}

Vector2D Vector2D::operator+(const Vector2D& other) const {
    double new_x, new_y;
    new_x = this->m_x + other.m_x;
    new_y = this->m_y + other.m_y;

    return (Vector2D(new_x, new_y));
}

Vector2D Vector2D::operator-(const Vector2D& other) const {
    double new_x, new_y;
    new_x = this->m_x - other.m_x;
    new_y = this->m_y - other.m_y;

    Vector2D ut = Vector2D(new_x, new_y);

    return ut;
}

Vector2D Vector2D::operator*(const double scalar) const {
    double new_x, new_y;
    new_x = this->m_x * scalar;
    new_y = this->m_y * scalar;

    return (Vector2D(new_x, new_y));
}

Vector2D& Vector2D::operator+=(const Vector2D& other) {
    this->m_x += other.m_x;
    this->m_y += other.m_y;

    return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& other) {
    this->m_x -= other.m_x;
    this->m_y -= other.m_y;

    return *this;
}

Vector2D& Vector2D::operator*=(const double scaler) {
    this->m_x *= scaler;
    this->m_y *= scaler;

    return *this;
}

double Vector2D::operator*(const Vector2D& other) const {
    double miu = (this->m_x * other.m_x) + (this->m_y * other.m_y);

    return miu;
}

bool Vector2D::operator==(const Vector2D& other) const {
    if ((this->m_x == other.m_x) && (this->m_y == other.m_y)) {
        return true;

    } else
        return false;
}

bool Vector2D::operator!=(const Vector2D& other) const {
    if ((this->m_x != other.m_x) && (this->m_y != other.m_y)) {
        return true;

    } else
        return false;
}

double Vector2D::operator[](int index) const {
    double ret = 0;
    if (index == 0) {
        ret = m_x;
    } else if (index == 1) {
        ret = m_y;
    } else {
        std::cout << "This is a 2D array!" << std::endl;
    };
    return ret;
}
