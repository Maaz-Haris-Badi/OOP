#include "SquareMatrix.hpp"

#include <iostream>

SquareMatrix::SquareMatrix(const int size) : Matrix(size, size) {}

SquareMatrix::SquareMatrix(SquareMatrix const& other) : Matrix(other) {}

double SquareMatrix::getElement(const int row, const int col) const {
    return Matrix::getElement(row, col);
}

void SquareMatrix::setElement(const int row, const int col,
                              const double value) {
    Matrix::setElement(row, col, value);
}

SquareMatrix SquareMatrix::operator+(const SquareMatrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument(
            "Matrix dimensions must agree for addition.");
    }

    SquareMatrix result(rows);
    for (int i = 0; i < rows * cols; ++i) {
        result.elements[i] = elements[i] + other.elements[i];
    }
    return result;
}

SquareMatrix SquareMatrix::operator-(const SquareMatrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument(
            "Matrix dimensions must agree for subtraction.");
    }

    SquareMatrix result(rows);
    for (int i = 0; i < rows * cols; ++i) {
        result.elements[i] = elements[i] - other.elements[i];
    }
    return result;
}

SquareMatrix SquareMatrix::operator*(const SquareMatrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument(
            "Matrix dimensions must agree for multiplication.");
    }

    SquareMatrix result(rows);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            double sum = 0;
            for (int k = 0; k < cols; ++k) {
                sum += getElement(i, k) * other.getElement(k, j);
            }
            result.setElement(i, j, sum);
        }
    }
    return result;
}

bool SquareMatrix::operator==(const SquareMatrix& other) const {
    return Matrix::operator==(other);
}