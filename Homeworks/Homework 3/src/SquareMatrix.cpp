#include "SquareMatrix.hpp"

#include <iostream>

//* This code is written by Maaz Haris, mh09633 of section L3/T3, taught by Dr.
//* Zubair Irshad and this homework will be checked by RA Muhammad Meesum Ali
//* Qazalbash

SquareMatrix::SquareMatrix(const int size) : Matrix(size, size) {
    if (size > 0) {
        elements.resize(size * size, 0.0);
    }
}

SquareMatrix::SquareMatrix(SquareMatrix const& other) : Matrix(other) {
    rows     = other.rows;
    cols     = other.cols;
    elements = other.elements;
}

double SquareMatrix::getElement(const int row, const int col) const {
    return Matrix::getElement(row, col);
}

void SquareMatrix::setElement(const int row, const int col,
                              const double value) {
    Matrix::setElement(row, col, value);
}

SquareMatrix SquareMatrix::operator+(const SquareMatrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        return SquareMatrix(0);
    }

    SquareMatrix result(rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.setElement(i, j,
                              this->getElement(i, j) + other.getElement(i, j));
        }
    }
    return result;
}

SquareMatrix SquareMatrix::operator-(const SquareMatrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        return SquareMatrix(0);
    }

    SquareMatrix result(rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.setElement(i, j,
                              this->getElement(i, j) - other.getElement(i, j));
        }
    }
    return result;
}

SquareMatrix SquareMatrix::operator*(const SquareMatrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        return SquareMatrix(0);
    }

    SquareMatrix result(rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            double sum = 0;
            for (int k = 0; k < cols; k++) {
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