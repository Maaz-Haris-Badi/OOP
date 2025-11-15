// // Test file for CS/CE 224/272 - Assignment #3
// // Matrix Algebra System Test Cases
// // This file tests all matrix classes and their operations

// #include <iostream>
// #include <iomanip>
// #include <cmath>
// #include "Matrix.hpp"
// #include "SquareMatrix.hpp"
// #include "UpperTriangularMatrix.hpp"
// #include "LowerTriangularMatrix.hpp"
// #include "DiagonalMatrix.hpp"

// using namespace std;

// // Helper function to compare doubles
// bool areEqual(double a, double b, double epsilon = 1e-9) {
//     return fabs(a - b) < epsilon;
// }

// // Test result tracking
// int totalTests = 0;
// int passedTests = 0;

// void printTestResult(const string& testName, bool passed) {
//     totalTests++;
//     if (passed) {
//         passedTests++;
//         cout << "[PASS] " << testName << endl;
//     } else {
//         cout << "[FAIL] " << testName << endl;
//     }
// }

// // ==================== MATRIX CLASS TESTS ====================

// void testMatrixConstructors() {
//     cout << "\n=== Testing Matrix Constructors ===" << endl;

//     // Test default constructor
//     // Note: With = default, the constructor doesn't initialize member
//     variables
//     // The test just checks that the default constructor compiles and can be
//     called Matrix m1; printTestResult("Matrix default constructor
//     (compiles)", true);

