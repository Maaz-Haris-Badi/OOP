#include "DiagonalMatrix.hpp"

#include <iostream>

//* This code is written by Maaz Haris, mh09633 of section L3/T3, taught by Dr.
//* Zubair Irshad and this homework will be checked by RA Muhammad Meesum Ali
//* Qazalbash

DiagonalMatrix::DiagonalMatrix(const int size) : SquareMatrix(size) {
    if (size > 0) {
        elements.resize(size, 0.0);
    }
}

DiagonalMatrix::DiagonalMatrix(DiagonalMatrix const& other)
    : SquareMatrix(other) {
    this->rows     = other.rows;
    this->cols     = other.cols;
    this->elements = other.elements;
}

double DiagonalMatrix::getElement(const int row, const int col) const {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return 0.0;
    }

    if (row == col) {
        return elements[row];
    }

    return 0.0;
}

void DiagonalMatrix::setElement(const int row, const int col,
                                const double value) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return;
    }

    if (row != col) {
        return;
    }
    elements[row] = value;
}

DiagonalMatrix DiagonalMatrix::operator+(const DiagonalMatrix& other) const {
    if (this->rows != other.rows || this->cols != other.cols) {
        return DiagonalMatrix(0);
    }

    DiagonalMatrix result(this->rows);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            if (i == j) {
                double sum = this->getElement(i, j) + other.getElement(i, j);
                result.setElement(i, j, sum);
            }
        }
    }
    return result;
}

// Operator -
DiagonalMatrix DiagonalMatrix::operator-(const DiagonalMatrix& other) const {
    if (this->rows != other.rows || this->cols != other.cols) {
        return DiagonalMatrix(0);
    }

    DiagonalMatrix result(this->rows);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            if (i == j) {
                double diff = this->getElement(i, j) - other.getElement(i, j);
                result.setElement(i, j, diff);
            }
        }
    }
    return result;
}

DiagonalMatrix DiagonalMatrix::operator*(const DiagonalMatrix& other) const {
    if (this->rows != other.rows || this->cols != other.cols) {
        return DiagonalMatrix(0);
    }

    DiagonalMatrix result(this->rows);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            if (i == j) {
                double prod = this->getElement(i, j) * other.getElement(i, j);
                result.setElement(i, j, prod);
            }
        }
    }
    return result;
}

bool DiagonalMatrix::operator==(const DiagonalMatrix& other) const {
    if (this->rows != other.rows || this->cols != other.cols) {
        return false;
    }
    return this->elements == other.elements;
}