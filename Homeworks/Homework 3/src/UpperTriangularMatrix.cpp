#include "UpperTriangularMatrix.hpp"

#include <iostream>

//* This code is written by Maaz Haris (mh09633) taught by Dr. Zuabiar Irshad
//* and RA is Mesum Qazalbash

UpperTriangularMatrix::UpperTriangularMatrix(const int size)
    : SquareMatrix(size) {}

UpperTriangularMatrix::UpperTriangularMatrix(const UpperTriangularMatrix& other)
    : SquareMatrix(other) {}

double UpperTriangularMatrix::getElement(const int row, const int col) const {
    return SquareMatrix::getElement(row, col);
}

void UpperTriangularMatrix::setElement(const int row, const int col,
                                       const double value) {
    if (col < row && value != 0) {
        throw std::invalid_argument(
            "Cannot set non-zero value below main diagonal in Upper "
            "Triangular Matrix.");
    }
    SquareMatrix::setElement(row, col, value);
}

UpperTriangularMatrix UpperTriangularMatrix::operator+(
    const UpperTriangularMatrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument(
            "Matrix dimensions must agree for addition.");
    }

    UpperTriangularMatrix result(rows);

    for (int i = 0; i < rows; ++i) {
        for (int j = i; j < cols; ++j) {
            double sum = getElement(i, j) + other.getElement(i, j);
            result.setElement(i, j, sum);
        }
    }
    return result;
}

UpperTriangularMatrix UpperTriangularMatrix::operator-(
    const UpperTriangularMatrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument(
            "Matrix dimensions must agree for subtraction.");
    }

    UpperTriangularMatrix result(rows);

    for (int i = 0; i < rows; ++i) {
        for (int j = i; j < cols; ++j) {
            double diff = getElement(i, j) - other.getElement(i, j);
            result.setElement(i, j, diff);
        }
    }
    return result;
}

UpperTriangularMatrix UpperTriangularMatrix::operator*(
    const UpperTriangularMatrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument(
            "Matrix dimensions must agree for multiplication.");
    }

    UpperTriangularMatrix result(rows);

    for (int i = 0; i < rows; ++i) {
        for (int j = i; j < cols; ++j) {
            double sum = 0.0;
            for (int k = i; k <= j; ++k) {
                sum += getElement(i, k) * other.getElement(k, j);
            }
            result.setElement(i, j, sum);
        }
    }
    return result;
}

bool UpperTriangularMatrix::operator==(
    const UpperTriangularMatrix& other) const {
    return SquareMatrix::operator==(other);
}
