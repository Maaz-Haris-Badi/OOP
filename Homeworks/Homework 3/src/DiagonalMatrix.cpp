#include "DiagonalMatrix.hpp"

#include <iostream>

DiagonalMatrix::DiagonalMatrix(const int size) : SquareMatrix(size) {}

DiagonalMatrix::DiagonalMatrix(DiagonalMatrix const& other)
    : SquareMatrix(other) {}

double DiagonalMatrix::getElement(const int row, const int col) const {
    return Matrix::getElement(row, col);
}

void DiagonalMatrix::setElement(const int row, const int col,
                                const double value) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        throw std::out_of_range("Index out of bounds");
    }
    if (row != col && value != 0.0) {
        throw std::invalid_argument(
            "Only diagonal elements can be non-zero in a DiagonalMatrix");
    }
    return Matrix::setElement(row, col, value);
}

DiagonalMatrix DiagonalMatrix::operator+(const DiagonalMatrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrix sizes do not match for addition");
    }
    DiagonalMatrix result(rows);
    for (int i = 0; i < rows; ++i) {
        double sum = this->getElement(i, i) + other.getElement(i, i);
        result.setElement(i, i, sum);
    }
    return result;
}

DiagonalMatrix DiagonalMatrix::operator-(const DiagonalMatrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument(
            "Matrix sizes do not match for subtraction");
    }
    DiagonalMatrix result(rows);
    for (int i = 0; i < rows; ++i) {
        double diff = this->getElement(i, i) - other.getElement(i, i);
        result.setElement(i, i, diff);
    }
    return result;
}

DiagonalMatrix DiagonalMatrix::operator*(const DiagonalMatrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument(
            "Matrix sizes do not match for multiplication");
    }
    DiagonalMatrix result(rows);
    for (int i = 0; i < rows; ++i) {
        double prod = this->getElement(i, i) * other.getElement(i, i);
        result.setElement(i, i, prod);
    }
    return result;
}

bool DiagonalMatrix::operator==(const DiagonalMatrix& other) const {
    return SquareMatrix::operator==(other);
}