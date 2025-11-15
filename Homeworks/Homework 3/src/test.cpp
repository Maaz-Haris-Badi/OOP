#include <cassert>
#include <iostream>
#include <stdexcept>

#include "Matrix.hpp"

// Helper function to compare doubles with tolerance
bool doubleEquals(double a, double b, double epsilon = 1e-9) {
    return std::abs(a - b) < epsilon;
}

// Helper function to print test results
void printTestResult(const std::string& testName, bool passed) {
    std::cout << "[" << (passed ? "PASS" : "FAIL") << "] " << testName
              << std::endl;
}

// Test 1: Constructor and Basic Getters
void testConstructorAndGetters() {
    std::cout << "\n=== Test 1: Constructor and Getters ===" << std::endl;

    Matrix M(3, 4);
    bool   test1 = (M.getRows() == 3);
    printTestResult("getRows() returns correct value", test1);

    bool test2 = (M.getCols() == 4);
    printTestResult("getCols() returns correct value", test2);

    bool test3 = (M.getElementsSize() == 12);
    printTestResult("getElementsSize() returns rows * cols", test3);

    // Check all elements are initialized to 0.0
    bool allZeros = true;
    for (int i = 0; i < M.getRows(); ++i) {
        for (int j = 0; j < M.getCols(); ++j) {
            if (!doubleEquals(M.getElement(i, j), 0.0)) {
                allZeros = false;
                break;
            }
        }
    }
    printTestResult("All elements initialized to 0.0", allZeros);
}

// Test 2: Copy Constructor
void testCopyConstructor() {
    std::cout << "\n=== Test 2: Copy Constructor ===" << std::endl;

    Matrix A(3, 3);
    A.setElement(0, 0, 1.5);
    A.setElement(1, 1, 42.0);
    A.setElement(2, 2, -7.3);

    Matrix B(A);

    bool dimensionsMatch = (B.getRows() == 3 && B.getCols() == 3);
    printTestResult("Copied matrix has same dimensions", dimensionsMatch);

    bool valuesMatch = doubleEquals(B.getElement(0, 0), 1.5) &&
                       doubleEquals(B.getElement(1, 1), 42.0) &&
                       doubleEquals(B.getElement(2, 2), -7.3);
    printTestResult("Copied matrix has same values", valuesMatch);

    // Test deep copy - modify B and check A is unchanged
    B.setElement(1, 1, 100.0);
    bool deepCopy = doubleEquals(A.getElement(1, 1), 42.0) &&
                    doubleEquals(B.getElement(1, 1), 100.0);
    printTestResult("Deep copy - modifying copy doesn't affect original",
                    deepCopy);
}

// Test 3: Element Access
void testElementAccess() {
    std::cout << "\n=== Test 3: Element Access ===" << std::endl;

    Matrix M(2, 2);
    M.setElement(0, 0, 1.0);
    M.setElement(0, 1, 2.0);
    M.setElement(1, 0, 3.0);
    M.setElement(1, 1, 4.0);

    bool test1 = doubleEquals(M.getElement(0, 0), 1.0);
    printTestResult("Get/Set element (0,0)", test1);

    bool test2 = doubleEquals(M.getElement(0, 1), 2.0);
    printTestResult("Get/Set element (0,1)", test2);

    bool test3 = doubleEquals(M.getElement(1, 0), 3.0);
    printTestResult("Get/Set element (1,0)", test3);

    bool test4 = doubleEquals(M.getElement(1, 1), 4.0);
    printTestResult("Get/Set element (1,1)", test4);
}