//     // Test parameterized constructor
//     Matrix m2(3, 4);
//     bool allZero = true;
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 4; j++) {
//             if (!areEqual(m2.getElement(i, j), 0.0)) {
//                 allZero = false;
//             }
//         }
//     }
//     printTestResult("Matrix parameterized constructor (3x4, all zeros)",
//                     m2.getRows() == 3 && m2.getCols() == 4 && allZero);

//     // Test copy constructor
//     Matrix m3(2, 2);
//     m3.setElement(0, 0, 1.5);
//     m3.setElement(0, 1, 2.5);
//     m3.setElement(1, 0, 3.5);
//     m3.setElement(1, 1, 4.5);

//     Matrix m4(m3);
//     bool copyCorrect = areEqual(m4.getElement(0, 0), 1.5) &&
//                        areEqual(m4.getElement(0, 1), 2.5) &&
//                        areEqual(m4.getElement(1, 0), 3.5) &&
//                        areEqual(m4.getElement(1, 1), 4.5);
//     printTestResult("Matrix copy constructor", copyCorrect);
// }

// void testMatrixAccessors() {
//     cout << "\n=== Testing Matrix Accessors ===" << endl;

//     Matrix m(2, 3);
//     m.setElement(0, 0, 1.0);
//     m.setElement(0, 1, 2.0);
//     m.setElement(0, 2, 3.0);
//     m.setElement(1, 0, 4.0);
//     m.setElement(1, 1, 5.0);
//     m.setElement(1, 2, 6.0);

//     bool gettersWork = areEqual(m.getElement(0, 0), 1.0) &&
//                        areEqual(m.getElement(0, 1), 2.0) &&
//                        areEqual(m.getElement(1, 2), 6.0);
//     printTestResult("Matrix getElement", gettersWork);

//     m.setElement(0, 0, 10.0);
//     printTestResult("Matrix setElement", areEqual(m.getElement(0, 0), 10.0));

//     printTestResult("Matrix getRows", m.getRows() == 2);
//     printTestResult("Matrix getCols", m.getCols() == 3);
// }

// void testMatrixAddition() {
//     cout << "\n=== Testing Matrix Addition ===" << endl;

//     Matrix m1(2, 2);
//     m1.setElement(0, 0, 1.0);
//     m1.setElement(0, 1, 2.0);
//     m1.setElement(1, 0, 3.0);
//     m1.setElement(1, 1, 4.0);

//     Matrix m2(2, 2);
//     m2.setElement(0, 0, 5.0);
//     m2.setElement(0, 1, 6.0);
//     m2.setElement(1, 0, 7.0);
//     m2.setElement(1, 1, 8.0);

//     Matrix m3 = m1 + m2;
//     bool addCorrect = areEqual(m3.getElement(0, 0), 6.0) &&
//                       areEqual(m3.getElement(0, 1), 8.0) &&
//                       areEqual(m3.getElement(1, 0), 10.0) &&
//                       areEqual(m3.getElement(1, 1), 12.0);
//     printTestResult("Matrix addition (operator+)", addCorrect);
// }

// void testMatrixSubtraction() {
//     cout << "\n=== Testing Matrix Subtraction ===" << endl;

//     Matrix m1(2, 2);
//     m1.setElement(0, 0, 10.0);
//     m1.setElement(0, 1, 8.0);
//     m1.setElement(1, 0, 6.0);
//     m1.setElement(1, 1, 4.0);

//     Matrix m2(2, 2);
//     m2.setElement(0, 0, 1.0);
//     m2.setElement(0, 1, 2.0);
//     m2.setElement(1, 0, 3.0);
//     m2.setElement(1, 1, 4.0);

//     Matrix m3 = m1 - m2;
//     bool subCorrect = areEqual(m3.getElement(0, 0), 9.0) &&
//                       areEqual(m3.getElement(0, 1), 6.0) &&
//                       areEqual(m3.getElement(1, 0), 3.0) &&
//                       areEqual(m3.getElement(1, 1), 0.0);
//     printTestResult("Matrix subtraction (operator-)", subCorrect);
// }

// void testMatrixMultiplication() {
//     cout << "\n=== Testing Matrix Multiplication ===" << endl;

//     // Test 2x3 * 3x2 = 2x2
//     Matrix m1(2, 3);
//     m1.setElement(0, 0, 1.0);
//     m1.setElement(0, 1, 2.0);
//     m1.setElement(0, 2, 3.0);
//     m1.setElement(1, 0, 4.0);
//     m1.setElement(1, 1, 5.0);
//     m1.setElement(1, 2, 6.0);

//     Matrix m2(3, 2);
//     m2.setElement(0, 0, 7.0);
//     m2.setElement(0, 1, 8.0);
//     m2.setElement(1, 0, 9.0);
//     m2.setElement(1, 1, 10.0);
//     m2.setElement(2, 0, 11.0);
//     m2.setElement(2, 1, 12.0);

//     Matrix m3 = m1 * m2;
//     // [1 2 3]   [7  8]     [58  64]
//     // [4 5 6] * [9 10]  =  [139 154]
//     //           [11 12]
//     bool mulCorrect = m3.getRows() == 2 && m3.getCols() == 2 &&
//                       areEqual(m3.getElement(0, 0), 58.0) &&
//                       areEqual(m3.getElement(0, 1), 64.0) &&
//                       areEqual(m3.getElement(1, 0), 139.0) &&
//                       areEqual(m3.getElement(1, 1), 154.0);
//     printTestResult("Matrix multiplication (operator*)", mulCorrect);
// }

// void testMatrixComparison() {
//     cout << "\n=== Testing Matrix Comparison ===" << endl;

//     Matrix m1(2, 2);
//     m1.setElement(0, 0, 1.0);
//     m1.setElement(0, 1, 2.0);
//     m1.setElement(1, 0, 3.0);
//     m1.setElement(1, 1, 4.0);

//     Matrix m2(2, 2);
//     m2.setElement(0, 0, 1.0);
//     m2.setElement(0, 1, 2.0);
//     m2.setElement(1, 0, 3.0);
//     m2.setElement(1, 1, 4.0);

//     Matrix m3(2, 2);
//     m3.setElement(0, 0, 1.0);
//     m3.setElement(0, 1, 2.0);
//     m3.setElement(1, 0, 3.0);
//     m3.setElement(1, 1, 5.0);

//     printTestResult("Matrix equality (same matrices)", m1 == m2);
//     printTestResult("Matrix equality (different matrices)", !(m1 == m3));
// }

// // ==================== SQUARE MATRIX CLASS TESTS ====================

// void testSquareMatrixConstructors() {
//     cout << "\n=== Testing SquareMatrix Constructors ===" << endl;

//     SquareMatrix s1(3);
//     bool allZero = true;
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 3; j++) {
//             if (!areEqual(s1.getElement(i, j), 0.0)) {
//                 allZero = false;
//             }
//         }
//     }
//     printTestResult("SquareMatrix constructor (3x3, all zeros)",
//                     s1.getRows() == 3 && s1.getCols() == 3 && allZero);

//     SquareMatrix s2(2);
//     s2.setElement(0, 0, 1.0);
//     s2.setElement(0, 1, 2.0);
//     s2.setElement(1, 0, 3.0);
//     s2.setElement(1, 1, 4.0);

//     SquareMatrix s3(s2);
//     bool copyCorrect = areEqual(s3.getElement(0, 0), 1.0) &&
//                        areEqual(s3.getElement(0, 1), 2.0) &&
//                        areEqual(s3.getElement(1, 0), 3.0) &&
//                        areEqual(s3.getElement(1, 1), 4.0);
//     printTestResult("SquareMatrix copy constructor", copyCorrect);
// }

// void testSquareMatrixOperations() {
//     cout << "\n=== Testing SquareMatrix Operations ===" << endl;

//     SquareMatrix s1(2);
//     s1.setElement(0, 0, 1.0);
//     s1.setElement(0, 1, 2.0);
//     s1.setElement(1, 0, 3.0);
//     s1.setElement(1, 1, 4.0);

//     SquareMatrix s2(2);
//     s2.setElement(0, 0, 5.0);
//     s2.setElement(0, 1, 6.0);
//     s2.setElement(1, 0, 7.0);
//     s2.setElement(1, 1, 8.0);

//     SquareMatrix s3 = s1 + s2;
//     bool addCorrect = areEqual(s3.getElement(0, 0), 6.0) &&
//                       areEqual(s3.getElement(0, 1), 8.0) &&
//                       areEqual(s3.getElement(1, 0), 10.0) &&
//                       areEqual(s3.getElement(1, 1), 12.0);
//     printTestResult("SquareMatrix addition", addCorrect);

//     SquareMatrix s4 = s2 - s1;
//     bool subCorrect = areEqual(s4.getElement(0, 0), 4.0) &&
//                       areEqual(s4.getElement(0, 1), 4.0) &&
//                       areEqual(s4.getElement(1, 0), 4.0) &&
//                       areEqual(s4.getElement(1, 1), 4.0);
//     printTestResult("SquareMatrix subtraction", subCorrect);

//     SquareMatrix s5 = s1 * s2;
//     // [1 2]   [5 6]   [19 22]
//     // [3 4] * [7 8] = [43 50]
//     bool mulCorrect = areEqual(s5.getElement(0, 0), 19.0) &&
//                       areEqual(s5.getElement(0, 1), 22.0) &&
//                       areEqual(s5.getElement(1, 0), 43.0) &&
//                       areEqual(s5.getElement(1, 1), 50.0);
//     printTestResult("SquareMatrix multiplication", mulCorrect);

//     printTestResult("SquareMatrix equality", s1 == s1);
// }

// // ==================== LOWER TRIANGULAR MATRIX TESTS ====================

// void testLowerTriangularMatrix() {
//     cout << "\n=== Testing LowerTriangularMatrix ===" << endl;

//     LowerTriangularMatrix l1(3);

//     // Set lower triangular elements
//     l1.setElement(0, 0, 1.0);
//     l1.setElement(1, 0, 2.0);
//     l1.setElement(1, 1, 3.0);
//     l1.setElement(2, 0, 4.0);
//     l1.setElement(2, 1, 5.0);
//     l1.setElement(2, 2, 6.0);

//     // Check that upper triangle is zero
//     bool upperZero = areEqual(l1.getElement(0, 1), 0.0) &&
//                      areEqual(l1.getElement(0, 2), 0.0) &&
//                      areEqual(l1.getElement(1, 2), 0.0);
//     printTestResult("LowerTriangularMatrix upper elements are zero",
//     upperZero);

//     // Check lower triangle values
//     bool lowerCorrect = areEqual(l1.getElement(0, 0), 1.0) &&
//                         areEqual(l1.getElement(1, 0), 2.0) &&
//                         areEqual(l1.getElement(1, 1), 3.0) &&
//                         areEqual(l1.getElement(2, 0), 4.0) &&
//                         areEqual(l1.getElement(2, 1), 5.0) &&
//                         areEqual(l1.getElement(2, 2), 6.0);
//     printTestResult("LowerTriangularMatrix lower elements are correct",
//     lowerCorrect);

//     // Test copy constructor
//     LowerTriangularMatrix l2(l1);
//     bool copyCorrect = areEqual(l2.getElement(1, 0), 2.0) &&
//                        areEqual(l2.getElement(2, 1), 5.0);
//     printTestResult("LowerTriangularMatrix copy constructor", copyCorrect);

//     // Test addition
//     LowerTriangularMatrix l3(3);
//     l3.setElement(0, 0, 1.0);
//     l3.setElement(1, 0, 1.0);
//     l3.setElement(1, 1, 1.0);
//     l3.setElement(2, 0, 1.0);
//     l3.setElement(2, 1, 1.0);
//     l3.setElement(2, 2, 1.0);

//     LowerTriangularMatrix l4 = l1 + l3;
//     bool addCorrect = areEqual(l4.getElement(0, 0), 2.0) &&
//                       areEqual(l4.getElement(1, 0), 3.0) &&
//                       areEqual(l4.getElement(2, 2), 7.0);
//     printTestResult("LowerTriangularMatrix addition", addCorrect);
// }

// // ==================== UPPER TRIANGULAR MATRIX TESTS ====================

// void testUpperTriangularMatrix() {
//     cout << "\n=== Testing UpperTriangularMatrix ===" << endl;

//     UpperTriangularMatrix u1(3);

//     // Set upper triangular elements
//     u1.setElement(0, 0, 1.0);
//     u1.setElement(0, 1, 2.0);
//     u1.setElement(0, 2, 3.0);
//     u1.setElement(1, 1, 4.0);
//     u1.setElement(1, 2, 5.0);
//     u1.setElement(2, 2, 6.0);

//     // Check that lower triangle is zero
//     bool lowerZero = areEqual(u1.getElement(1, 0), 0.0) &&
//                      areEqual(u1.getElement(2, 0), 0.0) &&
//                      areEqual(u1.getElement(2, 1), 0.0);
//     printTestResult("UpperTriangularMatrix lower elements are zero",
//     lowerZero);

//     // Check upper triangle values
//     bool upperCorrect = areEqual(u1.getElement(0, 0), 1.0) &&
//                         areEqual(u1.getElement(0, 1), 2.0) &&
//                         areEqual(u1.getElement(0, 2), 3.0) &&
//                         areEqual(u1.getElement(1, 1), 4.0) &&
//                         areEqual(u1.getElement(1, 2), 5.0) &&
//                         areEqual(u1.getElement(2, 2), 6.0);
//     printTestResult("UpperTriangularMatrix upper elements are correct",
//     upperCorrect);

//     // Test copy constructor
//     UpperTriangularMatrix u2(u1);
//     bool copyCorrect = areEqual(u2.getElement(0, 1), 2.0) &&
//                        areEqual(u2.getElement(1, 2), 5.0);
//     printTestResult("UpperTriangularMatrix copy constructor", copyCorrect);

//     // Test addition
//     UpperTriangularMatrix u3(3);
//     u3.setElement(0, 0, 1.0);
//     u3.setElement(0, 1, 1.0);
//     u3.setElement(0, 2, 1.0);
//     u3.setElement(1, 1, 1.0);
//     u3.setElement(1, 2, 1.0);
//     u3.setElement(2, 2, 1.0);

//     UpperTriangularMatrix u4 = u1 + u3;
//     bool addCorrect = areEqual(u4.getElement(0, 0), 2.0) &&
//                       areEqual(u4.getElement(0, 2), 4.0) &&
//                       areEqual(u4.getElement(2, 2), 7.0);
//     printTestResult("UpperTriangularMatrix addition", addCorrect);
// }

// // ==================== DIAGONAL MATRIX TESTS ====================

// void testDiagonalMatrix() {
//     cout << "\n=== Testing DiagonalMatrix ===" << endl;

//     DiagonalMatrix d1(3);

//     // Set diagonal elements
//     d1.setElement(0, 0, 1.0);
//     d1.setElement(1, 1, 2.0);
//     d1.setElement(2, 2, 3.0);

//     // Check that off-diagonal elements are zero
//     bool offDiagZero = areEqual(d1.getElement(0, 1), 0.0) &&
//                        areEqual(d1.getElement(0, 2), 0.0) &&
//                        areEqual(d1.getElement(1, 0), 0.0) &&
//                        areEqual(d1.getElement(1, 2), 0.0) &&
//                        areEqual(d1.getElement(2, 0), 0.0) &&
//                        areEqual(d1.getElement(2, 1), 0.0);
//     printTestResult("DiagonalMatrix off-diagonal elements are zero",
//     offDiagZero);

//     // Check diagonal values
//     bool diagCorrect = areEqual(d1.getElement(0, 0), 1.0) &&
//                        areEqual(d1.getElement(1, 1), 2.0) &&
//                        areEqual(d1.getElement(2, 2), 3.0);
//     printTestResult("DiagonalMatrix diagonal elements are correct",
//     diagCorrect);

//     // Test copy constructor
//     DiagonalMatrix d2(d1);
//     bool copyCorrect = areEqual(d2.getElement(0, 0), 1.0) &&
//                        areEqual(d2.getElement(1, 1), 2.0) &&
//                        areEqual(d2.getElement(2, 2), 3.0);
//     printTestResult("DiagonalMatrix copy constructor", copyCorrect);

//     // Test addition
//     DiagonalMatrix d3(3);
//     d3.setElement(0, 0, 2.0);
//     d3.setElement(1, 1, 3.0);
//     d3.setElement(2, 2, 4.0);

//     DiagonalMatrix d4 = d1 + d3;
//     bool addCorrect = areEqual(d4.getElement(0, 0), 3.0) &&
//                       areEqual(d4.getElement(1, 1), 5.0) &&
//                       areEqual(d4.getElement(2, 2), 7.0);
//     printTestResult("DiagonalMatrix addition", addCorrect);

//     // Test multiplication
//     DiagonalMatrix d5 = d1 * d3;
//     bool mulCorrect = areEqual(d5.getElement(0, 0), 2.0) &&
//                       areEqual(d5.getElement(1, 1), 6.0) &&
//                       areEqual(d5.getElement(2, 2), 12.0);
//     printTestResult("DiagonalMatrix multiplication", mulCorrect);
// }

// // ==================== ADDITIONAL MATRIX TESTS ====================

// void testMatrixBoundaryAccess() {
//     cout << "\n=== Testing Matrix Boundary Access ===" << endl;

//     Matrix m(3, 4);
//     // Test first element
//     m.setElement(0, 0, 1.0);
//     printTestResult("Matrix access first element (0,0)",
//     areEqual(m.getElement(0, 0), 1.0));

//     // Test last element
//     m.setElement(2, 3, 99.0);
//     printTestResult("Matrix access last element (2,3)",
//     areEqual(m.getElement(2, 3), 99.0));

//     // Test corners
//     m.setElement(0, 3, 10.0);
//     m.setElement(2, 0, 20.0);
//     bool corners = areEqual(m.getElement(0, 3), 10.0) &&
//     areEqual(m.getElement(2, 0), 20.0); printTestResult("Matrix access corner
//     elements", corners);
// }

// void testMatrixAllElements() {
//     cout << "\n=== Testing Matrix All Elements ===" << endl;

//     Matrix m(3, 3);
//     // Set all elements to unique values
//     double val = 1.0;
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 3; j++) {
//             m.setElement(i, j, val);
//             val += 1.0;
//         }
//     }

//     // Verify all elements
//     val = 1.0;
//     bool allCorrect = true;
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 3; j++) {
//             if (!areEqual(m.getElement(i, j), val)) {
//                 allCorrect = false;
//             }
//             val += 1.0;
//         }
//     }
//     printTestResult("Matrix set/get all elements correctly", allCorrect);
// }

// void testMatrixNegativeValues() {
//     cout << "\n=== Testing Matrix with Negative Values ===" << endl;

//     Matrix m(2, 2);
//     m.setElement(0, 0, -5.0);
//     m.setElement(0, 1, -3.0);
//     m.setElement(1, 0, 2.0);
//     m.setElement(1, 1, -7.0);

//     bool negCorrect = areEqual(m.getElement(0, 0), -5.0) &&
//                       areEqual(m.getElement(0, 1), -3.0) &&
//                       areEqual(m.getElement(1, 1), -7.0);
//     printTestResult("Matrix with negative values", negCorrect);
// }

// void testMatrixZeroValues() {
//     cout << "\n=== Testing Matrix with Zero Values ===" << endl;

//     Matrix m(2, 2);
//     m.setElement(0, 0, 0.0);
//     m.setElement(0, 1, 5.0);
//     m.setElement(1, 0, 0.0);
//     m.setElement(1, 1, 0.0);

//     bool zeroCorrect = areEqual(m.getElement(0, 0), 0.0) &&
//                        areEqual(m.getElement(1, 0), 0.0) &&
//                        areEqual(m.getElement(1, 1), 0.0) &&
//                        areEqual(m.getElement(0, 1), 5.0);
//     printTestResult("Matrix with explicit zero values", zeroCorrect);
// }

// void testMatrixLargeValues() {
//     cout << "\n=== Testing Matrix with Large Values ===" << endl;

//     Matrix m(2, 2);
//     m.setElement(0, 0, 1e10);
//     m.setElement(0, 1, 1e-10);
//     m.setElement(1, 0, -1e10);
//     m.setElement(1, 1, 1e15);

//     bool largeCorrect = areEqual(m.getElement(0, 0), 1e10) &&
//                         areEqual(m.getElement(0, 1), 1e-10) &&
//                         areEqual(m.getElement(1, 0), -1e10) &&
//                         areEqual(m.getElement(1, 1), 1e15);
//     printTestResult("Matrix with large/small values", largeCorrect);
// }

// // ==================== COMPREHENSIVE OPERATION TESTS ====================

// void testMatrixAdditionEdgeCases() {
//     cout << "\n=== Testing Matrix Addition Edge Cases ===" << endl;

//     // Adding zero matrices
//     Matrix m1(2, 2);
//     Matrix m2(2, 2);
//     Matrix m3 = m1 + m2;
//     bool zeroSum = areEqual(m3.getElement(0, 0), 0.0) &&
//                    areEqual(m3.getElement(0, 1), 0.0) &&
//                    areEqual(m3.getElement(1, 0), 0.0) &&
//                    areEqual(m3.getElement(1, 1), 0.0);
//     printTestResult("Matrix addition of zero matrices", zeroSum);

//     // Adding negative values
//     m1.setElement(0, 0, -5.0);
//     m1.setElement(0, 1, -3.0);
//     m2.setElement(0, 0, 5.0);
//     m2.setElement(0, 1, 3.0);
//     Matrix m4 = m1 + m2;
//     bool negCancel = areEqual(m4.getElement(0, 0), 0.0) &&
//                      areEqual(m4.getElement(0, 1), 0.0);
//     printTestResult("Matrix addition canceling negatives", negCancel);

//     // 1x1 matrix addition
//     Matrix m5(1, 1);
//     Matrix m6(1, 1);
//     m5.setElement(0, 0, 7.0);
//     m6.setElement(0, 0, 3.0);
//     Matrix m7 = m5 + m6;
//     printTestResult("Matrix addition 1x1", areEqual(m7.getElement(0,
//     0), 10.0));
// }

// void testMatrixSubtractionEdgeCases() {
//     cout << "\n=== Testing Matrix Subtraction Edge Cases ===" << endl;

//     // Self subtraction
//     Matrix m1(2, 2);
//     m1.setElement(0, 0, 5.0);
//     m1.setElement(0, 1, 3.0);
//     m1.setElement(1, 0, 7.0);
//     m1.setElement(1, 1, 2.0);

//     Matrix m2 = m1 - m1;
//     bool selfSubZero = areEqual(m2.getElement(0, 0), 0.0) &&
//                        areEqual(m2.getElement(0, 1), 0.0) &&
//                        areEqual(m2.getElement(1, 0), 0.0) &&
//                        areEqual(m2.getElement(1, 1), 0.0);
//     printTestResult("Matrix self-subtraction gives zero", selfSubZero);

//     // Subtraction resulting in negative
//     Matrix m3(2, 2);
//     m3.setElement(0, 0, 10.0);
//     Matrix m4(2, 2);
//     m4.setElement(0, 0, 15.0);
//     Matrix m5 = m3 - m4;
//     printTestResult("Matrix subtraction resulting in negative",
//     areEqual(m5.getElement(0, 0), -5.0));
// }

// void testMatrixMultiplicationEdgeCases() {
//     cout << "\n=== Testing Matrix Multiplication Edge Cases ===" << endl;

//     // 1x1 multiplication
//     Matrix m1(1, 1);
//     Matrix m2(1, 1);
//     m1.setElement(0, 0, 5.0);
//     m2.setElement(0, 0, 3.0);
//     Matrix m3 = m1 * m2;
//     printTestResult("Matrix multiplication 1x1", areEqual(m3.getElement(0,
//     0), 15.0));

//     // Multiplication with zero matrix
//     Matrix m4(2, 2);
//     m4.setElement(0, 0, 5.0);
//     m4.setElement(0, 1, 3.0);
//     m4.setElement(1, 0, 2.0);
//     m4.setElement(1, 1, 7.0);
//     Matrix m5(2, 2);  // All zeros
//     Matrix m6 = m4 * m5;
//     bool allZero = areEqual(m6.getElement(0, 0), 0.0) &&
//                    areEqual(m6.getElement(0, 1), 0.0) &&
//                    areEqual(m6.getElement(1, 0), 0.0) &&
//                    areEqual(m6.getElement(1, 1), 0.0);
//     printTestResult("Matrix multiplication with zero matrix", allZero);

//     // Non-square multiplication (1x3 * 3x1 = 1x1)
//     Matrix m7(1, 3);
//     m7.setElement(0, 0, 1.0);
//     m7.setElement(0, 1, 2.0);
//     m7.setElement(0, 2, 3.0);
//     Matrix m8(3, 1);
//     m8.setElement(0, 0, 4.0);
//     m8.setElement(1, 0, 5.0);
//     m8.setElement(2, 0, 6.0);
//     Matrix m9 = m7 * m8;
//     // 1*4 + 2*5 + 3*6 = 4 + 10 + 18 = 32
//     printTestResult("Matrix multiplication 1x3 * 3x1",
//                     m9.getRows() == 1 && m9.getCols() == 1 &&
//                     areEqual(m9.getElement(0, 0), 32.0));

//     // Multiplication (3x1 * 1x3 = 3x3)
//     Matrix m10 = m8 * m7;
//     bool correct3x3 = m10.getRows() == 3 && m10.getCols() == 3 &&
//                       areEqual(m10.getElement(0, 0), 4.0) &&  // 4*1
//                       areEqual(m10.getElement(0, 1), 8.0) &&  // 4*2
//                       areEqual(m10.getElement(0, 2), 12.0) && // 4*3
//                       areEqual(m10.getElement(1, 0), 5.0) &&  // 5*1
//                       areEqual(m10.getElement(2, 2), 18.0);   // 6*3
//     printTestResult("Matrix multiplication 3x1 * 1x3", correct3x3);
// }

// // ==================== SQUARE MATRIX COMPREHENSIVE TESTS
// ====================

// void testSquareMatrixSizes() {
//     cout << "\n=== Testing SquareMatrix Different Sizes ===" << endl;

//     // 1x1 square matrix
//     SquareMatrix s1(1);
//     s1.setElement(0, 0, 42.0);
//     printTestResult("SquareMatrix 1x1",
//                     s1.getRows() == 1 && s1.getCols() == 1 &&
//                     areEqual(s1.getElement(0, 0), 42.0));

//     // 2x2 square matrix
//     SquareMatrix s2(2);
//     printTestResult("SquareMatrix 2x2 dimensions", s2.getRows() == 2 &&
//     s2.getCols() == 2);

//     // 5x5 square matrix
//     SquareMatrix s3(5);
//     s3.setElement(4, 4, 25.0);
//     printTestResult("SquareMatrix 5x5",
//                     s3.getRows() == 5 && s3.getCols() == 5 &&
//                     areEqual(s3.getElement(4, 4), 25.0));

//     // 10x10 square matrix
//     SquareMatrix s4(10);
//     s4.setElement(9, 9, 100.0);
//     printTestResult("SquareMatrix 10x10",
//                     s4.getRows() == 10 && s4.getCols() == 10 &&
//                     areEqual(s4.getElement(9, 9), 100.0));
// }

// void testSquareMatrixAllOperations() {
//     cout << "\n=== Testing SquareMatrix All Operations ===" << endl;

//     SquareMatrix s1(2);
//     s1.setElement(0, 0, 2.0);
//     s1.setElement(0, 1, 3.0);
//     s1.setElement(1, 0, 4.0);
//     s1.setElement(1, 1, 5.0);

//     SquareMatrix s2(2);
//     s2.setElement(0, 0, 1.0);
//     s2.setElement(0, 1, 0.0);
//     s2.setElement(1, 0, 0.0);
//     s2.setElement(1, 1, 1.0);

//     // Test all operations preserve square property
//     SquareMatrix s3 = s1 + s2;
//     printTestResult("SquareMatrix addition preserves square",
//                     s3.getRows() == s3.getCols());

//     SquareMatrix s4 = s1 - s2;
//     printTestResult("SquareMatrix subtraction preserves square",
//                     s4.getRows() == s4.getCols());

//     SquareMatrix s5 = s1 * s2;
//     printTestResult("SquareMatrix multiplication preserves square",
//                     s5.getRows() == s5.getCols());
// }

// // ==================== LOWER TRIANGULAR COMPREHENSIVE TESTS
// ====================

// void testLowerTriangularSizes() {
//     cout << "\n=== Testing LowerTriangularMatrix Different Sizes ===" <<
//     endl;

//     // 1x1
//     LowerTriangularMatrix l1(1);
//     l1.setElement(0, 0, 5.0);
//     printTestResult("LowerTriangularMatrix 1x1", areEqual(l1.getElement(0,
//     0), 5.0));

//     // 2x2
//     LowerTriangularMatrix l2(2);
//     l2.setElement(0, 0, 1.0);
//     l2.setElement(1, 0, 2.0);
//     l2.setElement(1, 1, 3.0);
//     bool l2Correct = areEqual(l2.getElement(0, 0), 1.0) &&
//                      areEqual(l2.getElement(1, 0), 2.0) &&
//                      areEqual(l2.getElement(1, 1), 3.0) &&
//                      areEqual(l2.getElement(0, 1), 0.0);
//     printTestResult("LowerTriangularMatrix 2x2", l2Correct);

//     // 5x5
//     LowerTriangularMatrix l3(5);
//     l3.setElement(4, 0, 20.0);
//     l3.setElement(4, 4, 25.0);
//     bool l3Correct = areEqual(l3.getElement(4, 0), 20.0) &&
//                      areEqual(l3.getElement(4, 4), 25.0) &&
//                      areEqual(l3.getElement(0, 4), 0.0);
//     printTestResult("LowerTriangularMatrix 5x5", l3Correct);
// }

// void testLowerTriangularAllPositions() {
//     cout << "\n=== Testing LowerTriangularMatrix All Valid Positions ===" <<
//     endl;

//     LowerTriangularMatrix l(4);
//     // Set all valid lower triangular positions
//     int count = 0;
//     for (int i = 0; i < 4; i++) {
//         for (int j = 0; j <= i; j++) {
//             l.setElement(i, j, static_cast<double>(count));
//             count++;
//         }
//     }

//     // Verify all positions
//     count = 0;
//     bool allCorrect = true;
//     for (int i = 0; i < 4; i++) {
//         for (int j = 0; j <= i; j++) {
//             if (!areEqual(l.getElement(i, j), static_cast<double>(count))) {
//                 allCorrect = false;
//             }
//             count++;
//         }
//     }

//     // Verify upper triangle is zero
//     bool upperZero = true;
//     for (int i = 0; i < 4; i++) {
//         for (int j = i + 1; j < 4; j++) {
//             if (!areEqual(l.getElement(i, j), 0.0)) {
//                 upperZero = false;
//             }
//         }
//     }

//     printTestResult("LowerTriangularMatrix all lower positions", allCorrect);
//     printTestResult("LowerTriangularMatrix all upper positions zero",
//     upperZero);
// }

// void testLowerTriangularOperations() {
//     cout << "\n=== Testing LowerTriangularMatrix Operations ===" << endl;

//     LowerTriangularMatrix l1(3);
//     l1.setElement(0, 0, 1.0);
//     l1.setElement(1, 0, 2.0);
//     l1.setElement(1, 1, 3.0);
//     l1.setElement(2, 0, 4.0);
//     l1.setElement(2, 1, 5.0);
//     l1.setElement(2, 2, 6.0);

//     LowerTriangularMatrix l2(3);
//     l2.setElement(0, 0, 1.0);
//     l2.setElement(1, 0, 1.0);
//     l2.setElement(1, 1, 1.0);
//     l2.setElement(2, 0, 1.0);
//     l2.setElement(2, 1, 1.0);
//     l2.setElement(2, 2, 1.0);

//     // Addition
//     LowerTriangularMatrix l3 = l1 + l2;
//     bool addCorrect = areEqual(l3.getElement(0, 0), 2.0) &&
//                       areEqual(l3.getElement(2, 1), 6.0) &&
//                       areEqual(l3.getElement(0, 2), 0.0);
//     printTestResult("LowerTriangularMatrix addition", addCorrect);

//     // Subtraction
//     LowerTriangularMatrix l4 = l1 - l2;
//     bool subCorrect = areEqual(l4.getElement(0, 0), 0.0) &&
//                       areEqual(l4.getElement(2, 1), 4.0) &&
//                       areEqual(l4.getElement(1, 2), 0.0);
//     printTestResult("LowerTriangularMatrix subtraction", subCorrect);

//     // Multiplication
//     LowerTriangularMatrix l5 = l1 * l2;
//     bool mulDims = l5.getRows() == 3 && l5.getCols() == 3;
//     printTestResult("LowerTriangularMatrix multiplication dimensions",
//     mulDims);

//     // Equality
//     LowerTriangularMatrix l6(l1);
//     printTestResult("LowerTriangularMatrix equality (same)", l1 == l6);
//     printTestResult("LowerTriangularMatrix equality (different)", !(l1 ==
//     l2));
// }

// // ==================== UPPER TRIANGULAR COMPREHENSIVE TESTS
// ====================

// void testUpperTriangularSizes() {
//     cout << "\n=== Testing UpperTriangularMatrix Different Sizes ===" <<
//     endl;

//     // 1x1
//     UpperTriangularMatrix u1(1);
//     u1.setElement(0, 0, 5.0);
//     printTestResult("UpperTriangularMatrix 1x1", areEqual(u1.getElement(0,
//     0), 5.0));

//     // 2x2
//     UpperTriangularMatrix u2(2);
//     u2.setElement(0, 0, 1.0);
//     u2.setElement(0, 1, 2.0);
//     u2.setElement(1, 1, 3.0);
//     bool u2Correct = areEqual(u2.getElement(0, 0), 1.0) &&
//                      areEqual(u2.getElement(0, 1), 2.0) &&
//                      areEqual(u2.getElement(1, 1), 3.0) &&
//                      areEqual(u2.getElement(1, 0), 0.0);
//     printTestResult("UpperTriangularMatrix 2x2", u2Correct);

//     // 5x5
//     UpperTriangularMatrix u3(5);
//     u3.setElement(0, 4, 5.0);
//     u3.setElement(4, 4, 25.0);
//     bool u3Correct = areEqual(u3.getElement(0, 4), 5.0) &&
//                      areEqual(u3.getElement(4, 4), 25.0) &&
//                      areEqual(u3.getElement(4, 0), 0.0);
//     printTestResult("UpperTriangularMatrix 5x5", u3Correct);
// }

// void testUpperTriangularAllPositions() {
//     cout << "\n=== Testing UpperTriangularMatrix All Valid Positions ===" <<
//     endl;

//     UpperTriangularMatrix u(4);
//     // Set all valid upper triangular positions
//     int count = 0;
//     for (int i = 0; i < 4; i++) {
//         for (int j = i; j < 4; j++) {
//             u.setElement(i, j, static_cast<double>(count));
//             count++;
//         }
//     }

//     // Verify all positions
//     count = 0;
//     bool allCorrect = true;
//     for (int i = 0; i < 4; i++) {
//         for (int j = i; j < 4; j++) {
//             if (!areEqual(u.getElement(i, j), static_cast<double>(count))) {
//                 allCorrect = false;
//             }
//             count++;
//         }
//     }

//     // Verify lower triangle is zero
//     bool lowerZero = true;
//     for (int i = 0; i < 4; i++) {
//         for (int j = 0; j < i; j++) {
//             if (!areEqual(u.getElement(i, j), 0.0)) {
//                 lowerZero = false;
//             }
//         }
//     }

//     printTestResult("UpperTriangularMatrix all upper positions", allCorrect);
//     printTestResult("UpperTriangularMatrix all lower positions zero",
//     lowerZero);
// }

// void testUpperTriangularOperations() {
//     cout << "\n=== Testing UpperTriangularMatrix Operations ===" << endl;

//     UpperTriangularMatrix u1(3);
//     u1.setElement(0, 0, 1.0);
//     u1.setElement(0, 1, 2.0);
//     u1.setElement(0, 2, 3.0);
//     u1.setElement(1, 1, 4.0);
//     u1.setElement(1, 2, 5.0);
//     u1.setElement(2, 2, 6.0);

//     UpperTriangularMatrix u2(3);
//     u2.setElement(0, 0, 1.0);
//     u2.setElement(0, 1, 1.0);
//     u2.setElement(0, 2, 1.0);
//     u2.setElement(1, 1, 1.0);
//     u2.setElement(1, 2, 1.0);
//     u2.setElement(2, 2, 1.0);

//     // Addition
//     UpperTriangularMatrix u3 = u1 + u2;
//     bool addCorrect = areEqual(u3.getElement(0, 0), 2.0) &&
//                       areEqual(u3.getElement(0, 2), 4.0) &&
//                       areEqual(u3.getElement(2, 0), 0.0);
//     printTestResult("UpperTriangularMatrix addition", addCorrect);

//     // Subtraction
//     UpperTriangularMatrix u4 = u1 - u2;
//     bool subCorrect = areEqual(u4.getElement(0, 0), 0.0) &&
//                       areEqual(u4.getElement(1, 2), 4.0) &&
//                       areEqual(u4.getElement(2, 1), 0.0);
//     printTestResult("UpperTriangularMatrix subtraction", subCorrect);

//     // Multiplication
//     UpperTriangularMatrix u5 = u1 * u2;
//     bool mulDims = u5.getRows() == 3 && u5.getCols() == 3;
//     printTestResult("UpperTriangularMatrix multiplication dimensions",
//     mulDims);

//     // Equality
//     UpperTriangularMatrix u6(u1);
//     printTestResult("UpperTriangularMatrix equality (same)", u1 == u6);
//     printTestResult("UpperTriangularMatrix equality (different)", !(u1 ==
//     u2));
// }

// // ==================== DIAGONAL MATRIX COMPREHENSIVE TESTS
// ====================

// void testDiagonalSizes() {
//     cout << "\n=== Testing DiagonalMatrix Different Sizes ===" << endl;

//     // 1x1
//     DiagonalMatrix d1(1);
//     d1.setElement(0, 0, 5.0);
//     printTestResult("DiagonalMatrix 1x1", areEqual(d1.getElement(0,
//     0), 5.0));

//     // 2x2
//     DiagonalMatrix d2(2);
//     d2.setElement(0, 0, 1.0);
//     d2.setElement(1, 1, 2.0);
//     bool d2Correct = areEqual(d2.getElement(0, 0), 1.0) &&
//                      areEqual(d2.getElement(1, 1), 2.0) &&
//                      areEqual(d2.getElement(0, 1), 0.0) &&
//                      areEqual(d2.getElement(1, 0), 0.0);
//     printTestResult("DiagonalMatrix 2x2", d2Correct);

//     // 5x5
//     DiagonalMatrix d3(5);
//     d3.setElement(0, 0, 1.0);
//     d3.setElement(4, 4, 25.0);
//     bool d3Correct = areEqual(d3.getElement(0, 0), 1.0) &&
//                      areEqual(d3.getElement(4, 4), 25.0) &&
//                      areEqual(d3.getElement(2, 3), 0.0);
//     printTestResult("DiagonalMatrix 5x5", d3Correct);

//     // 10x10
//     DiagonalMatrix d4(10);
//     d4.setElement(9, 9, 100.0);
//     printTestResult("DiagonalMatrix 10x10", areEqual(d4.getElement(9, 9),
//     100.0));
// }

// void testDiagonalAllPositions() {
//     cout << "\n=== Testing DiagonalMatrix All Positions ===" << endl;

//     DiagonalMatrix d(5);
//     // Set all diagonal positions
//     for (int i = 0; i < 5; i++) {
//         d.setElement(i, i, static_cast<double>(i + 1));
//     }

//     // Verify diagonal
//     bool diagCorrect = true;
//     for (int i = 0; i < 5; i++) {
//         if (!areEqual(d.getElement(i, i), static_cast<double>(i + 1))) {
//             diagCorrect = false;
//         }
//     }

//     // Verify all off-diagonal elements are zero
//     bool offDiagZero = true;
//     for (int i = 0; i < 5; i++) {
//         for (int j = 0; j < 5; j++) {
//             if (i != j && !areEqual(d.getElement(i, j), 0.0)) {
//                 offDiagZero = false;
//             }
//         }
//     }

//     printTestResult("DiagonalMatrix all diagonal positions", diagCorrect);
//     printTestResult("DiagonalMatrix all off-diagonal zero", offDiagZero);
// }

// void testDiagonalOperations() {
//     cout << "\n=== Testing DiagonalMatrix All Operations ===" << endl;

//     DiagonalMatrix d1(3);
//     d1.setElement(0, 0, 2.0);
//     d1.setElement(1, 1, 3.0);
//     d1.setElement(2, 2, 4.0);

//     DiagonalMatrix d2(3);
//     d2.setElement(0, 0, 1.0);
//     d2.setElement(1, 1, 2.0);
//     d2.setElement(2, 2, 3.0);

//     // Addition
//     DiagonalMatrix d3 = d1 + d2;
//     bool addCorrect = areEqual(d3.getElement(0, 0), 3.0) &&
//                       areEqual(d3.getElement(1, 1), 5.0) &&
//                       areEqual(d3.getElement(2, 2), 7.0) &&
//                       areEqual(d3.getElement(0, 1), 0.0);
//     printTestResult("DiagonalMatrix addition", addCorrect);

//     // Subtraction
//     DiagonalMatrix d4 = d1 - d2;
//     bool subCorrect = areEqual(d4.getElement(0, 0), 1.0) &&
//                       areEqual(d4.getElement(1, 1), 1.0) &&
//                       areEqual(d4.getElement(2, 2), 1.0) &&
//                       areEqual(d4.getElement(1, 2), 0.0);
//     printTestResult("DiagonalMatrix subtraction", subCorrect);

//     // Multiplication
//     DiagonalMatrix d5 = d1 * d2;
//     bool mulCorrect = areEqual(d5.getElement(0, 0), 2.0) &&
//                       areEqual(d5.getElement(1, 1), 6.0) &&
//                       areEqual(d5.getElement(2, 2), 12.0) &&
//                       areEqual(d5.getElement(0, 2), 0.0);
//     printTestResult("DiagonalMatrix multiplication", mulCorrect);

//     // Equality
//     DiagonalMatrix d6(d1);
//     printTestResult("DiagonalMatrix equality (same)", d1 == d6);
//     printTestResult("DiagonalMatrix equality (different)", !(d1 == d2));

//     // Identity-like multiplication
//     DiagonalMatrix identity(3);
//     identity.setElement(0, 0, 1.0);
//     identity.setElement(1, 1, 1.0);
//     identity.setElement(2, 2, 1.0);

//     DiagonalMatrix d7 = d1 * identity;
//     bool identityMul = areEqual(d7.getElement(0, 0), 2.0) &&
//                        areEqual(d7.getElement(1, 1), 3.0) &&
//                        areEqual(d7.getElement(2, 2), 4.0);
//     printTestResult("DiagonalMatrix multiplication with identity",
//     identityMul);
// }

// // ==================== EDGE CASES AND SPECIAL TESTS ====================

// void testEdgeCases() {
//     cout << "\n=== Testing Edge Cases ===" << endl;

//     // Test 1x1 matrices
//     Matrix m1(1, 1);
//     m1.setElement(0, 0, 5.0);
//     printTestResult("1x1 Matrix creation and access",
//     areEqual(m1.getElement(0, 0), 5.0));

//     // Test large matrix
//     Matrix m2(100, 100);
//     m2.setElement(50, 50, 42.0);
//     printTestResult("100x100 Matrix creation and access",
//                     m2.getRows() == 100 && m2.getCols() == 100 &&
//                     areEqual(m2.getElement(50, 50), 42.0));

//     // Test very large matrix
//     Matrix m3(200, 150);
//     m3.setElement(199, 149, 999.0);
//     printTestResult("200x150 Matrix boundary access",
//     areEqual(m3.getElement(199, 149), 999.0));
// }

// void testCopyBehavior() {
//     cout << "\n=== Testing Deep Copy Behavior ===" << endl;

//     Matrix m1(2, 2);
//     m1.setElement(0, 0, 10.0);
//     m1.setElement(1, 1, 20.0);

//     Matrix m2(m1);
//     m1.setElement(0, 0, 99.0);

//     printTestResult("Matrix deep copy independence",
//                     areEqual(m2.getElement(0, 0), 10.0) &&
//                     areEqual(m1.getElement(0, 0), 99.0));

//     SquareMatrix s1(2);
//     s1.setElement(0, 0, 5.0);
//     SquareMatrix s2(s1);
//     s1.setElement(0, 0, 15.0);
//     printTestResult("SquareMatrix deep copy independence",
//                     areEqual(s2.getElement(0, 0), 5.0) &&
//                     areEqual(s1.getElement(0, 0), 15.0));
// }

// void testMixedOperations() {
//     cout << "\n=== Testing Mixed/Complex Operations ===" << endl;

//     // (A + B) - B should equal A
//     Matrix a(2, 2);
//     a.setElement(0, 0, 5.0);
//     a.setElement(0, 1, 3.0);
//     a.setElement(1, 0, 2.0);
//     a.setElement(1, 1, 7.0);

//     Matrix b(2, 2);
//     b.setElement(0, 0, 10.0);
//     b.setElement(0, 1, 20.0);
//     b.setElement(1, 0, 30.0);
//     b.setElement(1, 1, 40.0);

//     Matrix result = (a + b) - b;
//     bool mixedCorrect = areEqual(result.getElement(0, 0), 5.0) &&
//                         areEqual(result.getElement(0, 1), 3.0) &&
//                         areEqual(result.getElement(1, 0), 2.0) &&
//                         areEqual(result.getElement(1, 1), 7.0);
//     printTestResult("Matrix (A+B)-B == A", mixedCorrect);

//     // A * (B + C) test
//     Matrix c(2, 2);
//     c.setElement(0, 0, 1.0);
//     c.setElement(0, 1, 0.0);
//     c.setElement(1, 0, 0.0);
//     c.setElement(1, 1, 1.0);

//     Matrix d(2, 2);
//     d.setElement(0, 0, 2.0);
//     d.setElement(0, 1, 3.0);
//     d.setElement(1, 0, 4.0);
//     d.setElement(1, 1, 5.0);

//     Matrix result2 = c * (c + d);
//     // (I + D) * I where I is identity-like
//     bool chainCorrect = areEqual(result2.getElement(0, 0), 3.0) &&
//                         areEqual(result2.getElement(1, 1), 6.0);
//     printTestResult("Matrix chained operations", chainCorrect);
// }

// // ==================== MAIN TEST RUNNER ====================

// int main() {
//     cout << "========================================" << endl;
//     cout << "Matrix Algebra System - Test Suite" << endl;
//     cout << "CS/CE 224/272 - Assignment #3" << endl;
//     cout << "========================================" << endl;

//     // Matrix class tests
//     testMatrixConstructors();
//     testMatrixAccessors();
//     testMatrixBoundaryAccess();
//     testMatrixAllElements();
//     testMatrixNegativeValues();
//     testMatrixZeroValues();
//     testMatrixLargeValues();
//     testMatrixAddition();
//     testMatrixAdditionEdgeCases();
//     testMatrixSubtraction();
//     testMatrixSubtractionEdgeCases();
//     testMatrixMultiplication();
//     testMatrixMultiplicationEdgeCases();
//     testMatrixComparison();

//     // SquareMatrix class tests
//     testSquareMatrixConstructors();
//     testSquareMatrixOperations();
//     testSquareMatrixSizes();
//     testSquareMatrixAllOperations();

//     // LowerTriangularMatrix tests
//     testLowerTriangularMatrix();
//     testLowerTriangularSizes();
//     testLowerTriangularAllPositions();
//     testLowerTriangularOperations();

//     // UpperTriangularMatrix tests
//     testUpperTriangularMatrix();
//     testUpperTriangularSizes();
//     testUpperTriangularAllPositions();
//     testUpperTriangularOperations();

//     // DiagonalMatrix tests
//     testDiagonalMatrix();
//     testDiagonalSizes();
//     testDiagonalAllPositions();
//     testDiagonalOperations();

//     // Edge cases and special tests
//     testEdgeCases();
//     testCopyBehavior();
//     testMixedOperations();

//     // Print summary
//     cout << "\n========================================" << endl;
//     cout << "Test Summary" << endl;
//     cout << "========================================" << endl;
//     cout << "Total Tests: " << totalTests << endl;
//     cout << "Passed: " << passedTests << endl;
//     cout << "Failed: " << (totalTests - passedTests) << endl;
//     cout << "Success Rate: " << fixed << setprecision(1)
//          << (100.0 * passedTests / totalTests) << "%" << endl;
//     cout << "========================================" << endl;

//     return (passedTests == totalTests) ? 0 : 1;
// }

// Test file for CS/CE 224/272 - Assignment #3
// Matrix Algebra System Test Cases
// This file tests all matrix classes and their operations

#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "DiagonalMatrix.hpp"
#include "LowerTriangularMatrix.hpp"
#include "Matrix.hpp"
#include "SquareMatrix.hpp"
#include "UpperTriangularMatrix.hpp"

using namespace std;

// --- ANSI Color Codes for output ---
const string GREEN = "\033[32m";
const string RED   = "\033[31m";
const string RESET = "\033[0m";

// Helper function to compare doubles
bool areEqual(double a, double b, double epsilon = 1e-9) {
    return fabs(a - b) < epsilon;
}

// Test result tracking
int            totalTests  = 0;
int            passedTests = 0;
vector<string> failedTestNames;  // Stores the names of failed tests

// ===================================================================
// ================== TEST HELPER & ASSERTION FUNCTIONS ===================
// ===================================================================

/**
 * @brief Helper function to print a matrix with a title.
 */
void printMatrix(const Matrix& m, const string& title,
                 const string& color = RESET, const string& indent = "      ") {
    cout << indent << color << title << " (" << m.getRows() << "x"
         << m.getCols() << "):" << RESET << endl;
    for (int i = 0; i < m.getRows(); i++) {
        cout << indent;
        for (int j = 0; j < m.getCols(); j++) {
            // Setw(8) gives us some nice spacing
            cout << fixed << setprecision(2) << setw(8) << m.getElement(i, j)
                 << " ";
        }
        cout << endl;
    }
}

// For asserting a condition is true
void testAssertTrue(bool actual, const string& testName) {
    totalTests++;
    if (actual) {
        passedTests++;
        cout << GREEN << "[PASS] " << RESET << testName << endl;
    } else {
        cout << RED << "[FAIL] " << RESET << testName << endl;
        cout << "    Expected: true" << endl;
        cout << "    Your Result: false" << endl;
        failedTestNames.push_back(testName);
    }
}

// For asserting a condition is false
void testAssertFalse(bool actual, const string& testName) {
    totalTests++;
    if (!actual) {
        passedTests++;
        cout << GREEN << "[PASS] " << RESET << testName << endl;
    } else {
        cout << RED << "[FAIL] " << RESET << testName << endl;
        cout << "    Expected: false" << endl;
        cout << "    Your Result: true" << endl;
        failedTestNames.push_back(testName);
    }
}

// For comparing two doubles (uses epsilon)
void testAssertEqual(double expected, double actual, const string& testName) {
    totalTests++;
    if (areEqual(expected, actual)) {
        passedTests++;
        cout << GREEN << "[PASS] " << RESET << testName << endl;
    } else {
        cout << RED << "[FAIL] " << RESET << testName << endl;
        cout << "    Expected: " << expected << endl;
        cout << "    Your Result: " << actual << endl;
        failedTestNames.push_back(testName);
    }
}

// For comparing non-double types (int, size_t, etc.)
template <typename T>
void testAssertEqual(T expected, T actual, const string& testName) {
    totalTests++;
    if (expected == actual) {
        passedTests++;
        cout << GREEN << "[PASS] " << RESET << testName << endl;
    } else {
        cout << RED << "[FAIL] " << RESET << testName << endl;
        cout << "    Expected: " << expected << endl;
        cout << "    Your Result: " << actual << endl;
        failedTestNames.push_back(testName);
    }
}

/**
 * @brief NEW: Asserts that two matrices are equal. If not, prints both.
 */
void testAssertMatrixEqual(const Matrix& expected, const Matrix& actual,
                           const string& testName) {
    totalTests++;
    // We assume operator== is implemented for Matrix and works.
    // That operator is tested separately.
    if (expected == actual) {
        passedTests++;
        cout << GREEN << "[PASS] " << RESET << testName << endl;
    } else {
        cout << RED << "[FAIL] " << RESET << testName << endl;
        // Print both matrices for comparison
        printMatrix(expected, "Expected", GREEN);
        printMatrix(actual, "Your Result", RED);
        failedTestNames.push_back(testName);
    }
}

// ===================================================================
// ======================= MATRIX CLASS TESTS ========================
// ===================================================================

void testMatrixConstructors() {
    cout << "\n=== Testing Matrix Constructors ===" << endl;

    // Test default constructor
    Matrix m1;
    testAssertTrue(true, "Matrix default constructor (compiles)");

    // Test parameterized constructor
    Matrix m2(3, 4);
    testAssertEqual(3, m2.getRows(), "Matrix param constructor (3x4) [Rows]");
    testAssertEqual(4, m2.getCols(), "Matrix param constructor (3x4) [Cols]");

    // Check if it's all zeros
    Matrix m2_expected(3, 4);  // A matrix of all zeros
    testAssertMatrixEqual(m2_expected, m2,
                          "Matrix param constructor (3x4) [All Zeros]");

    // Test copy constructor
    Matrix m3(2, 2);
    m3.setElement(0, 0, 1.5);
    m3.setElement(0, 1, 2.5);
    m3.setElement(1, 0, 3.5);
    m3.setElement(1, 1, 4.5);

    Matrix m4(m3);
    // Here, we're testing the copy, so we compare it to the original m3
    testAssertMatrixEqual(m3, m4, "Matrix copy constructor");
}

void testMatrixAccessors() {
    cout << "\n=== Testing Matrix Accessors ===" << endl;

    Matrix m(2, 3);
    m.setElement(0, 0, 1.0);
    m.setElement(0, 1, 2.0);
    m.setElement(0, 2, 3.0);
    m.setElement(1, 0, 4.0);
    m.setElement(1, 1, 5.0);
    m.setElement(1, 2, 6.0);

    testAssertEqual(1.0, m.getElement(0, 0), "Matrix getElement [0,0]");
    testAssertEqual(2.0, m.getElement(0, 1), "Matrix getElement [0,1]");
    testAssertEqual(6.0, m.getElement(1, 2), "Matrix getElement [1,2]");

    m.setElement(0, 0, 10.0);
    testAssertEqual(10.0, m.getElement(0, 0), "Matrix setElement");

    testAssertEqual(2, m.getRows(), "Matrix getRows");
    testAssertEqual(3, m.getCols(), "Matrix getCols");
}

void testMatrixAddition() {
    cout << "\n=== Testing Matrix Addition ===" << endl;

    Matrix m1(2, 2);
    m1.setElement(0, 0, 1.0);
    m1.setElement(0, 1, 2.0);
    m1.setElement(1, 0, 3.0);
    m1.setElement(1, 1, 4.0);

    Matrix m2(2, 2);
    m2.setElement(0, 0, 5.0);
    m2.setElement(0, 1, 6.0);
    m2.setElement(1, 0, 7.0);
    m2.setElement(1, 1, 8.0);

    // Create the expected result matrix
    Matrix m3_expected(2, 2);
    m3_expected.setElement(0, 0, 6.0);
    m3_expected.setElement(0, 1, 8.0);
    m3_expected.setElement(1, 0, 10.0);
    m3_expected.setElement(1, 1, 12.0);

    Matrix m3_actual = m1 + m2;
    testAssertMatrixEqual(m3_expected, m3_actual,
                          "Matrix addition (operator+)");
}

void testMatrixSubtraction() {
    cout << "\n=== Testing Matrix Subtraction ===" << endl;

    Matrix m1(2, 2);
    m1.setElement(0, 0, 10.0);
    m1.setElement(0, 1, 8.0);
    m1.setElement(1, 0, 6.0);
    m1.setElement(1, 1, 4.0);

    Matrix m2(2, 2);
    m2.setElement(0, 0, 1.0);
    m2.setElement(0, 1, 2.0);
    m2.setElement(1, 0, 3.0);
    m2.setElement(1, 1, 4.0);

    // Create the expected result matrix
    Matrix m3_expected(2, 2);
    m3_expected.setElement(0, 0, 9.0);
    m3_expected.setElement(0, 1, 6.0);
    m3_expected.setElement(1, 0, 3.0);
    m3_expected.setElement(1, 1, 0.0);

    Matrix m3_actual = m1 - m2;
    testAssertMatrixEqual(m3_expected, m3_actual,
                          "Matrix subtraction (operator-)");
}

void testMatrixMultiplication() {
    cout << "\n=== Testing Matrix Multiplication ===" << endl;

    // Test 2x3 * 3x2 = 2x2
    Matrix m1(2, 3);
    m1.setElement(0, 0, 1.0);
    m1.setElement(0, 1, 2.0);
    m1.setElement(0, 2, 3.0);
    m1.setElement(1, 0, 4.0);
    m1.setElement(1, 1, 5.0);
    m1.setElement(1, 2, 6.0);

    Matrix m2(3, 2);
    m2.setElement(0, 0, 7.0);
    m2.setElement(0, 1, 8.0);
    m2.setElement(1, 0, 9.0);
    m2.setElement(1, 1, 10.0);
    m2.setElement(2, 0, 11.0);
    m2.setElement(2, 1, 12.0);

    // Create the expected result matrix
    // [1 2 3]   [7  8]     [58  64]
    // [4 5 6] * [9 10]  =  [139 154]
    //           [11 12]
    Matrix m3_expected(2, 2);
    m3_expected.setElement(0, 0, 58.0);
    m3_expected.setElement(0, 1, 64.0);
    m3_expected.setElement(1, 0, 139.0);
    m3_expected.setElement(1, 1, 154.0);

    Matrix m3_actual = m1 * m2;
    testAssertMatrixEqual(m3_expected, m3_actual,
                          "Matrix multiplication (2x3 * 3x2)");
}

void testMatrixComparison() {
    cout << "\n=== Testing Matrix Comparison ===" << endl;

    Matrix m1(2, 2);
    m1.setElement(0, 0, 1.0);
    m1.setElement(0, 1, 2.0);
    m1.setElement(1, 0, 3.0);
    m1.setElement(1, 1, 4.0);

    Matrix m2(2, 2);
    m2.setElement(0, 0, 1.0);
    m2.setElement(0, 1, 2.0);
    m2.setElement(1, 0, 3.0);
    m2.setElement(1, 1, 4.0);

    Matrix m3(2, 2);
    m3.setElement(0, 0, 1.0);
    m3.setElement(0, 1, 2.0);
    m3.setElement(1, 0, 3.0);
    m3.setElement(1, 1, 5.0);  // Different

    testAssertTrue(m1 == m2, "Matrix equality (same matrices)");
    testAssertFalse(m1 == m3, "Matrix equality (different matrices)");
}

// ==================== SQUARE MATRIX CLASS TESTS ====================

void testSquareMatrixConstructors() {
    cout << "\n=== Testing SquareMatrix Constructors ===" << endl;

    SquareMatrix s1(3);
    testAssertEqual(3, s1.getRows(), "SquareMatrix constructor (3x3) [Rows]");
    testAssertEqual(3, s1.getCols(), "SquareMatrix constructor (3x3) [Cols]");

    SquareMatrix s1_expected(3);  // All zeros
    testAssertMatrixEqual(s1_expected, s1,
                          "SquareMatrix constructor (3x3) [All Zeros]");

    SquareMatrix s2(2);
    s2.setElement(0, 0, 1.0);
    s2.setElement(0, 1, 2.0);
    s2.setElement(1, 0, 3.0);
    s2.setElement(1, 1, 4.0);

    SquareMatrix s3(s2);
    testAssertMatrixEqual(s2, s3, "SquareMatrix copy constructor");
}

void testSquareMatrixOperations() {
    cout << "\n=== Testing SquareMatrix Operations ===" << endl;

    SquareMatrix s1(2);
    s1.setElement(0, 0, 1.0);
    s1.setElement(0, 1, 2.0);
    s1.setElement(1, 0, 3.0);
    s1.setElement(1, 1, 4.0);

    SquareMatrix s2(2);
    s2.setElement(0, 0, 5.0);
    s2.setElement(0, 1, 6.0);
    s2.setElement(1, 0, 7.0);
    s2.setElement(1, 1, 8.0);

    // Test Addition
    SquareMatrix s3_expected(2);
    s3_expected.setElement(0, 0, 6.0);
    s3_expected.setElement(0, 1, 8.0);
    s3_expected.setElement(1, 0, 10.0);
    s3_expected.setElement(1, 1, 12.0);
    SquareMatrix s3_actual = s1 + s2;
    testAssertMatrixEqual(s3_expected, s3_actual, "SquareMatrix addition");

    // Test Subtraction
    SquareMatrix s4_expected(2);
    s4_expected.setElement(0, 0, 4.0);
    s4_expected.setElement(0, 1, 4.0);
    s4_expected.setElement(1, 0, 4.0);
    s4_expected.setElement(1, 1, 4.0);
    SquareMatrix s4_actual = s2 - s1;
    testAssertMatrixEqual(s4_expected, s4_actual, "SquareMatrix subtraction");

    // Test Multiplication
    // [1 2]   [5 6]   [19 22]
    // [3 4] * [7 8] = [43 50]
    SquareMatrix s5_expected(2);
    s5_expected.setElement(0, 0, 19.0);
    s5_expected.setElement(0, 1, 22.0);
    s5_expected.setElement(1, 0, 43.0);
    s5_expected.setElement(1, 1, 50.0);
    SquareMatrix s5_actual = s1 * s2;
    testAssertMatrixEqual(s5_expected, s5_actual,
                          "SquareMatrix multiplication");
}

// ==================== LOWER TRIANGULAR MATRIX TESTS ====================

void testLowerTriangularMatrix() {
    cout << "\n=== Testing LowerTriangularMatrix ===" << endl;

    LowerTriangularMatrix l1(3);
    l1.setElement(0, 0, 1.0);
    l1.setElement(1, 0, 2.0);
    l1.setElement(1, 1, 3.0);
    l1.setElement(2, 0, 4.0);
    l1.setElement(2, 1, 5.0);
    l1.setElement(2, 2, 6.0);

    // Check values
    testAssertEqual(1.0, l1.getElement(0, 0),
                    "LowerTriangularMatrix get [0,0]");
    testAssertEqual(5.0, l1.getElement(2, 1),
                    "LowerTriangularMatrix get [2,1]");
    // Check that upper triangle is zero
    testAssertEqual(0.0, l1.getElement(0, 1),
                    "LowerTriangularMatrix upper element [0,1]");
    testAssertEqual(0.0, l1.getElement(0, 2),
                    "LowerTriangularMatrix upper element [0,2]");
    testAssertEqual(0.0, l1.getElement(1, 2),
                    "LowerTriangularMatrix upper element [1,2]");

    // Test copy constructor
    LowerTriangularMatrix l2(l1);
    testAssertMatrixEqual(l1, l2, "LowerTriangularMatrix copy constructor");

    // Test addition
    LowerTriangularMatrix l3(3);
    l3.setElement(0, 0, 1.0);
    l3.setElement(1, 0, 1.0);
    l3.setElement(1, 1, 1.0);
    l3.setElement(2, 0, 1.0);
    l3.setElement(2, 1, 1.0);
    l3.setElement(2, 2, 1.0);

    LowerTriangularMatrix l4_expected(3);
    l4_expected.setElement(0, 0, 2.0);
    l4_expected.setElement(1, 0, 3.0);
    l4_expected.setElement(1, 1, 4.0);
    l4_expected.setElement(2, 0, 5.0);
    l4_expected.setElement(2, 1, 6.0);
    l4_expected.setElement(2, 2, 7.0);

    LowerTriangularMatrix l4_actual = l1 + l3;
    testAssertMatrixEqual(l4_expected, l4_actual,
                          "LowerTriangularMatrix addition");
}

// ==================== UPPER TRIANGULAR MATRIX TESTS ====================

void testUpperTriangularMatrix() {
    cout << "\n=== Testing UpperTriangularMatrix ===" << endl;

    UpperTriangularMatrix u1(3);
    u1.setElement(0, 0, 1.0);
    u1.setElement(0, 1, 2.0);
    u1.setElement(0, 2, 3.0);
    u1.setElement(1, 1, 4.0);
    u1.setElement(1, 2, 5.0);
    u1.setElement(2, 2, 6.0);

    // Check values
    testAssertEqual(1.0, u1.getElement(0, 0),
                    "UpperTriangularMatrix get [0,0]");
    testAssertEqual(5.0, u1.getElement(1, 2),
                    "UpperTriangularMatrix get [1,2]");
    // Check that lower triangle is zero
    testAssertEqual(0.0, u1.getElement(1, 0),
                    "UpperTriangularMatrix lower element [1,0]");
    testAssertEqual(0.0, u1.getElement(2, 0),
                    "UpperTriangularMatrix lower element [2,0]");
    testAssertEqual(0.0, u1.getElement(2, 1),
                    "UpperTriangularMatrix lower element [2,1]");

    // Test copy constructor
    UpperTriangularMatrix u2(u1);
    testAssertMatrixEqual(u1, u2, "UpperTriangularMatrix copy constructor");

    // Test addition
    UpperTriangularMatrix u3(3);
    u3.setElement(0, 0, 1.0);
    u3.setElement(0, 1, 1.0);
    u3.setElement(0, 2, 1.0);
    u3.setElement(1, 1, 1.0);
    u3.setElement(1, 2, 1.0);
    u3.setElement(2, 2, 1.0);

    UpperTriangularMatrix u4_expected(3);
    u4_expected.setElement(0, 0, 2.0);
    u4_expected.setElement(0, 1, 3.0);
    u4_expected.setElement(0, 2, 4.0);
    u4_expected.setElement(1, 1, 5.0);
    u4_expected.setElement(1, 2, 6.0);
    u4_expected.setElement(2, 2, 7.0);

    UpperTriangularMatrix u4_actual = u1 + u3;
    testAssertMatrixEqual(u4_expected, u4_actual,
                          "UpperTriangularMatrix addition");
}

// ==================== DIAGONAL MATRIX TESTS ====================

void testDiagonalMatrix() {
    cout << "\n=== Testing DiagonalMatrix ===" << endl;

    DiagonalMatrix d1(3);
    d1.setElement(0, 0, 1.0);
    d1.setElement(1, 1, 2.0);
    d1.setElement(2, 2, 3.0);

    // Check values
    testAssertEqual(1.0, d1.getElement(0, 0), "DiagonalMatrix get [0,0]");
    testAssertEqual(2.0, d1.getElement(1, 1), "DiagonalMatrix get [1,1]");
    // Check that off-diagonal elements are zero
    testAssertEqual(0.0, d1.getElement(0, 1),
                    "DiagonalMatrix off-diagonal [0,1]");
    testAssertEqual(0.0, d1.getElement(1, 0),
                    "DiagonalMatrix off-diagonal [1,0]");
    testAssertEqual(0.0, d1.getElement(2, 1),
                    "DiagonalMatrix off-diagonal [2,1]");

    // Test copy constructor
    DiagonalMatrix d2(d1);
    testAssertMatrixEqual(d1, d2, "DiagonalMatrix copy constructor");

    // Test addition
    DiagonalMatrix d3(3);
    d3.setElement(0, 0, 2.0);
    d3.setElement(1, 1, 3.0);
    d3.setElement(2, 2, 4.0);

    DiagonalMatrix d4_expected(3);
    d4_expected.setElement(0, 0, 3.0);
    d4_expected.setElement(1, 1, 5.0);
    d4_expected.setElement(2, 2, 7.0);

    DiagonalMatrix d4_actual = d1 + d3;
    testAssertMatrixEqual(d4_expected, d4_actual, "DiagonalMatrix addition");

    // Test multiplication
    DiagonalMatrix d5_expected(3);
    d5_expected.setElement(0, 0, 2.0);
    d5_expected.setElement(1, 1, 6.0);
    d5_expected.setElement(2, 2, 12.0);

    DiagonalMatrix d5_actual = d1 * d3;
    testAssertMatrixEqual(d5_expected, d5_actual,
                          "DiagonalMatrix multiplication");
}

// ==================== ADDITIONAL MATRIX TESTS ====================

void testMatrixBoundaryAccess() {
    cout << "\n=== Testing Matrix Boundary Access ===" << endl;

    Matrix m(3, 4);
    // Test first element
    m.setElement(0, 0, 1.0);
    testAssertEqual(1.0, m.getElement(0, 0),
                    "Matrix access first element (0,0)");

    // Test last element
    m.setElement(2, 3, 99.0);
    testAssertEqual(99.0, m.getElement(2, 3),
                    "Matrix access last element (2,3)");

    // Test corners
    m.setElement(0, 3, 10.0);
    m.setElement(2, 0, 20.0);
    testAssertEqual(10.0, m.getElement(0, 3),
                    "Matrix access corner element (0,3)");
    testAssertEqual(20.0, m.getElement(2, 0),
                    "Matrix access corner element (2,0)");
}

void testMatrixAllElements() {
    cout << "\n=== Testing Matrix All Elements ===" << endl;

    Matrix m(3, 3);
    Matrix m_expected(3, 3);
    double val = 1.0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            m.setElement(i, j, val);
            m_expected.setElement(i, j, val);
            val += 1.0;
        }
    }
    testAssertMatrixEqual(m_expected, m,
                          "Matrix set/get all elements correctly");
}

