#include "UpperTriangularMatrix.hpp"

#include <iostream>

//* This code is written by Maaz Haris, mh09633 of section L3/T3, taught by Dr.
//* Zubair Irshad and this homework will be checked by RA Muhammad Meesum Ali
//* Qazalbash

UpperTriangularMatrix::UpperTriangularMatrix(const int size)
    : SquareMatrix(size) {
    if (size > 0) {
        int numElements = size * (size + 1) / 2;
        elements.resize(numElements, 0.0);
    }
}

UpperTriangularMatrix::UpperTriangularMatrix(const UpperTriangularMatrix& other)
    : SquareMatrix(other) {
    rows     = other.rows;
    cols     = other.cols;
    elements = other.elements;
}

double UpperTriangularMatrix::getElement(const int row, const int col) const {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return 0.0;
    }
    if (row > col) {
        return 0.0;
    }
    int index = cols * row + col - (row * (row + 1) / 2);
    return elements[index];
}

void UpperTriangularMatrix::setElement(const int row, const int col,
                                       const double value) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return;
    }
    if (row > col) {
        return;
    }
    int index       = cols * row + col - (row * (row + 1) / 2);
    elements[index] = value;
}

UpperTriangularMatrix UpperTriangularMatrix::operator+(
    const UpperTriangularMatrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        return UpperTriangularMatrix(0);
    }

    UpperTriangularMatrix result(rows);
    for (int i = 0; i < rows; i++) {
        for (int j = i; j < cols; j++) {
            double sum = this->getElement(i, j) + other.getElement(i, j);
            result.setElement(i, j, sum);
        }
    }
    return result;
}

UpperTriangularMatrix UpperTriangularMatrix::operator-(
    const UpperTriangularMatrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        return UpperTriangularMatrix(0);
    }

    UpperTriangularMatrix result(rows);
    for (int i = 0; i < rows; i++) {
        for (int j = i; j < cols; j++) {
            double diff = this->getElement(i, j) - other.getElement(i, j);
            result.setElement(i, j, diff);
        }
    }
    return result;
}

UpperTriangularMatrix UpperTriangularMatrix::operator*(
    const UpperTriangularMatrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        return UpperTriangularMatrix(0);
    }

    UpperTriangularMatrix result(rows);
    for (int i = 0; i < rows; i++) {
        for (int j = i; j < cols; j++) {
            double sum = 0.0;
            for (int k = i; k <= j; k++) {
                sum += getElement(i, k) * other.getElement(k, j);
            }
            result.setElement(i, j, sum);
        }
    }
    return result;
}

bool UpperTriangularMatrix::operator==(
    const UpperTriangularMatrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        return false;
    }
    return elements == other.elements;
}