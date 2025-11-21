#include "LowerTriangularMatrix.hpp"

#include <iostream>

//* This code is written by Maaz Haris, mh09633 of section L3/T3, taught by Dr.
//* Zubair Irshad and this homework will be checked by RA Muhammad Meesum Ali
//* Qazalbash

LowerTriangularMatrix::LowerTriangularMatrix(const int size)
    : SquareMatrix(size) {
    if (size > 0) {
        int numElements = size * (size + 1) / 2;
        elements.resize(numElements, 0.0);
    }
}

LowerTriangularMatrix::LowerTriangularMatrix(const LowerTriangularMatrix& other)
    : SquareMatrix(other) {
    rows     = other.rows;
    cols     = other.cols;
    elements = other.elements;
}

double LowerTriangularMatrix::getElement(const int row, const int col) const {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return 0.0;
    }
    if (col > row) {
        return 0.0;
    }
    int index = (row * (row + 1) / 2) + col;
    return elements[index];
}

void LowerTriangularMatrix::setElement(const int row, const int col,
                                       const double value) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return;
    }
    if (col > row) {
        return;
    }
    int index       = (row * (row + 1) / 2) + col;
    elements[index] = value;
}

LowerTriangularMatrix LowerTriangularMatrix::operator+(
    const LowerTriangularMatrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        return LowerTriangularMatrix(0);
    }

    LowerTriangularMatrix result(rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= i; j++) {
            double sum = this->getElement(i, j) + other.getElement(i, j);
            result.setElement(i, j, sum);
        }
    }
    return result;
}

LowerTriangularMatrix LowerTriangularMatrix::operator-(
    const LowerTriangularMatrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        return LowerTriangularMatrix(0);
    }

    LowerTriangularMatrix result(rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= i; j++) {
            double diff = this->getElement(i, j) - other.getElement(i, j);
            result.setElement(i, j, diff);
        }
    }
    return result;
}

LowerTriangularMatrix LowerTriangularMatrix::operator*(
    const LowerTriangularMatrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        return LowerTriangularMatrix(0);
    }

    LowerTriangularMatrix result(rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= i; j++) {
            double sum = 0.0;
            for (int k = j; k <= i; k++) {
                sum += getElement(i, k) * other.getElement(k, j);
            }
            result.setElement(i, j, sum);
        }
    }
    return result;
}

bool LowerTriangularMatrix::operator==(
    const LowerTriangularMatrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        return false;
    }
    return elements == other.elements;
}