// Test 4: Matrix Addition - Valid
void testAdditionValid() {
    std::cout << "\n=== Test 4: Matrix Addition (Valid) ===" << std::endl;

    Matrix A(2, 2);
    A.setElement(0, 0, 1.0);
    A.setElement(0, 1, 2.0);
    A.setElement(1, 0, 3.0);
    A.setElement(1, 1, 4.0);

    Matrix B(2, 2);
    B.setElement(0, 0, 5.0);
    B.setElement(0, 1, 6.0);
    B.setElement(1, 0, 7.0);
    B.setElement(1, 1, 8.0);

    Matrix C = A + B;

    bool test1 = doubleEquals(C.getElement(0, 0), 6.0);
    bool test2 = doubleEquals(C.getElement(0, 1), 8.0);
    bool test3 = doubleEquals(C.getElement(1, 0), 10.0);
    bool test4 = doubleEquals(C.getElement(1, 1), 12.0);

    printTestResult("Addition result (0,0) = 6.0", test1);
    printTestResult("Addition result (0,1) = 8.0", test2);
    printTestResult("Addition result (1,0) = 10.0", test3);
    printTestResult("Addition result (1,1) = 12.0", test4);
}

// Test 5: Matrix Addition - Dimension Mismatch
void testAdditionInvalid() {
    std::cout << "\n=== Test 5: Matrix Addition (Dimension Mismatch) ==="
              << std::endl;

    Matrix A(2, 3);
    Matrix B(3, 2);

    bool exceptionThrown = false;
    try {
        Matrix C = A + B;
    } catch (const std::invalid_argument& e) {
        exceptionThrown = true;
    }

    printTestResult("Exception thrown for mismatched dimensions",
                    exceptionThrown);
}

// Test 6: Matrix Subtraction - Valid
void testSubtractionValid() {
    std::cout << "\n=== Test 6: Matrix Subtraction (Valid) ===" << std::endl;

    Matrix A(2, 2);
    A.setElement(0, 0, 10.0);
    A.setElement(0, 1, 8.0);
    A.setElement(1, 0, 6.0);
    A.setElement(1, 1, 4.0);

    Matrix B(2, 2);
    B.setElement(0, 0, 1.0);
    B.setElement(0, 1, 2.0);
    B.setElement(1, 0, 3.0);
    B.setElement(1, 1, 2.0);

    Matrix C = A - B;

    bool test1 = doubleEquals(C.getElement(0, 0), 9.0);
    bool test2 = doubleEquals(C.getElement(0, 1), 6.0);
    bool test3 = doubleEquals(C.getElement(1, 0), 3.0);
    bool test4 = doubleEquals(C.getElement(1, 1), 2.0);

    printTestResult("Subtraction result (0,0) = 9.0", test1);
    printTestResult("Subtraction result (0,1) = 6.0", test2);
    printTestResult("Subtraction result (1,0) = 3.0", test3);
    printTestResult("Subtraction result (1,1) = 2.0", test4);
}

// Test 7: Matrix Subtraction - Dimension Mismatch
void testSubtractionInvalid() {
    std::cout << "\n=== Test 7: Matrix Subtraction (Dimension Mismatch) ==="
              << std::endl;

    Matrix A(2, 2);
    Matrix B(3, 3);

    bool exceptionThrown = false;
    try {
        Matrix C = A - B;
    } catch (const std::invalid_argument& e) {
        exceptionThrown = true;
    }

    printTestResult("Exception thrown for mismatched dimensions",
                    exceptionThrown);
}