void testMatrixNegativeValues() {
    cout << "\n=== Testing Matrix with Negative Values ===" << endl;

    Matrix m(2, 2);
    m.setElement(0, 0, -5.0);
    m.setElement(0, 1, -3.0);
    m.setElement(1, 0, 2.0);
    m.setElement(1, 1, -7.0);

    Matrix m_expected(2, 2);
    m_expected.setElement(0, 0, -5.0);
    m_expected.setElement(0, 1, -3.0);
    m_expected.setElement(1, 0, 2.0);
    m_expected.setElement(1, 1, -7.0);

    testAssertMatrixEqual(m_expected, m, "Matrix with negative values");
}

void testMatrixZeroValues() {
    cout << "\n=== Testing Matrix with Zero Values ===" << endl;

    Matrix m(2, 2);
    m.setElement(0, 0, 0.0);
    m.setElement(0, 1, 5.0);
    m.setElement(1, 0, 0.0);
    m.setElement(1, 1, 0.0);

    Matrix m_expected(2, 2);
    m_expected.setElement(0, 1, 5.0);

    testAssertMatrixEqual(m_expected, m, "Matrix with explicit zero values");
}

void testMatrixLargeValues() {
    cout << "\n=== Testing Matrix with Large Values ===" << endl;

    Matrix m(2, 2);
    m.setElement(0, 0, 1e10);
    m.setElement(0, 1, 1e-10);
    m.setElement(1, 0, -1e10);
    m.setElement(1, 1, 1e15);

    Matrix m_expected(2, 2);
    m_expected.setElement(0, 0, 1e10);
    m_expected.setElement(0, 1, 1e-10);
    m_expected.setElement(1, 0, -1e10);
    m_expected.setElement(1, 1, 1e15);

    testAssertMatrixEqual(m_expected, m, "Matrix with large/small values");
}

