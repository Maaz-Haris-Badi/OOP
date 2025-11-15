#include "Matrix.hpp"

#include <iostream>

Matrix::Matrix(const int rows, const int cols)
    : rows(rows), cols(cols), elements(rows * cols, 0.0) {}

Matrix::Matrix(Matrix const& other)
    : rows(other.rows), cols(other.cols), elements(other.elements) {}

double Matrix::getElement(const int row, const int col) const {
    return elements[row * cols + col];
}

void Matrix::setElement(const int row, const int col, const double value) {
    elements[row * cols + col] = value;
}

int Matrix::getRows() const { return rows; }

int Matrix::getCols() const { return cols; }

int Matrix::getElementsSize() const { return elements.size(); }

Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument(
            "Matrix dimensions must agree for addition.");
    }

    Matrix result(rows, cols);
    for (int i = 0; i < rows * cols; ++i) {
        result.elements[i] = elements[i] + other.elements[i];
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument(
            "Matrix dimensions must agree for subtraction.");
    }

    Matrix result(rows, cols);
    for (int i = 0; i < rows * cols; ++i) {
        result.elements[i] = elements[i] - other.elements[i];
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows) {
        throw std::invalid_argument(
            "Matrix dimensions must agree for multiplication.");
    }

    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < other.cols; ++j) {
            double sum = 0.0;
            for (int k = 0; k < cols; ++k) {
                sum += getElement(i, k) * other.getElement(k, j);
            }
            result.setElement(i, j, sum);
        }
    }
    return result;
}

bool Matrix::operator==(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        return false;
    }

    for (int i = 0; i < rows * cols; ++i) {
        if (elements[i] != other.elements[i]) {
            return false;
        }
    }
    return true;
}