// Test 8: Matrix Multiplication - Valid
void testMultiplicationValid() {
    std::cout << "\n=== Test 8: Matrix Multiplication (Valid) ===" << std::endl;

    // M (2x3) * M1 (3x2) = M4 (2x2)
    Matrix M(2, 3);
    M.setElement(0, 0, 1.0);
    M.setElement(0, 1, 2.0);
    M.setElement(0, 2, 5.0);
    M.setElement(1, 0, 2.0);
    M.setElement(1, 1, 12.0);
    M.setElement(1, 2, 31.0);

    Matrix M1(3, 2);
    M1.setElement(0, 0, 1.0);
    M1.setElement(0, 1, 2.0);
    M1.setElement(1, 0, 3.0);
    M1.setElement(1, 1, 4.0);
    M1.setElement(2, 0, 5.0);
    M1.setElement(2, 1, 6.0);

    Matrix M4 = M * M1;

    // M4[0][0] = 1*1 + 2*3 + 5*5 = 1 + 6 + 25 = 32
    // M4[0][1] = 1*2 + 2*4 + 5*6 = 2 + 8 + 30 = 40
    // M4[1][0] = 2*1 + 12*3 + 31*5 = 2 + 36 + 155 = 193
    // M4[1][1] = 2*2 + 12*4 + 31*6 = 4 + 48 + 186 = 238

    bool test1 = doubleEquals(M4.getElement(0, 0), 32.0);
    bool test2 = doubleEquals(M4.getElement(0, 1), 40.0);
    bool test3 = doubleEquals(M4.getElement(1, 0), 193.0);
    bool test4 = doubleEquals(M4.getElement(1, 1), 238.0);

    printTestResult("Multiplication result (0,0) = 32.0", test1);
    printTestResult("Multiplication result (0,1) = 40.0", test2);
    printTestResult("Multiplication result (1,0) = 193.0", test3);
    printTestResult("Multiplication result (1,1) = 238.0", test4);

    bool dimensionsCorrect = (M4.getRows() == 2 && M4.getCols() == 2);
    printTestResult("Result has correct dimensions (2x2)", dimensionsCorrect);
}

// Test 9: Matrix Multiplication - Dimension Mismatch
void testMultiplicationInvalid() {
    std::cout << "\n=== Test 9: Matrix Multiplication (Dimension Mismatch) ==="
              << std::endl;

    Matrix A(2, 3);
    Matrix B(2, 2);  // A.cols (3) != B.rows (2)

    bool exceptionThrown = false;
    try {
        Matrix C = A * B;
    } catch (const std::invalid_argument& e) {
        exceptionThrown = true;
    }

    printTestResult("Exception thrown for incompatible dimensions",
                    exceptionThrown);
}

// Test 10: Identity Matrix Multiplication
void testIdentityMultiplication() {
    std::cout << "\n=== Test 10: Identity Matrix Multiplication ==="
              << std::endl;

    Matrix A(3, 3);
    A.setElement(0, 0, 1.0);
    A.setElement(0, 1, 2.0);
    A.setElement(0, 2, 3.0);
    A.setElement(1, 0, 4.0);
    A.setElement(1, 1, 5.0);
    A.setElement(1, 2, 6.0);
    A.setElement(2, 0, 7.0);
    A.setElement(2, 1, 8.0);
    A.setElement(2, 2, 9.0);

    Matrix I(3, 3);
    I.setElement(0, 0, 1.0);
    I.setElement(1, 1, 1.0);
    I.setElement(2, 2, 1.0);

    Matrix result = A * I;

    bool allMatch = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (!doubleEquals(result.getElement(i, j), A.getElement(i, j))) {
                allMatch = false;
                break;
            }
        }
    }

    printTestResult("A * I = A (Identity property)", allMatch);
}

// Test 11: Equality Operator - Equal Matrices
void testEqualityTrue() {
    std::cout << "\n=== Test 11: Equality Operator (Equal Matrices) ==="
              << std::endl;

    Matrix A(2, 2);
    A.setElement(0, 0, 1.5);
    A.setElement(0, 1, 2.5);
    A.setElement(1, 0, 3.5);
    A.setElement(1, 1, 4.5);

    Matrix B(2, 2);
    B.setElement(0, 0, 1.5);
    B.setElement(0, 1, 2.5);
    B.setElement(1, 0, 3.5);
    B.setElement(1, 1, 4.5);

    bool equal = (A == B);
    printTestResult("Equal matrices return true", equal);
}