// ==================== COMPREHENSIVE OPERATION TESTS ====================

void testMatrixAdditionEdgeCases() {
    cout << "\n=== Testing Matrix Addition Edge Cases ===" << endl;

    // Adding zero matrices
    Matrix m1(2, 2);
    Matrix m2(2, 2);
    Matrix m3_expected(2, 2);  // All zeros
    Matrix m3_actual = m1 + m2;
    testAssertMatrixEqual(m3_expected, m3_actual,
                          "Matrix addition of zero matrices");

    // Adding negative values
    m1.setElement(0, 0, -5.0);
    m1.setElement(0, 1, -3.0);
    m2.setElement(0, 0, 5.0);
    m2.setElement(0, 1, 3.0);
    Matrix m4_expected(2, 2);  // All zeros
    Matrix m4_actual = m1 + m2;
    testAssertMatrixEqual(m4_expected, m4_actual,
                          "Matrix addition canceling negatives");

    // 1x1 matrix addition
    Matrix m5(1, 1);
    Matrix m6(1, 1);
    m5.setElement(0, 0, 7.0);
    m6.setElement(0, 0, 3.0);
    Matrix m7_expected(1, 1);
    m7_expected.setElement(0, 0, 10.0);
    Matrix m7_actual = m5 + m6;
    testAssertMatrixEqual(m7_expected, m7_actual, "Matrix addition 1x1");
}

