#include <iostream>

#include "src/MatrixAlgebraSystem.hpp"

std::ostream& operator<<(std::ostream&, const Matrix&);  // for printing purposes

int main() {
    Matrix* M = new Matrix(2, 3);              // a 2x3 matrix
    Matrix* S = new SquareMatrix(2);           // a 2x2 square matrix
    Matrix* D = new DiagonalMatrix(2);         // a 2x2 diagonal matrix
    Matrix* L = new LowerTriangularMatrix(2);  // a 2x2 lower triangular matrix
    Matrix* U = new UpperTriangularMatrix(2);  // a 2x2 upper triangular matrix

    // Initialize the matrices using setElement
    ///         0   1   2
    /// M = | 1.0 2.0 3.0 | 0
    ///     | 4.0 5.0 6.0 | 1
    M->setElement(0, 0, 1.0);
    M->setElement(0, 1, 2.0);
    M->setElement(0, 2, 3.0);
    M->setElement(1, 0, 4.0);
    M->setElement(1, 1, 5.0);
    M->setElement(1, 2, 6.0);
    std::cout << "M = " << std::endl << *M << std::endl;

    ///         0   1
    /// S = | 1.0 2.0 | 0
    ///     | 3.0 4.0 | 1
    S->setElement(0, 0, 1.0);
    S->setElement(0, 1, 2.0);
    S->setElement(1, 0, 3.0);
    S->setElement(1, 1, 4.0);
    std::cout << "S = " << std::endl << *S << std::endl;

    ///         0   1
    /// D = | 1.0 0.0 | 0
    ///     | 0.0 2.0 | 1
    D->setElement(0, 0, 1.0);
    D->setElement(1, 1, 2.0);
    std::cout << "D = " << std::endl << *D << std::endl;

    ///         0   1
    /// L = | 1.0 0.0 | 0
    ///     | 2.0 3.0 | 1
    L->setElement(0, 0, 1.0);
    L->setElement(1, 0, 2.0);
    L->setElement(1, 1, 3.0);
    std::cout << "L = " << std::endl << *L << std::endl;

    ///         0   1
    /// U = | 1.0 2.0 | 0
    ///     | 0.0 3.0 | 1
    U->setElement(0, 0, 1.0);
    U->setElement(0, 1, 2.0);
    U->setElement(1, 1, 3.0);
    std::cout << "U = " << std::endl << *U << std::endl;

    const Matrix S_plus_D = *S + *D;
    std::cout << "S = " << std::endl << *S << std::endl;
    std::cout << "D = " << std::endl << *D << std::endl;
    std::cout << "S + D = " << std::endl << S_plus_D << std::endl;

    const Matrix L_minus_U = *L - *U;
    std::cout << "L = " << std::endl << *L << std::endl;
    std::cout << "U = " << std::endl << *U << std::endl;
    std::cout << "L - U = " << std::endl << L_minus_U << std::endl;

    return 0;
}

std::ostream& operator<<(std::ostream& os, const Matrix& M) {
    const char open_bracket  = '|';
    const char close_bracket = '|';

    for (int i = 0; i < M.getRows(); ++i) {
        os << open_bracket << ' ';
        for (int j = 0; j < M.getCols(); ++j) {
            os.width(4);
            os << M.getElement(i, j) << " ";
        }
        os << close_bracket;
        os << std::endl;
    }

    return os;
}