// Test 12: Equality Operator - Different Values
void testEqualityFalseDifferentValues() {
    std::cout << "\n=== Test 12: Equality Operator (Different Values) ==="
              << std::endl;

    Matrix A(2, 2);
    A.setElement(0, 0, 1.0);
    A.setElement(0, 1, 2.0);
    A.setElement(1, 0, 3.0);
    A.setElement(1, 1, 4.0);

    Matrix B(2, 2);
    B.setElement(0, 0, 1.0);
    B.setElement(0, 1, 2.0);
    B.setElement(1, 0, 3.0);
    B.setElement(1, 1, 5.0);  // Different value

    bool notEqual = !(A == B);
    printTestResult("Different values return false", notEqual);
}

// Test 13: Equality Operator - Different Dimensions
void testEqualityFalseDifferentDimensions() {
    std::cout << "\n=== Test 13: Equality Operator (Different Dimensions) ==="
              << std::endl;

    Matrix A(2, 3);
    Matrix B(3, 2);

    bool notEqual = !(A == B);
    printTestResult("Different dimensions return false", notEqual);
}

// Test 14: Single Element Matrix
void testSingleElement() {
    std::cout << "\n=== Test 14: Single Element Matrix ===" << std::endl;

    Matrix A(1, 1);
    A.setElement(0, 0, 42.0);

    bool test1 = doubleEquals(A.getElement(0, 0), 42.0);
    printTestResult("1x1 matrix element access", test1);

    Matrix B(1, 1);
    B.setElement(0, 0, 10.0);

    Matrix C     = A + B;
    bool   test2 = doubleEquals(C.getElement(0, 0), 52.0);
    printTestResult("1x1 matrix addition", test2);

    Matrix D     = A * B;
    bool   test3 = doubleEquals(D.getElement(0, 0), 420.0);
    printTestResult("1x1 matrix multiplication", test3);
}

// Test 15: Chain Operations
void testChainOperations() {
    std::cout << "\n=== Test 15: Chain Operations ===" << std::endl;

    Matrix A(2, 2);
    A.setElement(0, 0, 1.0);
    A.setElement(0, 1, 2.0);
    A.setElement(1, 0, 3.0);
    A.setElement(1, 1, 4.0);

    Matrix B(2, 2);
    B.setElement(0, 0, 5.0);
    B.setElement(0, 1, 6.0);
    B.setElement(1, 0, 7.0);
    B.setElement(1, 1, 8.0);

    Matrix C(2, 2);
    C.setElement(0, 0, 1.0);
    C.setElement(0, 1, 1.0);
    C.setElement(1, 0, 1.0);
    C.setElement(1, 1, 1.0);

    // (A + B) - C
    Matrix result = (A + B) - C;

    bool test1 = doubleEquals(result.getElement(0, 0), 5.0);   // 6 - 1
    bool test2 = doubleEquals(result.getElement(0, 1), 7.0);   // 8 - 1
    bool test3 = doubleEquals(result.getElement(1, 0), 9.0);   // 10 - 1
    bool test4 = doubleEquals(result.getElement(1, 1), 11.0);  // 12 - 1

    printTestResult("Chain operation (A+B)-C (0,0) = 5.0", test1);
    printTestResult("Chain operation (A+B)-C (0,1) = 7.0", test2);
    printTestResult("Chain operation (A+B)-C (1,0) = 9.0", test3);
    printTestResult("Chain operation (A+B)-C (1,1) = 11.0", test4);
}

// Test 16: Zero Matrix Operations
void testZeroMatrix() {
    std::cout << "\n=== Test 16: Zero Matrix Operations ===" << std::endl;

    Matrix A(2, 2);
    A.setElement(0, 0, 5.0);
    A.setElement(0, 1, 10.0);
    A.setElement(1, 0, 15.0);
    A.setElement(1, 1, 20.0);

    Matrix Zero(2, 2);  // All elements are 0.0 by default

    Matrix sum          = A + Zero;
    bool   additionTest = (sum == A);
    printTestResult("A + Zero = A", additionTest);

    Matrix diff            = A - Zero;
    bool   subtractionTest = (diff == A);
    printTestResult("A - Zero = A", subtractionTest);

    Matrix prod               = A * Zero;
    bool   multiplicationTest = (prod == Zero);
    printTestResult("A * Zero = Zero", multiplicationTest);
}