void testMatrixSubtractionEdgeCases() {
    cout << "\n=== Testing Matrix Subtraction Edge Cases ===" << endl;

    // Self subtraction
    Matrix m1(2, 2);
    m1.setElement(0, 0, 5.0);
    m1.setElement(0, 1, 3.0);
    m1.setElement(1, 0, 7.0);
    m1.setElement(1, 1, 2.0);

    Matrix m2_expected(2, 2);  // All zeros
    Matrix m2_actual = m1 - m1;
    testAssertMatrixEqual(m2_expected, m2_actual,
                          "Matrix self-subtraction gives zero");

    // Subtraction resulting in negative
    Matrix m3(2, 2);
    m3.setElement(0, 0, 10.0);
    Matrix m4(2, 2);
    m4.setElement(0, 0, 15.0);
    Matrix m5_expected(2, 2);
    m5_expected.setElement(0, 0, -5.0);
    Matrix m5_actual = m3 - m4;
    testAssertMatrixEqual(m5_expected, m5_actual,
                          "Matrix subtraction resulting in negative");
}

void testMatrixMultiplicationEdgeCases() {
    cout << "\n=== Testing Matrix Multiplication Edge Cases ===" << endl;

    // 1x1 multiplication
    Matrix m1(1, 1);
    m1.setElement(0, 0, 5.0);
    Matrix m2(1, 1);
    m2.setElement(0, 0, 3.0);
    Matrix m3_expected(1, 1);
    m3_expected.setElement(0, 0, 15.0);
    Matrix m3_actual = m1 * m2;
    testAssertMatrixEqual(m3_expected, m3_actual, "Matrix multiplication 1x1");

    // Multiplication with zero matrix
    Matrix m4(2, 2);
    m4.setElement(0, 0, 5.0);
    m4.setElement(0, 1, 3.0);
    m4.setElement(1, 0, 2.0);
    m4.setElement(1, 1, 7.0);
    Matrix m5(2, 2);           // All zeros
    Matrix m6_expected(2, 2);  // All zeros
    Matrix m6_actual = m4 * m5;
    testAssertMatrixEqual(m6_expected, m6_actual,
                          "Matrix multiplication with zero matrix (A * 0)");
    Matrix m7_actual = m5 * m4;
    testAssertMatrixEqual(m6_expected, m7_actual,
                          "Matrix multiplication with zero matrix (0 * A)");

    // Non-square multiplication (1x3 * 3x1 = 1x1)
    Matrix m8(1, 3);
    m8.setElement(0, 0, 1.0);
    m8.setElement(0, 1, 2.0);
    m8.setElement(0, 2, 3.0);
    Matrix m9(3, 1);
    m9.setElement(0, 0, 4.0);
    m9.setElement(1, 0, 5.0);
    m9.setElement(2, 0, 6.0);
    // 1*4 + 2*5 + 3*6 = 4 + 10 + 18 = 32
    Matrix m10_expected(1, 1);
    m10_expected.setElement(0, 0, 32.0);
    Matrix m10_actual = m8 * m9;
    testAssertMatrixEqual(m10_expected, m10_actual,
                          "Matrix multiplication 1x3 * 3x1");

    // Multiplication (3x1 * 1x3 = 3x3)
    Matrix m11_expected(3, 3);
    m11_expected.setElement(0, 0, 4.0);
    m11_expected.setElement(0, 1, 8.0);
    m11_expected.setElement(0, 2, 12.0);
    m11_expected.setElement(1, 0, 5.0);
    m11_expected.setElement(1, 1, 10.0);
    m11_expected.setElement(1, 2, 15.0);
    m11_expected.setElement(2, 0, 6.0);
    m11_expected.setElement(2, 1, 12.0);
    m11_expected.setElement(2, 2, 18.0);
    Matrix m11_actual = m9 * m8;
    testAssertMatrixEqual(m11_expected, m11_actual,
                          "Matrix multiplication 3x1 * 1x3");
}

