#include "LowerTriangularMatrix.hpp"

#include <iostream>

//* This code is written by Maaz Haris (mh09633) taught by Dr. Zuabiar Irshad
//* and RA is Mesum Qazalbash

LowerTriangularMatrix::LowerTriangularMatrix(const int size)
    : SquareMatrix(size) {}

LowerTriangularMatrix::LowerTriangularMatrix(const LowerTriangularMatrix& other)
    : SquareMatrix(other) {}

double LowerTriangularMatrix::getElement(const int row, const int col) const {
    return SquareMatrix::getElement(row, col);
}

void LowerTriangularMatrix::setElement(const int row, const int col,
                                       const double value) {
    if (col > row && value != 0) {
        throw std::invalid_argument(
            "Cannot set non-zero value above main diagonal in Lower "
            "Triangular Matrix.");
    }
    SquareMatrix::setElement(row, col, value);
}

LowerTriangularMatrix LowerTriangularMatrix::operator+(
    const LowerTriangularMatrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument(
            "Matrix dimensions must agree for addition.");
    }

    LowerTriangularMatrix result(rows);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j <= i; ++j) {
            double sum = getElement(i, j) + other.getElement(i, j);
            result.setElement(i, j, sum);
        }
    }
    return result;
}

LowerTriangularMatrix LowerTriangularMatrix::operator-(
    const LowerTriangularMatrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument(
            "Matrix dimensions must agree for subtraction.");
    }

    LowerTriangularMatrix result(rows);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j <= i; ++j) {
            double diff = getElement(i, j) - other.getElement(i, j);
            result.setElement(i, j, diff);
        }
    }
    return result;
}

LowerTriangularMatrix LowerTriangularMatrix::operator*(
    const LowerTriangularMatrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument(
            "Matrix dimensions must agree for multiplication.");
    }

    LowerTriangularMatrix result(rows);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j <= i; ++j) {
            double sum = 0;
            for (int k = j; k <= i; ++k) {
                sum += getElement(i, k) * other.getElement(k, j);
            }
            result.setElement(i, j, sum);
        }
    }
    return result;
}

bool LowerTriangularMatrix::operator==(
    const LowerTriangularMatrix& other) const {
    return SquareMatrix::operator==(other);
}