// Test 17: Rectangular Matrix Multiplication
void testRectangularMultiplication() {
    std::cout << "\n=== Test 17: Rectangular Matrix Multiplication ==="
              << std::endl;

    Matrix A(2, 3);
    A.setElement(0, 0, 1.0);
    A.setElement(0, 1, 2.0);
    A.setElement(0, 2, 3.0);
    A.setElement(1, 0, 4.0);
    A.setElement(1, 1, 5.0);
    A.setElement(1, 2, 6.0);

    Matrix B(3, 4);
    B.setElement(0, 0, 1.0);
    B.setElement(0, 1, 0.0);
    B.setElement(0, 2, 0.0);
    B.setElement(0, 3, 0.0);
    B.setElement(1, 0, 0.0);
    B.setElement(1, 1, 1.0);
    B.setElement(1, 2, 0.0);
    B.setElement(1, 3, 0.0);
    B.setElement(2, 0, 0.0);
    B.setElement(2, 1, 0.0);
    B.setElement(2, 2, 1.0);
    B.setElement(2, 3, 0.0);

    Matrix C = A * B;

    bool dimensionsCorrect = (C.getRows() == 2 && C.getCols() == 4);
    printTestResult("Result dimensions are 2x4", dimensionsCorrect);

    bool test1 = doubleEquals(C.getElement(0, 0), 1.0);
    bool test2 = doubleEquals(C.getElement(0, 1), 2.0);
    bool test3 = doubleEquals(C.getElement(0, 2), 3.0);

    printTestResult("2x3 * 3x4 correct calculation", test1 && test2 && test3);
}

// Test 18: Negative Numbers
void testNegativeNumbers() {
    std::cout << "\n=== Test 18: Negative Numbers ===" << std::endl;

    Matrix A(2, 2);
    A.setElement(0, 0, -1.0);
    A.setElement(0, 1, -2.0);
    A.setElement(1, 0, -3.0);
    A.setElement(1, 1, -4.0);

    Matrix B(2, 2);
    B.setElement(0, 0, 5.0);
    B.setElement(0, 1, 6.0);
    B.setElement(1, 0, 7.0);
    B.setElement(1, 1, 8.0);

    Matrix sum   = A + B;
    bool   test1 = doubleEquals(sum.getElement(0, 0), 4.0);
    printTestResult("Addition with negative numbers", test1);

    Matrix diff  = A - B;
    bool   test2 = doubleEquals(diff.getElement(0, 0), -6.0);
    printTestResult("Subtraction with negative numbers", test2);
}

// Main function to run all tests
int main() {
    std::cout << "======================================" << std::endl;
    std::cout << "   MATRIX CLASS COMPREHENSIVE TESTS   " << std::endl;
    std::cout << "======================================" << std::endl;

    testConstructorAndGetters();
    testCopyConstructor();
    testElementAccess();
    testAdditionValid();
    testAdditionInvalid();
    testSubtractionValid();
    testSubtractionInvalid();
    testMultiplicationValid();
    testMultiplicationInvalid();
    testIdentityMultiplication();
    testEqualityTrue();
    testEqualityFalseDifferentValues();
    testEqualityFalseDifferentDimensions();
    testSingleElement();
    testChainOperations();
    testZeroMatrix();
    testRectangularMultiplication();
    testNegativeNumbers();

    std::cout << "\n======================================" << std::endl;
    std::cout << "         ALL TESTS COMPLETED          " << std::endl;
    std::cout << "======================================" << std::endl;

    return 0;
}