// ==================== SQUARE MATRIX COMPREHENSIVE TESTS ====================

void testSquareMatrixSizes() {
    cout << "\n=== Testing SquareMatrix Different Sizes ===" << endl;

    // 1x1 square matrix
    SquareMatrix s1(1);
    s1.setElement(0, 0, 42.0);
    testAssertEqual(1, s1.getRows(), "SquareMatrix 1x1 [Rows]");
    testAssertEqual(1, s1.getCols(), "SquareMatrix 1x1 [Cols]");
    testAssertEqual(42.0, s1.getElement(0, 0), "SquareMatrix 1x1 [Value]");

    // 5x5 square matrix
    SquareMatrix s3(5);
    s3.setElement(4, 4, 25.0);
    testAssertEqual(5, s3.getRows(), "SquareMatrix 5x5 [Rows]");
    testAssertEqual(25.0, s3.getElement(4, 4), "SquareMatrix 5x5 [Value 4,4]");
}

void testSquareMatrixAllOperations() {
    cout << "\n=== Testing SquareMatrix All Operations ===" << endl;

    SquareMatrix s1(2);
    s1.setElement(0, 0, 2.0);
    s1.setElement(0, 1, 3.0);
    s1.setElement(1, 0, 4.0);
    s1.setElement(1, 1, 5.0);

    SquareMatrix s2(2);
    s2.setElement(0, 0, 1.0);
    s2.setElement(0, 1, 0.0);
    s2.setElement(1, 0, 0.0);
    s2.setElement(1, 1, 1.0);  // Identity

    // Test all operations preserve square property
    SquareMatrix s3 = s1 + s2;
    testAssertEqual(2, s3.getRows(),
                    "SquareMatrix addition preserves square [Rows]");
    testAssertEqual(2, s3.getCols(),
                    "SquareMatrix addition preserves square [Cols]");

    SquareMatrix s4 = s1 - s2;
    testAssertEqual(2, s4.getRows(),
                    "SquareMatrix subtraction preserves square [Rows]");
    testAssertEqual(2, s4.getCols(),
                    "SquareMatrix subtraction preserves square [Cols]");

    // Multiplying by identity should return original matrix
    SquareMatrix s5 = s1 * s2;
    testAssertMatrixEqual(s1, s5, "SquareMatrix multiplication by identity");
}

// ==================== LOWER TRIANGULAR COMPREHENSIVE TESTS
// ====================

void testLowerTriangularAllPositions() {
    cout << "\n=== Testing LowerTriangularMatrix All Valid Positions ==="
         << endl;

    LowerTriangularMatrix l(4);
    LowerTriangularMatrix l_expected(4);
    int                   count = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j <= i; j++) {
            l.setElement(i, j, static_cast<double>(count));
            l_expected.setElement(i, j, static_cast<double>(count));
            count++;
        }
    }

    // This one test checks all lower positions AND all upper-zero positions
    testAssertMatrixEqual(l_expected, l, "LowerTriangularMatrix all positions");
}

void testLowerTriangularOperations() {
    cout << "\n=== Testing LowerTriangularMatrix Operations ===" << endl;

    LowerTriangularMatrix l1(3);
    l1.setElement(0, 0, 1.0);
    l1.setElement(1, 0, 2.0);
    l1.setElement(1, 1, 3.0);
    l1.setElement(2, 0, 4.0);
    l1.setElement(2, 1, 5.0);
    l1.setElement(2, 2, 6.0);

    LowerTriangularMatrix l2(3);
    l2.setElement(0, 0, 1.0);
    l2.setElement(1, 0, 1.0);
    l2.setElement(1, 1, 1.0);
    l2.setElement(2, 0, 1.0);
    l2.setElement(2, 1, 1.0);
    l2.setElement(2, 2, 1.0);

    // Addition
    LowerTriangularMatrix l3_expected(3);
    l3_expected.setElement(0, 0, 2.0);
    l3_expected.setElement(1, 0, 3.0);
    l3_expected.setElement(1, 1, 4.0);
    l3_expected.setElement(2, 0, 5.0);
    l3_expected.setElement(2, 1, 6.0);
    l3_expected.setElement(2, 2, 7.0);
    LowerTriangularMatrix l3_actual = l1 + l2;
    testAssertMatrixEqual(l3_expected, l3_actual,
                          "LowerTriangularMatrix addition");

    // Subtraction
    LowerTriangularMatrix l4_expected(3);
    l4_expected.setElement(0, 0, 0.0);
    l4_expected.setElement(1, 0, 1.0);
    l4_expected.setElement(1, 1, 2.0);
    l4_expected.setElement(2, 0, 3.0);
    l4_expected.setElement(2, 1, 4.0);
    l4_expected.setElement(2, 2, 5.0);
    LowerTriangularMatrix l4_actual = l1 - l2;
    testAssertMatrixEqual(l4_expected, l4_actual,
                          "LowerTriangularMatrix subtraction");

    // Equality
    LowerTriangularMatrix l6(l1);
    testAssertTrue(l1 == l6, "LowerTriangularMatrix equality (same)");
    testAssertFalse(l1 == l2, "LowerTriangularMatrix equality (different)");
}

// ==================== UPPER TRIANGULAR COMPREHENSIVE TESTS
// ====================

void testUpperTriangularAllPositions() {
    cout << "\n=== Testing UpperTriangularMatrix All Valid Positions ==="
         << endl;

    UpperTriangularMatrix u(4);
    UpperTriangularMatrix u_expected(4);
    int                   count = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = i; j < 4; j++) {
            u.setElement(i, j, static_cast<double>(count));
            u_expected.setElement(i, j, static_cast<double>(count));
            count++;
        }
    }
    // This one test checks all upper positions AND all lower-zero positions
    testAssertMatrixEqual(u_expected, u, "UpperTriangularMatrix all positions");
}

void testUpperTriangularOperations() {
    cout << "\n=== Testing UpperTriangularMatrix Operations ===" << endl;

    UpperTriangularMatrix u1(3);
    u1.setElement(0, 0, 1.0);
    u1.setElement(0, 1, 2.0);
    u1.setElement(0, 2, 3.0);
    u1.setElement(1, 1, 4.0);
    u1.setElement(1, 2, 5.0);
    u1.setElement(2, 2, 6.0);

    UpperTriangularMatrix u2(3);
    u2.setElement(0, 0, 1.0);
    u2.setElement(0, 1, 1.0);
    u2.setElement(0, 2, 1.0);
    u2.setElement(1, 1, 1.0);
    u2.setElement(1, 2, 1.0);
    u2.setElement(2, 2, 1.0);

    // Addition
    UpperTriangularMatrix u3_expected(3);
    u3_expected.setElement(0, 0, 2.0);
    u3_expected.setElement(0, 1, 3.0);
    u3_expected.setElement(0, 2, 4.0);
    u3_expected.setElement(1, 1, 5.0);
    u3_expected.setElement(1, 2, 6.0);
    u3_expected.setElement(2, 2, 7.0);
    UpperTriangularMatrix u3_actual = u1 + u2;
    testAssertMatrixEqual(u3_expected, u3_actual,
                          "UpperTriangularMatrix addition");

    // Subtraction
    UpperTriangularMatrix u4_expected(3);
    u4_expected.setElement(0, 0, 0.0);
    u4_expected.setElement(0, 1, 1.0);
    u4_expected.setElement(0, 2, 2.0);
    u4_expected.setElement(1, 1, 3.0);
    u4_expected.setElement(1, 2, 4.0);
    u4_expected.setElement(2, 2, 5.0);
    UpperTriangularMatrix u4_actual = u1 - u2;
    testAssertMatrixEqual(u4_expected, u4_actual,
                          "UpperTriangularMatrix subtraction");
}

// ==================== DIAGONAL MATRIX COMPREHENSIVE TESTS ====================

void testDiagonalAllPositions() {
    cout << "\n=== Testing DiagonalMatrix All Positions ===" << endl;

    DiagonalMatrix d(5);
    DiagonalMatrix d_expected(5);
    for (int i = 0; i < 5; i++) {
        d.setElement(i, i, static_cast<double>(i + 1));
        d_expected.setElement(i, i, static_cast<double>(i + 1));
    }

    // This one test checks all diagonal positions AND all off-diagonal-zero
    // positions
    testAssertMatrixEqual(d_expected, d, "DiagonalMatrix all positions");
}

void testDiagonalOperations() {
    cout << "\n=== Testing DiagonalMatrix All Operations ===" << endl;

    DiagonalMatrix d1(3);
    d1.setElement(0, 0, 2.0);
    d1.setElement(1, 1, 3.0);
    d1.setElement(2, 2, 4.0);

    DiagonalMatrix d2(3);
    d2.setElement(0, 0, 1.0);
    d2.setElement(1, 1, 2.0);
    d2.setElement(2, 2, 3.0);

    // Addition
    DiagonalMatrix d3_expected(3);
    d3_expected.setElement(0, 0, 3.0);
    d3_expected.setElement(1, 1, 5.0);
    d3_expected.setElement(2, 2, 7.0);
    DiagonalMatrix d3_actual = d1 + d2;
    testAssertMatrixEqual(d3_expected, d3_actual, "DiagonalMatrix addition");

    // Subtraction
    DiagonalMatrix d4_expected(3);
    d4_expected.setElement(0, 0, 1.0);
    d4_expected.setElement(1, 1, 1.0);
    d4_expected.setElement(2, 2, 1.0);
    DiagonalMatrix d4_actual = d1 - d2;
    testAssertMatrixEqual(d4_expected, d4_actual, "DiagonalMatrix subtraction");

    // Multiplication
    DiagonalMatrix d5_expected(3);
    d5_expected.setElement(0, 0, 2.0);
    d5_expected.setElement(1, 1, 6.0);
    d5_expected.setElement(2, 2, 12.0);
    DiagonalMatrix d5_actual = d1 * d2;
    testAssertMatrixEqual(d5_expected, d5_actual,
                          "DiagonalMatrix multiplication");

    // Identity-like multiplication
    DiagonalMatrix identity(3);
    identity.setElement(0, 0, 1.0);
    identity.setElement(1, 1, 1.0);
    identity.setElement(2, 2, 1.0);

    DiagonalMatrix d7_actual = d1 * identity;
    // d1 * I should just be d1
    testAssertMatrixEqual(d1, d7_actual,
                          "DiagonalMatrix multiplication with identity");
}

// ==================== EDGE CASES AND SPECIAL TESTS ====================

void testEdgeCases() {
    cout << "\n=== Testing Edge Cases ===" << endl;

    // Test 1x1 matrices
    Matrix m1(1, 1);
    m1.setElement(0, 0, 5.0);
    testAssertEqual(5.0, m1.getElement(0, 0), "1x1 Matrix creation and access");

    // Test large matrix
    Matrix m2(100, 100);
    m2.setElement(50, 50, 42.0);
    testAssertEqual(100, m2.getRows(), "100x100 Matrix creation [Rows]");
    testAssertEqual(42.0, m2.getElement(50, 50),
                    "100x100 Matrix access [50,50]");

    // Test very large matrix
    Matrix m3(200, 150);
    m3.setElement(199, 149, 999.0);
    testAssertEqual(999.0, m3.getElement(199, 149),
                    "200x150 Matrix boundary access");
}

void testCopyBehavior() {
    cout << "\n=== Testing Deep Copy Behavior ===" << endl;

    Matrix m1(2, 2);
    m1.setElement(0, 0, 10.0);
    m1.setElement(1, 1, 20.0);

    Matrix m2_expected(m1);  // m2_expected is the "before" state

    Matrix m2(m1);
    m1.setElement(0, 0, 99.0);  // Modify original

    // Test that the copy (m2) is NOT modified
    testAssertMatrixEqual(m2_expected, m2, "Matrix deep copy independence");
    // Test that the original (m1) IS modified
    testAssertEqual(99.0, m1.getElement(0, 0),
                    "Matrix deep copy independence (original modified)");
}

void testMixedOperations() {
    cout << "\n=== Testing Mixed/Complex Operations ===" << endl;

    // (A + B) - B should equal A
    Matrix a(2, 2);
    a.setElement(0, 0, 5.0);
    a.setElement(0, 1, 3.0);
    a.setElement(1, 0, 2.0);
    a.setElement(1, 1, 7.0);

    Matrix b(2, 2);
    b.setElement(0, 0, 10.0);
    b.setElement(0, 1, 20.0);
    b.setElement(1, 0, 30.0);
    b.setElement(1, 1, 40.0);

    Matrix result_actual = (a + b) - b;
    // The expected result is just 'a'
    testAssertMatrixEqual(a, result_actual, "Matrix (A+B)-B == A");

    // A * (B + C) test
    Matrix c(2, 2);  // Identity
    c.setElement(0, 0, 1.0);
    c.setElement(0, 1, 0.0);
    c.setElement(1, 0, 0.0);
    c.setElement(1, 1, 1.0);

    Matrix d(2, 2);
    d.setElement(0, 0, 2.0);
    d.setElement(0, 1, 3.0);
    d.setElement(1, 0, 4.0);
    d.setElement(1, 1, 5.0);

    // We expect C * (C + D) = I * (I + D) = I + D
    Matrix result_expected(2, 2);
    result_expected.setElement(0, 0, 3.0);
    result_expected.setElement(0, 1, 3.0);
    result_expected.setElement(1, 0, 4.0);
    result_expected.setElement(1, 1, 6.0);

    Matrix result2_actual = c * (c + d);
    testAssertMatrixEqual(result_expected, result2_actual,
                          "Matrix chained operations I*(I+D)");
}

// ==================== MAIN TEST RUNNER ====================

int main() {
    cout << "========================================" << endl;
    cout << "Matrix Algebra System - Test Suite" << endl;
    cout << "CS/CE 224/272 - Assignment #3" << endl;
    cout << "========================================" << endl;

    // Matrix class tests
    testMatrixConstructors();
    testMatrixAccessors();
    testMatrixBoundaryAccess();
    testMatrixAllElements();
    testMatrixNegativeValues();
    testMatrixZeroValues();
    testMatrixLargeValues();
    testMatrixAddition();
    testMatrixAdditionEdgeCases();
    testMatrixSubtraction();
    testMatrixSubtractionEdgeCases();
    testMatrixMultiplication();
    testMatrixMultiplicationEdgeCases();
    testMatrixComparison();

    // SquareMatrix class tests
    testSquareMatrixConstructors();
    testSquareMatrixOperations();
    testSquareMatrixSizes();
    testSquareMatrixAllOperations();

    // LowerTriangularMatrix tests
    testLowerTriangularMatrix();
    // testLowerTriangularSizes(); // Covered by other tests
    testLowerTriangularAllPositions();
    testLowerTriangularOperations();

    // UpperTriangularMatrix tests
    testUpperTriangularMatrix();
    // testUpperTriangularSizes(); // Covered by other tests
    testUpperTriangularAllPositions();
    testUpperTriangularOperations();

    // DiagonalMatrix tests
    testDiagonalMatrix();
    // testDiagonalSizes(); // Covered by other tests
    testDiagonalAllPositions();
    testDiagonalOperations();

    // Edge cases and special tests
    testEdgeCases();
    testCopyBehavior();
    testMixedOperations();

    // --- MODIFIED SUMMARY ---

    // Print summary of failed tests if any
    if (passedTests < totalTests) {
        cout << "\n"
             << RED << "========================================" << RESET
             << endl;
        cout << RED << "          Failed Tests Summary" << RESET << endl;
        cout << RED << "========================================" << RESET
             << endl;
        for (const string& failedName : failedTestNames) {
            cout << RED << "  [FAIL] " << RESET << failedName << endl;
        }
    }

    // Print final summary
    cout << "\n========================================" << endl;
    cout << "Final Test Summary" << endl;
    cout << "========================================" << endl;
    cout << "Total Tests: " << totalTests << endl;
    cout << "Passed: " << GREEN << passedTests << RESET << endl;
    cout << "Failed: " << (totalTests - passedTests > 0 ? RED : RESET)
         << (totalTests - passedTests) << RESET << endl;

    // Avoid division by zero if totalTests is 0
    double successRate =
        (totalTests > 0) ? (100.0 * passedTests / totalTests) : 100.0;
    cout << "Success Rate: " << fixed << setprecision(1) << successRate << "%"
         << endl;
    cout << "========================================" << endl;

    return (passedTests == totalTests) ? 0 : 1;
}