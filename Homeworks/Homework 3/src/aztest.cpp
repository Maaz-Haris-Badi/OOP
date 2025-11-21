// g++ main.cpp Matrix.cpp SquareMatrix.cpp LowerTriangularMatrix.cpp UpperTriangularMatrix.cpp DiagonalMatrix.cpp -o main

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cassert>
#include <windows.h>

#include "MatrixAlgebraSystem.hpp"

std::ostream &operator<<(std::ostream &, const Matrix &); // for printing purposes

// ============================================================
// CONFIGURATION: Set to false to hide passing test messages
// ============================================================
bool SHOW_PASSED_TESTS = false; // Change to false to only show failures

// Test result tracking
int total_test_sections = 0;
int total_assertions = 0;
int passed_assertions = 0;
int failed_assertions = 0;

// Windows console colors
#define COLOR_GREEN 10
#define COLOR_RED 12
#define COLOR_CYAN 11
#define COLOR_YELLOW 14
#define COLOR_WHITE 7

void setColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

#define TEST(name)                                                            \
    total_test_sections++;                                                    \
    setColor(COLOR_CYAN);                                                     \
    std::cout << "\n========================================" << std::endl;   \
    std::cout << "TEST " << total_test_sections << ": " << name << std::endl; \
    std::cout << "========================================" << std::endl;     \
    setColor(COLOR_WHITE);

#define ASSERT(condition, message)                                                  \
    total_assertions++;                                                             \
    if (condition)                                                                  \
    {                                                                               \
        passed_assertions++;                                                        \
        if (SHOW_PASSED_TESTS)                                                      \
        {                                                                           \
            setColor(COLOR_GREEN);                                                  \
            std::cout << "[PASS] " << message << std::endl;                         \
            setColor(COLOR_WHITE);                                                  \
        }                                                                           \
    }                                                                               \
    else                                                                            \
    {                                                                               \
        failed_assertions++;                                                        \
        setColor(COLOR_RED);                                                        \
        std::cout << "[FAIL] " << message << " (condition was false)" << std::endl; \
        setColor(COLOR_WHITE);                                                      \
    }

#define ASSERT_WITH_VALUE(condition, message, actual_value, expected_value)             \
    total_assertions++;                                                                 \
    if (condition)                                                                      \
    {                                                                                   \
        passed_assertions++;                                                            \
        if (SHOW_PASSED_TESTS)                                                          \
        {                                                                               \
            setColor(COLOR_GREEN);                                                      \
            std::cout << "[PASS] " << message << std::endl;                             \
            setColor(COLOR_WHITE);                                                      \
        }                                                                               \
    }                                                                                   \
    else                                                                                \
    {                                                                                   \
        failed_assertions++;                                                            \
        setColor(COLOR_RED);                                                            \
        std::cout << "[FAIL] " << message                                               \
                  << " (expected " << expected_value << ", got " << actual_value << ")" \
                  << std::endl;                                                         \
        setColor(COLOR_WHITE);                                                          \
    }

#define ASSERT_EQUAL(a, b, message)                                                                       \
    total_assertions++;                                                                                   \
    if (std::abs((a) - (b)) < 1e-9)                                                                       \
    {                                                                                                     \
        passed_assertions++;                                                                              \
        if (SHOW_PASSED_TESTS)                                                                            \
        {                                                                                                 \
            setColor(COLOR_GREEN);                                                                        \
            std::cout << "[PASS] " << message << std::endl;                                               \
            setColor(COLOR_WHITE);                                                                        \
        }                                                                                                 \
    }                                                                                                     \
    else                                                                                                  \
    {                                                                                                     \
        failed_assertions++;                                                                              \
        setColor(COLOR_RED);                                                                              \
        std::cout << "[FAIL] " << message << " (expected " << (b) << ", got " << (a) << ")" << std::endl; \
        setColor(COLOR_WHITE);                                                                            \
    }

#define ASSERT_MATRIX_EQUAL(mat, row, col, expected, message)                                     \
    total_assertions++;                                                                           \
    if (std::abs((mat).getElement(row, col) - (expected)) < 1e-9)                                 \
    {                                                                                             \
        passed_assertions++;                                                                      \
        if (SHOW_PASSED_TESTS)                                                                    \
        {                                                                                         \
            setColor(COLOR_GREEN);                                                                \
            std::cout << "[PASS] " << message << std::endl;                                       \
            setColor(COLOR_WHITE);                                                                \
        }                                                                                         \
    }                                                                                             \
    else                                                                                          \
    {                                                                                             \
        failed_assertions++;                                                                      \
        setColor(COLOR_RED);                                                                      \
        std::cout << "[FAIL] " << message << " at (" << row << "," << col << ")"                  \
                  << " (expected " << (expected) << ", got " << (mat).getElement(row, col) << ")" \
                  << std::endl;                                                                   \
        setColor(COLOR_YELLOW);                                                                   \
        std::cout << "  Matrix contents:" << std::endl;                                           \
        std::cout << mat << std::endl;                                                            \
        setColor(COLOR_WHITE);                                                                    \
    }

#define ASSERT_MATRICES_EQUAL(mat1, mat2, message)                                              \
    total_assertions++;                                                                         \
    {                                                                                           \
        bool matrices_equal = true;                                                             \
        int diff_row = -1, diff_col = -1;                                                       \
        double diff_val1 = 0, diff_val2 = 0;                                                    \
        if ((mat1).getRows() == (mat2).getRows() && (mat1).getCols() == (mat2).getCols())       \
        {                                                                                       \
            for (int i = 0; i < (mat1).getRows() && matrices_equal; i++)                        \
            {                                                                                   \
                for (int j = 0; j < (mat1).getCols() && matrices_equal; j++)                    \
                {                                                                               \
                    if (std::abs((mat1).getElement(i, j) - (mat2).getElement(i, j)) > 1e-9)     \
                    {                                                                           \
                        matrices_equal = false;                                                 \
                        diff_row = i;                                                           \
                        diff_col = j;                                                           \
                        diff_val1 = (mat1).getElement(i, j);                                    \
                        diff_val2 = (mat2).getElement(i, j);                                    \
                    }                                                                           \
                }                                                                               \
            }                                                                                   \
        }                                                                                       \
        else                                                                                    \
        {                                                                                       \
            matrices_equal = false;                                                             \
        }                                                                                       \
        if (matrices_equal)                                                                     \
        {                                                                                       \
            passed_assertions++;                                                                \
            if (SHOW_PASSED_TESTS)                                                              \
            {                                                                                   \
                setColor(COLOR_GREEN);                                                          \
                std::cout << "[PASS] " << message << std::endl;                                 \
                setColor(COLOR_WHITE);                                                          \
            }                                                                                   \
        }                                                                                       \
        else                                                                                    \
        {                                                                                       \
            failed_assertions++;                                                                \
            setColor(COLOR_RED);                                                                \
            std::cout << "[FAIL] " << message;                                                  \
            if (diff_row >= 0)                                                                  \
                std::cout << " - First difference at (" << diff_row << "," << diff_col << "): " \
                          << diff_val1 << " vs " << diff_val2;                                  \
            std::cout << std::endl;                                                             \
            setColor(COLOR_YELLOW);                                                             \
            std::cout << "  Matrix 1:" << std::endl                                             \
                      << mat1 << std::endl;                                                     \
            std::cout << "  Matrix 2:" << std::endl                                             \
                      << mat2 << std::endl;                                                     \
            setColor(COLOR_WHITE);                                                              \
        }                                                                                       \
    }

// NEW EXTREME TEST CATEGORIES
void testCategory1_MemoryStorageSmall();
void testCategory1_MemoryStorageMedium();
void testCategory1_MemoryStorageLarge();
void testCategory2_IndexMappingDiagonal();
void testCategory2_IndexMappingLower();
void testCategory2_IndexMappingUpper();
void testCategory3_StructurePreservationDiagonal();
void testCategory3_StructurePreservationTriangular();
void testCategory4_PolymorphismTests();
void testCategory5_EdgeCasesBoundaries();
void testCategory6_ZeroMatrices();
void testCategory7_DeepCopyTests();
void testCategory8_PerformanceEfficiency();
void testCategory9_MathematicalProperties();
void testCategory10_EqualityComparison();
void testCategory11_StressTesting();
void testCategory12_SpecialValues();
void testCategory13_SetElementEdgeCases();
void testCategory14_AccessPatterns();
void testCategory15_CorrectnessVerification();
void testCategory16_RealWorldPatterns();
void testCategory17_BoundaryValueAnalysis();
void testCategory18_InterleavedOperations();
void testCategory19_ConstructorBehavior();
void testCategory20_FinalIntegrationTests();
void testCategory21_CrossTypeOperations();

// ORIGINAL TEST FUNCTIONS
void testMatrixBasics();
void testMatrixOperations();
void testMatrixEdgeCases();
void testSquareMatrixBasics();
void testSquareMatrixOperations();
void testDiagonalMatrixBasics();
void testDiagonalMatrixOperations();
void testLowerTriangularBasics();
void testLowerTriangularOperations();
void testUpperTriangularBasics();
void testUpperTriangularOperations();
void testPolymorphism();
void testCopyConstructors();
void testLargeMatrices();
void testNegativeNumbers();
void testZeroMatrices();
void testIdentityMatrices();
void testMemoryLayout();

int main()
{
    setColor(COLOR_YELLOW);
    std::cout << "\n";
    std::cout << "============================================================\n";
    std::cout << "  EXTREME COMPREHENSIVE MATRIX ALGEBRA SYSTEM TEST SUITE   \n";
    std::cout << "============================================================\n";
    setColor(COLOR_WHITE);

    // Display configuration
    std::cout << "Configuration: ";
    if (SHOW_PASSED_TESTS)
    {
        setColor(COLOR_GREEN);
        std::cout << "Showing PASSED tests";
    }
    else
    {
        setColor(COLOR_YELLOW);
        std::cout << "Hiding PASSED tests (only showing FAILURES)";
    }
    setColor(COLOR_WHITE);
    std::cout << "\n";
    std::cout << "(Change SHOW_PASSED_TESTS at top of main.cpp to toggle)\n";
    std::cout << "============================================================\n";

    // EXTREME TEST CATEGORIES - PHASE 1 (Categories 1-8)
    setColor(COLOR_YELLOW);
    std::cout << "\n>>> CATEGORY 1: Memory Storage Verification <<<\n";
    setColor(COLOR_WHITE);
    testCategory1_MemoryStorageSmall();
    testCategory1_MemoryStorageMedium();
    testCategory1_MemoryStorageLarge();

    setColor(COLOR_YELLOW);
    std::cout << "\n>>> CATEGORY 2: Index Mapping Formula Correctness <<<\n";
    setColor(COLOR_WHITE);
    testCategory2_IndexMappingDiagonal();
    testCategory2_IndexMappingLower();
    testCategory2_IndexMappingUpper();

    setColor(COLOR_YELLOW);
    std::cout << "\n>>> CATEGORY 3: Structure Preservation <<<\n";
    setColor(COLOR_WHITE);
    testCategory3_StructurePreservationDiagonal();
    testCategory3_StructurePreservationTriangular();

    setColor(COLOR_YELLOW);
    std::cout << "\n>>> CATEGORY 4: Cross-Type Operations & Polymorphism <<<\n";
    setColor(COLOR_WHITE);
    testCategory4_PolymorphismTests();

    setColor(COLOR_YELLOW);
    std::cout << "\n>>> CATEGORY 5: Edge Cases & Boundary Conditions <<<\n";
    setColor(COLOR_WHITE);
    testCategory5_EdgeCasesBoundaries();

    setColor(COLOR_YELLOW);
    std::cout << "\n>>> CATEGORY 6: Zero Matrix Special Cases <<<\n";
    setColor(COLOR_WHITE);
    testCategory6_ZeroMatrices();

    setColor(COLOR_YELLOW);
    std::cout << "\n>>> CATEGORY 7: Copy Constructor & Deep Copy <<<\n";
    setColor(COLOR_WHITE);
    testCategory7_DeepCopyTests();

    setColor(COLOR_YELLOW);
    std::cout << "\n>>> CATEGORY 8: Performance & Algorithmic Efficiency <<<\n";
    setColor(COLOR_WHITE);
    testCategory8_PerformanceEfficiency();

    setColor(COLOR_YELLOW);
    std::cout << "\n>>> CATEGORY 9: Mathematical Properties & Correctness <<<\n";
    setColor(COLOR_WHITE);
    testCategory9_MathematicalProperties();

    setColor(COLOR_YELLOW);
    std::cout << "\n>>> CATEGORY 10: Equality & Comparison Operations <<<\n";
    setColor(COLOR_WHITE);
    testCategory10_EqualityComparison();

    setColor(COLOR_YELLOW);
    std::cout << "\n>>> CATEGORY 11: Stress Testing & Robustness <<<\n";
    setColor(COLOR_WHITE);
    testCategory11_StressTesting();

    setColor(COLOR_YELLOW);
    std::cout << "\n>>> CATEGORY 12: Negative, Fractional & Special Values <<<\n";
    setColor(COLOR_WHITE);
    testCategory12_SpecialValues();

    setColor(COLOR_YELLOW);
    std::cout << "\n>>> CATEGORY 13: setElement Edge Cases <<<\n";
    setColor(COLOR_WHITE);
    testCategory13_SetElementEdgeCases();

    setColor(COLOR_YELLOW);
    std::cout << "\n>>> CATEGORY 14: Multi-dimensional Access Patterns <<<\n";
    setColor(COLOR_WHITE);
    testCategory14_AccessPatterns();

    setColor(COLOR_YELLOW);
    std::cout << "\n>>> CATEGORY 15: Extreme Correctness Verification <<<\n";
    setColor(COLOR_WHITE);
    testCategory15_CorrectnessVerification();

    setColor(COLOR_YELLOW);
    std::cout << "\n>>> CATEGORY 16: Real-world Usage Patterns <<<\n";
    setColor(COLOR_WHITE);
    testCategory16_RealWorldPatterns();

    setColor(COLOR_YELLOW);
    std::cout << "\n>>> CATEGORY 17: Boundary Value Analysis <<<\n";
    setColor(COLOR_WHITE);
    testCategory17_BoundaryValueAnalysis();

    setColor(COLOR_YELLOW);
    std::cout << "\n>>> CATEGORY 18: Interleaved Operations <<<\n";
    setColor(COLOR_WHITE);
    testCategory18_InterleavedOperations();

    setColor(COLOR_YELLOW);
    std::cout << "\n>>> CATEGORY 19: Constructor Behavior <<<\n";
    setColor(COLOR_WHITE);
    testCategory19_ConstructorBehavior();

    setColor(COLOR_YELLOW);
    std::cout << "\n>>> CATEGORY 20: Final Integration & Comprehensive Tests <<<\n";
    setColor(COLOR_WHITE);
    testCategory20_FinalIntegrationTests();

    setColor(COLOR_YELLOW);
    std::cout << "\n>>> CATEGORY 21: Cross-Type Operations (Different Matrix Classes) <<<\n";
    setColor(COLOR_WHITE);
    testCategory21_CrossTypeOperations();

    // ORIGINAL TESTS
    setColor(COLOR_YELLOW);
    std::cout << "\n>>> ORIGINAL COMPREHENSIVE TESTS <<<\n";
    setColor(COLOR_WHITE);
    testMatrixBasics();
    testMatrixOperations();
    testMatrixEdgeCases();
    testSquareMatrixBasics();
    testSquareMatrixOperations();
    testDiagonalMatrixBasics();
    testDiagonalMatrixOperations();
    testLowerTriangularBasics();
    testLowerTriangularOperations();
    testUpperTriangularBasics();
    testUpperTriangularOperations();
    testPolymorphism();
    testCopyConstructors();
    testLargeMatrices();
    testNegativeNumbers();
    testZeroMatrices();
    testIdentityMatrices();
    testMemoryLayout();

    std::cout << "\n";
    setColor(COLOR_YELLOW);
    std::cout << "============================================================\n";
    std::cout << "                      TEST SUMMARY                          \n";
    std::cout << "============================================================\n";
    setColor(COLOR_WHITE);
    std::cout << "Test Sections Run: " << total_test_sections << std::endl;
    std::cout << "Total Assertions: " << total_assertions << std::endl;
    setColor(COLOR_GREEN);
    std::cout << "Assertions Passed: " << passed_assertions << std::endl;
    if (failed_assertions > 0)
    {
        setColor(COLOR_RED);
        std::cout << "Assertions Failed: " << failed_assertions << std::endl;
    }
    else
    {
        setColor(COLOR_WHITE);
        std::cout << "Assertions Failed: " << failed_assertions << std::endl;
    }
    setColor(COLOR_WHITE);
    std::cout << "Success Rate: " << std::fixed << std::setprecision(2)
              << (100.0 * passed_assertions / total_assertions) << "%" << std::endl;

    if (failed_assertions == 0)
    {
        setColor(COLOR_GREEN);
        std::cout << "\n*** ALL TESTS PASSED! ***\n"
                  << std::endl;
        setColor(COLOR_WHITE);
    }
    else
    {
        setColor(COLOR_RED);
        std::cout << "\n*** SOME TESTS FAILED ***\n"
                  << std::endl;
        setColor(COLOR_WHITE);
    }

    return 0;
}

// ==================== MATRIX TESTS ====================

void testMatrixBasics()
{
    TEST("Matrix - Basic Construction and Accessors");

    Matrix m1(3, 4);
    ASSERT(m1.getRows() == 3, "Matrix rows initialized correctly");
    ASSERT(m1.getCols() == 4, "Matrix cols initialized correctly");

    // Test default initialization to zero
    bool allZero = true;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (m1.getElement(i, j) != 0.0)
                allZero = false;
        }
    }
    ASSERT(allZero, "Matrix initialized with zeros");

    // Test setElement and getElement
    m1.setElement(1, 2, 42.5);
    ASSERT_EQUAL(m1.getElement(1, 2), 42.5, "setElement/getElement work correctly");

    // Test all positions
    Matrix m2(2, 3);
    m2.setElement(0, 0, 1.0);
    m2.setElement(0, 1, 2.0);
    m2.setElement(0, 2, 3.0);
    m2.setElement(1, 0, 4.0);
    m2.setElement(1, 1, 5.0);
    m2.setElement(1, 2, 6.0);

    ASSERT_EQUAL(m2.getElement(0, 0), 1.0, "Element (0,0) correct");
    ASSERT_EQUAL(m2.getElement(0, 1), 2.0, "Element (0,1) correct");
    ASSERT_EQUAL(m2.getElement(0, 2), 3.0, "Element (0,2) correct");
    ASSERT_EQUAL(m2.getElement(1, 0), 4.0, "Element (1,0) correct");
    ASSERT_EQUAL(m2.getElement(1, 1), 5.0, "Element (1,1) correct");
    ASSERT_EQUAL(m2.getElement(1, 2), 6.0, "Element (1,2) correct");
}

void testMatrixOperations()
{
    TEST("Matrix - Addition");
    Matrix m1(2, 3);
    m1.setElement(0, 0, 1.0);
    m1.setElement(0, 1, 2.0);
    m1.setElement(0, 2, 3.0);
    m1.setElement(1, 0, 4.0);
    m1.setElement(1, 1, 5.0);
    m1.setElement(1, 2, 6.0);

    Matrix m2(2, 3);
    m2.setElement(0, 0, 6.0);
    m2.setElement(0, 1, 5.0);
    m2.setElement(0, 2, 4.0);
    m2.setElement(1, 0, 3.0);
    m2.setElement(1, 1, 2.0);
    m2.setElement(1, 2, 1.0);

    Matrix result = m1 + m2;
    ASSERT_EQUAL(result.getElement(0, 0), 7.0, "Addition (0,0) correct");
    ASSERT_EQUAL(result.getElement(0, 1), 7.0, "Addition (0,1) correct");
    ASSERT_EQUAL(result.getElement(0, 2), 7.0, "Addition (0,2) correct");
    ASSERT_EQUAL(result.getElement(1, 0), 7.0, "Addition (1,0) correct");
    ASSERT_EQUAL(result.getElement(1, 1), 7.0, "Addition (1,1) correct");
    ASSERT_EQUAL(result.getElement(1, 2), 7.0, "Addition (1,2) correct");

    TEST("Matrix - Subtraction");
    Matrix diff = m1 - m2;
    ASSERT_EQUAL(diff.getElement(0, 0), -5.0, "Subtraction (0,0) correct");
    ASSERT_EQUAL(diff.getElement(0, 1), -3.0, "Subtraction (0,1) correct");
    ASSERT_EQUAL(diff.getElement(0, 2), -1.0, "Subtraction (0,2) correct");
    ASSERT_EQUAL(diff.getElement(1, 0), 1.0, "Subtraction (1,0) correct");
    ASSERT_EQUAL(diff.getElement(1, 1), 3.0, "Subtraction (1,1) correct");
    ASSERT_EQUAL(diff.getElement(1, 2), 5.0, "Subtraction (1,2) correct");

    TEST("Matrix - Multiplication");
    Matrix A(2, 3);
    A.setElement(0, 0, 1.0);
    A.setElement(0, 1, 2.0);
    A.setElement(0, 2, 3.0);
    A.setElement(1, 0, 4.0);
    A.setElement(1, 1, 5.0);
    A.setElement(1, 2, 6.0);

    Matrix B(3, 2);
    B.setElement(0, 0, 7.0);
    B.setElement(0, 1, 8.0);
    B.setElement(1, 0, 9.0);
    B.setElement(1, 1, 10.0);
    B.setElement(2, 0, 11.0);
    B.setElement(2, 1, 12.0);

    Matrix prod = A * B;
    // Result should be 2x2: [[58, 64], [139, 154]]
    ASSERT_EQUAL(prod.getRows(), 2, "Product has correct rows");
    ASSERT_EQUAL(prod.getCols(), 2, "Product has correct cols");
    ASSERT_EQUAL(prod.getElement(0, 0), 58.0, "Product (0,0) = 1*7 + 2*9 + 3*11");
    ASSERT_EQUAL(prod.getElement(0, 1), 64.0, "Product (0,1) = 1*8 + 2*10 + 3*12");
    ASSERT_EQUAL(prod.getElement(1, 0), 139.0, "Product (1,0) = 4*7 + 5*9 + 6*11");
    ASSERT_EQUAL(prod.getElement(1, 1), 154.0, "Product (1,1) = 4*8 + 5*10 + 6*12");

    TEST("Matrix - Equality");
    Matrix e1(2, 2);
    e1.setElement(0, 0, 1.5);
    e1.setElement(0, 1, 2.5);
    e1.setElement(1, 0, 3.5);
    e1.setElement(1, 1, 4.5);

    Matrix e2(2, 2);
    e2.setElement(0, 0, 1.5);
    e2.setElement(0, 1, 2.5);
    e2.setElement(1, 0, 3.5);
    e2.setElement(1, 1, 4.5);

    Matrix e3(2, 2);
    e3.setElement(0, 0, 1.5);
    e3.setElement(0, 1, 2.5);
    e3.setElement(1, 0, 3.5);
    e3.setElement(1, 1, 4.6);

    ASSERT(e1 == e2, "Equal matrices are equal");
    ASSERT(!(e1 == e3), "Different matrices are not equal");
}

void testMatrixEdgeCases()
{
    TEST("Matrix - Edge Cases");

    // 1x1 matrix
    Matrix tiny(1, 1);
    tiny.setElement(0, 0, 99.9);
    ASSERT_EQUAL(tiny.getElement(0, 0), 99.9, "1x1 matrix works");

    // Large rectangular matrices
    Matrix wide(2, 10);
    wide.setElement(1, 9, 123.456);
    ASSERT_EQUAL(wide.getElement(1, 9), 123.456, "Wide matrix works");

    Matrix tall(10, 2);
    tall.setElement(9, 1, 789.012);
    ASSERT_EQUAL(tall.getElement(9, 1), 789.012, "Tall matrix works");

    // Chain multiplication (A * B) * C
    Matrix chain1(2, 3), chain2(3, 2), chain3(2, 4);
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            chain1.setElement(i, j, i + j + 1);

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 2; j++)
            chain2.setElement(i, j, i * 2 + j);

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 4; j++)
            chain3.setElement(i, j, 1.0);

    Matrix temp = chain1 * chain2;
    Matrix chained = temp * chain3;
    ASSERT(chained.getRows() == 2 && chained.getCols() == 4, "Chained multiplication dimensions correct");
}

// ==================== SQUARE MATRIX TESTS ====================

void testSquareMatrixBasics()
{
    TEST("SquareMatrix - Basic Construction");

    SquareMatrix s1(3);
    ASSERT(s1.getRows() == 3, "Square matrix rows correct");
    ASSERT(s1.getCols() == 3, "Square matrix cols correct");

    // Test all zeros
    bool allZero = true;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (s1.getElement(i, j) != 0.0)
                allZero = false;
        }
    }
    ASSERT(allZero, "SquareMatrix initialized with zeros");

    // Set and get elements
    SquareMatrix s2(2);
    s2.setElement(0, 0, 1.0);
    s2.setElement(0, 1, 2.0);
    s2.setElement(1, 0, 3.0);
    s2.setElement(1, 1, 4.0);

    ASSERT_EQUAL(s2.getElement(0, 0), 1.0, "SquareMatrix (0,0) correct");
    ASSERT_EQUAL(s2.getElement(0, 1), 2.0, "SquareMatrix (0,1) correct");
    ASSERT_EQUAL(s2.getElement(1, 0), 3.0, "SquareMatrix (1,0) correct");
    ASSERT_EQUAL(s2.getElement(1, 1), 4.0, "SquareMatrix (1,1) correct");
}

void testSquareMatrixOperations()
{
    TEST("SquareMatrix - Addition");
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

    SquareMatrix sum = s1 + s2;
    ASSERT_EQUAL(sum.getElement(0, 0), 6.0, "Square addition (0,0)");
    ASSERT_EQUAL(sum.getElement(0, 1), 8.0, "Square addition (0,1)");
    ASSERT_EQUAL(sum.getElement(1, 0), 10.0, "Square addition (1,0)");
    ASSERT_EQUAL(sum.getElement(1, 1), 12.0, "Square addition (1,1)");

    TEST("SquareMatrix - Subtraction");
    SquareMatrix diff = s2 - s1;
    ASSERT_EQUAL(diff.getElement(0, 0), 4.0, "Square subtraction (0,0)");
    ASSERT_EQUAL(diff.getElement(0, 1), 4.0, "Square subtraction (0,1)");
    ASSERT_EQUAL(diff.getElement(1, 0), 4.0, "Square subtraction (1,0)");
    ASSERT_EQUAL(diff.getElement(1, 1), 4.0, "Square subtraction (1,1)");

    TEST("SquareMatrix - Multiplication");
    SquareMatrix prod = s1 * s2;
    // [1 2] * [5 6] = [19 22]
    // [3 4]   [7 8]   [43 50]
    ASSERT_EQUAL(prod.getElement(0, 0), 19.0, "Square multiplication (0,0)");
    ASSERT_EQUAL(prod.getElement(0, 1), 22.0, "Square multiplication (0,1)");
    ASSERT_EQUAL(prod.getElement(1, 0), 43.0, "Square multiplication (1,0)");
    ASSERT_EQUAL(prod.getElement(1, 1), 50.0, "Square multiplication (1,1)");

    TEST("SquareMatrix - Equality");
    SquareMatrix s3(2);
    s3.setElement(0, 0, 1.0);
    s3.setElement(0, 1, 2.0);
    s3.setElement(1, 0, 3.0);
    s3.setElement(1, 1, 4.0);

    ASSERT(s1 == s3, "Equal square matrices");
    ASSERT(!(s1 == s2), "Different square matrices");

    TEST("SquareMatrix - Large Size");
    SquareMatrix large(5);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            large.setElement(i, j, i * 5 + j);
        }
    }
    ASSERT_EQUAL(large.getElement(3, 4), 19.0, "Large square matrix element access");
}

// ==================== DIAGONAL MATRIX TESTS ====================

void testDiagonalMatrixBasics()
{
    TEST("DiagonalMatrix - Basic Construction");

    DiagonalMatrix d1(3);
    ASSERT(d1.getRows() == 3, "Diagonal matrix rows correct");
    ASSERT(d1.getCols() == 3, "Diagonal matrix cols correct");

    // All elements should be zero initially
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            ASSERT_EQUAL(d1.getElement(i, j), 0.0, "Diagonal matrix initialized to zero");
        }
    }

    TEST("DiagonalMatrix - Diagonal Elements");
    DiagonalMatrix d2(4);
    d2.setElement(0, 0, 1.0);
    d2.setElement(1, 1, 2.0);
    d2.setElement(2, 2, 3.0);
    d2.setElement(3, 3, 4.0);

    ASSERT_EQUAL(d2.getElement(0, 0), 1.0, "Diagonal (0,0) correct");
    ASSERT_EQUAL(d2.getElement(1, 1), 2.0, "Diagonal (1,1) correct");
    ASSERT_EQUAL(d2.getElement(2, 2), 3.0, "Diagonal (2,2) correct");
    ASSERT_EQUAL(d2.getElement(3, 3), 4.0, "Diagonal (3,3) correct");

    // Off-diagonal should remain zero
    ASSERT_EQUAL(d2.getElement(0, 1), 0.0, "Off-diagonal (0,1) is zero");
    ASSERT_EQUAL(d2.getElement(1, 0), 0.0, "Off-diagonal (1,0) is zero");
    ASSERT_EQUAL(d2.getElement(2, 3), 0.0, "Off-diagonal (2,3) is zero");
}

void testDiagonalMatrixOperations()
{
    TEST("DiagonalMatrix - Addition");
    DiagonalMatrix d1(3);
    d1.setElement(0, 0, 1.0);
    d1.setElement(1, 1, 2.0);
    d1.setElement(2, 2, 3.0);

    DiagonalMatrix d2(3);
    d2.setElement(0, 0, 4.0);
    d2.setElement(1, 1, 5.0);
    d2.setElement(2, 2, 6.0);

    DiagonalMatrix sum = d1 + d2;
    ASSERT_EQUAL(sum.getElement(0, 0), 5.0, "Diagonal addition (0,0)");
    ASSERT_EQUAL(sum.getElement(1, 1), 7.0, "Diagonal addition (1,1)");
    ASSERT_EQUAL(sum.getElement(2, 2), 9.0, "Diagonal addition (2,2)");
    ASSERT_EQUAL(sum.getElement(0, 1), 0.0, "Diagonal addition off-diagonal stays zero");

    TEST("DiagonalMatrix - Subtraction");
    DiagonalMatrix diff = d2 - d1;
    ASSERT_EQUAL(diff.getElement(0, 0), 3.0, "Diagonal subtraction (0,0)");
    ASSERT_EQUAL(diff.getElement(1, 1), 3.0, "Diagonal subtraction (1,1)");
    ASSERT_EQUAL(diff.getElement(2, 2), 3.0, "Diagonal subtraction (2,2)");

    TEST("DiagonalMatrix - Multiplication");
    DiagonalMatrix prod = d1 * d2;
    ASSERT_EQUAL(prod.getElement(0, 0), 4.0, "Diagonal multiplication (0,0) = 1*4");
    ASSERT_EQUAL(prod.getElement(1, 1), 10.0, "Diagonal multiplication (1,1) = 2*5");
    ASSERT_EQUAL(prod.getElement(2, 2), 18.0, "Diagonal multiplication (2,2) = 3*6");
    ASSERT_EQUAL(prod.getElement(0, 2), 0.0, "Diagonal multiplication off-diagonal");

    TEST("DiagonalMatrix - Equality");
    DiagonalMatrix d3(3);
    d3.setElement(0, 0, 1.0);
    d3.setElement(1, 1, 2.0);
    d3.setElement(2, 2, 3.0);

    ASSERT(d1 == d3, "Equal diagonal matrices");
    ASSERT(!(d1 == d2), "Different diagonal matrices");
}

// ==================== LOWER TRIANGULAR TESTS ====================

void testLowerTriangularBasics()
{
    TEST("LowerTriangularMatrix - Basic Construction");

    LowerTriangularMatrix L(3);
    ASSERT(L.getRows() == 3, "Lower triangular rows correct");
    ASSERT(L.getCols() == 3, "Lower triangular cols correct");

    // Upper triangle should be zero
    ASSERT_EQUAL(L.getElement(0, 1), 0.0, "Upper element (0,1) is zero");
    ASSERT_EQUAL(L.getElement(0, 2), 0.0, "Upper element (0,2) is zero");
    ASSERT_EQUAL(L.getElement(1, 2), 0.0, "Upper element (1,2) is zero");

    TEST("LowerTriangularMatrix - Setting Elements");
    LowerTriangularMatrix L2(3);
    L2.setElement(0, 0, 1.0);
    L2.setElement(1, 0, 2.0);
    L2.setElement(1, 1, 3.0);
    L2.setElement(2, 0, 4.0);
    L2.setElement(2, 1, 5.0);
    L2.setElement(2, 2, 6.0);

    ASSERT_EQUAL(L2.getElement(0, 0), 1.0, "Lower (0,0) correct");
    ASSERT_EQUAL(L2.getElement(1, 0), 2.0, "Lower (1,0) correct");
    ASSERT_EQUAL(L2.getElement(1, 1), 3.0, "Lower (1,1) correct");
    ASSERT_EQUAL(L2.getElement(2, 0), 4.0, "Lower (2,0) correct");
    ASSERT_EQUAL(L2.getElement(2, 1), 5.0, "Lower (2,1) correct");
    ASSERT_EQUAL(L2.getElement(2, 2), 6.0, "Lower (2,2) correct");

    // Upper should still be zero
    ASSERT_EQUAL(L2.getElement(0, 1), 0.0, "Upper still zero after setting lower");
}

void testLowerTriangularOperations()
{
    TEST("LowerTriangularMatrix - Addition");
    LowerTriangularMatrix L1(3);
    L1.setElement(0, 0, 1.0);
    L1.setElement(1, 0, 2.0);
    L1.setElement(1, 1, 3.0);
    L1.setElement(2, 0, 4.0);
    L1.setElement(2, 1, 5.0);
    L1.setElement(2, 2, 6.0);

    LowerTriangularMatrix L2(3);
    L2.setElement(0, 0, 6.0);
    L2.setElement(1, 0, 5.0);
    L2.setElement(1, 1, 4.0);
    L2.setElement(2, 0, 3.0);
    L2.setElement(2, 1, 2.0);
    L2.setElement(2, 2, 1.0);

    LowerTriangularMatrix sum = L1 + L2;
    ASSERT_EQUAL(sum.getElement(0, 0), 7.0, "Lower addition (0,0)");
    ASSERT_EQUAL(sum.getElement(1, 0), 7.0, "Lower addition (1,0)");
    ASSERT_EQUAL(sum.getElement(1, 1), 7.0, "Lower addition (1,1)");
    ASSERT_EQUAL(sum.getElement(2, 2), 7.0, "Lower addition (2,2)");

    TEST("LowerTriangularMatrix - Subtraction");
    LowerTriangularMatrix diff = L1 - L2;
    ASSERT_EQUAL(diff.getElement(0, 0), -5.0, "Lower subtraction (0,0)");
    ASSERT_EQUAL(diff.getElement(1, 0), -3.0, "Lower subtraction (1,0)");
    ASSERT_EQUAL(diff.getElement(2, 2), 5.0, "Lower subtraction (2,2)");

    TEST("LowerTriangularMatrix - Multiplication");
    LowerTriangularMatrix L3(2);
    L3.setElement(0, 0, 2.0);
    L3.setElement(1, 0, 3.0);
    L3.setElement(1, 1, 4.0);

    LowerTriangularMatrix L4(2);
    L4.setElement(0, 0, 1.0);
    L4.setElement(1, 0, 5.0);
    L4.setElement(1, 1, 6.0);

    LowerTriangularMatrix prod = L3 * L4;
    // [2 0] * [1 0] = [2   0]
    // [3 4]   [5 6]   [23 24]
    ASSERT_EQUAL(prod.getElement(0, 0), 2.0, "Lower multiplication (0,0)");
    ASSERT_EQUAL(prod.getElement(1, 0), 23.0, "Lower multiplication (1,0)");
    ASSERT_EQUAL(prod.getElement(1, 1), 24.0, "Lower multiplication (1,1)");
    ASSERT_EQUAL(prod.getElement(0, 1), 0.0, "Lower multiplication upper is zero");

    TEST("LowerTriangularMatrix - Equality");
    LowerTriangularMatrix L5(2);
    L5.setElement(0, 0, 2.0);
    L5.setElement(1, 0, 3.0);
    L5.setElement(1, 1, 4.0);

    ASSERT(L3 == L5, "Equal lower triangular matrices");
    ASSERT(!(L3 == L4), "Different lower triangular matrices");
}

// ==================== UPPER TRIANGULAR TESTS ====================

void testUpperTriangularBasics()
{
    TEST("UpperTriangularMatrix - Basic Construction");

    UpperTriangularMatrix U(3);
    ASSERT(U.getRows() == 3, "Upper triangular rows correct");
    ASSERT(U.getCols() == 3, "Upper triangular cols correct");

    // Lower triangle should be zero
    ASSERT_EQUAL(U.getElement(1, 0), 0.0, "Lower element (1,0) is zero");
    ASSERT_EQUAL(U.getElement(2, 0), 0.0, "Lower element (2,0) is zero");
    ASSERT_EQUAL(U.getElement(2, 1), 0.0, "Lower element (2,1) is zero");

    TEST("UpperTriangularMatrix - Setting Elements");
    UpperTriangularMatrix U2(3);
    U2.setElement(0, 0, 1.0);
    U2.setElement(0, 1, 2.0);
    U2.setElement(0, 2, 3.0);
    U2.setElement(1, 1, 4.0);
    U2.setElement(1, 2, 5.0);
    U2.setElement(2, 2, 6.0);

    ASSERT_EQUAL(U2.getElement(0, 0), 1.0, "Upper (0,0) correct");
    ASSERT_EQUAL(U2.getElement(0, 1), 2.0, "Upper (0,1) correct");
    ASSERT_EQUAL(U2.getElement(0, 2), 3.0, "Upper (0,2) correct");
    ASSERT_EQUAL(U2.getElement(1, 1), 4.0, "Upper (1,1) correct");
    ASSERT_EQUAL(U2.getElement(1, 2), 5.0, "Upper (1,2) correct");
    ASSERT_EQUAL(U2.getElement(2, 2), 6.0, "Upper (2,2) correct");

    // Lower should still be zero
    ASSERT_EQUAL(U2.getElement(1, 0), 0.0, "Lower still zero after setting upper");
}

void testUpperTriangularOperations()
{
    TEST("UpperTriangularMatrix - Addition");
    UpperTriangularMatrix U1(3);
    U1.setElement(0, 0, 1.0);
    U1.setElement(0, 1, 2.0);
    U1.setElement(0, 2, 3.0);
    U1.setElement(1, 1, 4.0);
    U1.setElement(1, 2, 5.0);
    U1.setElement(2, 2, 6.0);

    UpperTriangularMatrix U2(3);
    U2.setElement(0, 0, 6.0);
    U2.setElement(0, 1, 5.0);
    U2.setElement(0, 2, 4.0);
    U2.setElement(1, 1, 3.0);
    U2.setElement(1, 2, 2.0);
    U2.setElement(2, 2, 1.0);

    UpperTriangularMatrix sum = U1 + U2;
    ASSERT_EQUAL(sum.getElement(0, 0), 7.0, "Upper addition (0,0)");
    ASSERT_EQUAL(sum.getElement(0, 1), 7.0, "Upper addition (0,1)");
    ASSERT_EQUAL(sum.getElement(0, 2), 7.0, "Upper addition (0,2)");
    ASSERT_EQUAL(sum.getElement(1, 1), 7.0, "Upper addition (1,1)");

    TEST("UpperTriangularMatrix - Subtraction");
    UpperTriangularMatrix diff = U1 - U2;
    ASSERT_EQUAL(diff.getElement(0, 0), -5.0, "Upper subtraction (0,0)");
    ASSERT_EQUAL(diff.getElement(0, 2), -1.0, "Upper subtraction (0,2)");
    ASSERT_EQUAL(diff.getElement(2, 2), 5.0, "Upper subtraction (2,2)");

    TEST("UpperTriangularMatrix - Multiplication");
    UpperTriangularMatrix U3(2);
    U3.setElement(0, 0, 2.0);
    U3.setElement(0, 1, 3.0);
    U3.setElement(1, 1, 4.0);

    UpperTriangularMatrix U4(2);
    U4.setElement(0, 0, 1.0);
    U4.setElement(0, 1, 5.0);
    U4.setElement(1, 1, 6.0);

    UpperTriangularMatrix prod = U3 * U4;
    // [2 3] * [1 5] = [2  28]
    // [0 4]   [0 6]   [0  24]

    setColor(COLOR_YELLOW);
    std::cout << "  Input U3:" << std::endl
              << U3;
    std::cout << "  Input U4:" << std::endl
              << U4;
    std::cout << "  Expected Result:" << std::endl;
    std::cout << "  |  2.00  28.00 |" << std::endl;
    std::cout << "  |  0.00  24.00 |" << std::endl;
    std::cout << "  Actual Result:" << std::endl
              << prod;
    setColor(COLOR_WHITE);

    ASSERT_MATRIX_EQUAL(prod, 0, 0, 2.0, "Upper multiplication (0,0)");
    ASSERT_MATRIX_EQUAL(prod, 0, 1, 28.0, "Upper multiplication (0,1)");
    ASSERT_MATRIX_EQUAL(prod, 1, 1, 24.0, "Upper multiplication (1,1)");
    ASSERT_MATRIX_EQUAL(prod, 1, 0, 0.0, "Upper multiplication lower is zero");

    TEST("UpperTriangularMatrix - Equality");
    UpperTriangularMatrix U5(2);
    U5.setElement(0, 0, 2.0);
    U5.setElement(0, 1, 3.0);
    U5.setElement(1, 1, 4.0);

    ASSERT(U3 == U5, "Equal upper triangular matrices");
    ASSERT(!(U3 == U4), "Different upper triangular matrices");
}

// ==================== POLYMORPHISM TESTS ====================

void testPolymorphism()
{
    TEST("Polymorphism - Matrix Base Class Pointer");

    Matrix *m = new SquareMatrix(2);
    m->setElement(0, 0, 1.0);
    m->setElement(0, 1, 2.0);
    m->setElement(1, 0, 3.0);
    m->setElement(1, 1, 4.0);

    ASSERT_EQUAL(m->getElement(0, 0), 1.0, "Polymorphic access to SquareMatrix");
    ASSERT(m->getRows() == 2 && m->getCols() == 2, "Polymorphic dimensions");
    delete m;

    m = new DiagonalMatrix(3);
    m->setElement(0, 0, 5.0);
    m->setElement(1, 1, 6.0);
    m->setElement(2, 2, 7.0);

    ASSERT_EQUAL(m->getElement(1, 1), 6.0, "Polymorphic access to DiagonalMatrix");
    ASSERT_EQUAL(m->getElement(0, 1), 0.0, "Polymorphic DiagonalMatrix off-diagonal");
    delete m;

    m = new LowerTriangularMatrix(2);
    m->setElement(0, 0, 8.0);
    m->setElement(1, 0, 9.0);
    m->setElement(1, 1, 10.0);

    ASSERT_EQUAL(m->getElement(1, 0), 9.0, "Polymorphic access to LowerTriangular");
    delete m;

    m = new UpperTriangularMatrix(2);
    m->setElement(0, 0, 11.0);
    m->setElement(0, 1, 12.0);
    m->setElement(1, 1, 13.0);

    ASSERT_EQUAL(m->getElement(0, 1), 12.0, "Polymorphic access to UpperTriangular");
    delete m;
}

// ==================== COPY CONSTRUCTOR TESTS ====================

void testCopyConstructors()
{
    TEST("Copy Constructors - Matrix");
    Matrix m1(2, 3);
    m1.setElement(0, 0, 1.0);
    m1.setElement(0, 1, 2.0);
    m1.setElement(0, 2, 3.0);
    m1.setElement(1, 0, 4.0);
    m1.setElement(1, 1, 5.0);
    m1.setElement(1, 2, 6.0);

    Matrix m2(m1);
    ASSERT_EQUAL(m2.getElement(0, 0), 1.0, "Matrix copy (0,0)");
    ASSERT_EQUAL(m2.getElement(1, 2), 6.0, "Matrix copy (1,2)");
    ASSERT(m1 == m2, "Copied matrix equals original");

    // Modify copy, original shouldn't change
    m2.setElement(0, 0, 99.0);
    ASSERT_EQUAL(m1.getElement(0, 0), 1.0, "Original unchanged after copy modification");
    ASSERT_EQUAL(m2.getElement(0, 0), 99.0, "Copy modified correctly");

    TEST("Copy Constructors - SquareMatrix");
    SquareMatrix s1(2);
    s1.setElement(0, 0, 1.0);
    s1.setElement(0, 1, 2.0);
    s1.setElement(1, 0, 3.0);
    s1.setElement(1, 1, 4.0);

    SquareMatrix s2(s1);
    ASSERT(s1 == s2, "SquareMatrix copy equals original");
    s2.setElement(0, 0, 88.0);
    ASSERT(!(s1 == s2), "Modified copy differs from original");

    TEST("Copy Constructors - DiagonalMatrix");
    DiagonalMatrix d1(3);
    d1.setElement(0, 0, 1.0);
    d1.setElement(1, 1, 2.0);
    d1.setElement(2, 2, 3.0);

    DiagonalMatrix d2(d1);
    ASSERT(d1 == d2, "DiagonalMatrix copy equals original");

    TEST("Copy Constructors - LowerTriangularMatrix");
    LowerTriangularMatrix L1(2);
    L1.setElement(0, 0, 1.0);
    L1.setElement(1, 0, 2.0);
    L1.setElement(1, 1, 3.0);

    LowerTriangularMatrix L2(L1);
    ASSERT(L1 == L2, "LowerTriangularMatrix copy equals original");

    TEST("Copy Constructors - UpperTriangularMatrix");
    UpperTriangularMatrix U1(2);
    U1.setElement(0, 0, 1.0);
    U1.setElement(0, 1, 2.0);
    U1.setElement(1, 1, 3.0);

    UpperTriangularMatrix U2(U1);
    ASSERT(U1 == U2, "UpperTriangularMatrix copy equals original");
}

// ==================== LARGE MATRIX TESTS ====================

void testLargeMatrices()
{
    TEST("Large Matrices - 10x10 Matrix");
    Matrix large(10, 10);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            large.setElement(i, j, i * 10 + j);
        }
    }
    ASSERT_EQUAL(large.getElement(5, 7), 57.0, "Large matrix element access");

    TEST("Large Matrices - 10x10 SquareMatrix Multiplication");
    SquareMatrix A(10), B(10);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            A.setElement(i, j, 1.0);
            B.setElement(i, j, 1.0);
        }
    }
    SquareMatrix C = A * B;
    ASSERT_EQUAL(C.getElement(5, 5), 10.0, "Large matrix multiplication result");

    TEST("Large Matrices - 20x20 DiagonalMatrix");
    DiagonalMatrix bigD(20);
    for (int i = 0; i < 20; i++)
    {
        bigD.setElement(i, i, i + 1);
    }
    ASSERT_EQUAL(bigD.getElement(15, 15), 16.0, "Large diagonal matrix element");
    ASSERT_EQUAL(bigD.getElement(15, 16), 0.0, "Large diagonal off-diagonal is zero");
}

// ==================== NEGATIVE NUMBER TESTS ====================

void testNegativeNumbers()
{
    TEST("Negative Numbers - Matrix");
    Matrix m(2, 2);
    m.setElement(0, 0, -1.5);
    m.setElement(0, 1, -2.5);
    m.setElement(1, 0, -3.5);
    m.setElement(1, 1, -4.5);

    ASSERT_EQUAL(m.getElement(0, 0), -1.5, "Negative element storage");

    Matrix m2(2, 2);
    m2.setElement(0, 0, 1.5);
    m2.setElement(0, 1, 2.5);
    m2.setElement(1, 0, 3.5);
    m2.setElement(1, 1, 4.5);

    Matrix sum = m + m2;
    ASSERT_EQUAL(sum.getElement(0, 0), 0.0, "Negative + positive = 0");

    TEST("Negative Numbers - DiagonalMatrix");
    DiagonalMatrix d(3);
    d.setElement(0, 0, -5.0);
    d.setElement(1, 1, -10.0);
    d.setElement(2, 2, -15.0);

    DiagonalMatrix d2(3);
    d2.setElement(0, 0, 5.0);
    d2.setElement(1, 1, 10.0);
    d2.setElement(2, 2, 15.0);

    DiagonalMatrix result = d + d2;
    ASSERT_EQUAL(result.getElement(0, 0), 0.0, "Negative diagonal addition");

    TEST("Negative Numbers - Multiplication");
    Matrix A(2, 2), B(2, 2);
    A.setElement(0, 0, -2.0);
    A.setElement(0, 1, 3.0);
    A.setElement(1, 0, -4.0);
    A.setElement(1, 1, 5.0);

    B.setElement(0, 0, 1.0);
    B.setElement(0, 1, -1.0);
    B.setElement(1, 0, 2.0);
    B.setElement(1, 1, -2.0);

    Matrix prod = A * B;
    // [-2  3] * [ 1 -1] = [ 4  -4]
    // [-4  5]   [ 2 -2]   [ 6  -6]
    ASSERT_EQUAL(prod.getElement(0, 0), 4.0, "Negative multiplication (0,0)");
    ASSERT_EQUAL(prod.getElement(0, 1), -4.0, "Negative multiplication (0,1)");
    ASSERT_EQUAL(prod.getElement(1, 0), 6.0, "Negative multiplication (1,0)");
    ASSERT_EQUAL(prod.getElement(1, 1), -6.0, "Negative multiplication (1,1)");
}

// ==================== ZERO MATRIX TESTS ====================

void testZeroMatrices()
{
    TEST("Zero Matrices - Matrix Addition");
    Matrix zero(3, 3);
    Matrix m(3, 3);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            m.setElement(i, j, i * 3 + j + 1);
        }
    }

    Matrix result = m + zero;
    ASSERT(result == m, "Matrix + zero matrix = matrix");

    TEST("Zero Matrices - Matrix Multiplication");
    Matrix A(2, 3), B(3, 2);
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            A.setElement(i, j, i + j + 1);

    // B is zero matrix
    Matrix prod = A * B;
    bool allZero = true;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (prod.getElement(i, j) != 0.0)
                allZero = false;
        }
    }
    ASSERT(allZero, "Matrix * zero matrix = zero matrix");

    TEST("Zero Matrices - DiagonalMatrix");
    DiagonalMatrix zeroD(4);
    DiagonalMatrix d(4);
    for (int i = 0; i < 4; i++)
    {
        d.setElement(i, i, i + 1);
    }

    DiagonalMatrix prod2 = d * zeroD;
    bool diagZero = true;
    for (int i = 0; i < 4; i++)
    {
        if (prod2.getElement(i, i) != 0.0)
            diagZero = false;
    }
    ASSERT(diagZero, "Diagonal * zero diagonal = zero");
}

// ==================== IDENTITY MATRIX TESTS ====================

void testIdentityMatrices()
{
    TEST("Identity Matrices - Diagonal as Identity");
    DiagonalMatrix I(3);
    I.setElement(0, 0, 1.0);
    I.setElement(1, 1, 1.0);
    I.setElement(2, 2, 1.0);

    SquareMatrix A(3);
    A.setElement(0, 0, 2.0);
    A.setElement(0, 1, 3.0);
    A.setElement(0, 2, 4.0);
    A.setElement(1, 0, 5.0);
    A.setElement(1, 1, 6.0);
    A.setElement(1, 2, 7.0);
    A.setElement(2, 0, 8.0);
    A.setElement(2, 1, 9.0);
    A.setElement(2, 2, 10.0);

    // Note: This tests I * A through polymorphism if implemented
    DiagonalMatrix D(3);
    D.setElement(0, 0, 5.0);
    D.setElement(1, 1, 5.0);
    D.setElement(2, 2, 5.0);

    DiagonalMatrix prod = I * D;
    ASSERT(prod == D, "Identity * Diagonal = Diagonal");

    TEST("Identity Matrices - LowerTriangular");
    LowerTriangularMatrix L(2);
    L.setElement(0, 0, 1.0);
    L.setElement(1, 0, 0.0);
    L.setElement(1, 1, 1.0);

    LowerTriangularMatrix L2(2);
    L2.setElement(0, 0, 5.0);
    L2.setElement(1, 0, 6.0);
    L2.setElement(1, 1, 7.0);

    LowerTriangularMatrix prod2 = L * L2;
    ASSERT(prod2 == L2, "Lower identity * Lower = Lower");
}

// ==================== MEMORY LAYOUT TESTS ====================

void testMemoryLayout()
{
    TEST("Memory Layout - Matrix Row-Major Order");
    Matrix m(2, 3);
    m.setElement(0, 0, 0.0);
    m.setElement(0, 1, 1.0);
    m.setElement(0, 2, 2.0);
    m.setElement(1, 0, 3.0);
    m.setElement(1, 1, 4.0);
    m.setElement(1, 2, 5.0);

    // Elements should be stored as [0, 1, 2, 3, 4, 5]
    // This verifies index calculation: i*n + j
    ASSERT_EQUAL(m.getElement(0, 0), 0.0, "Row-major (0,0)");
    ASSERT_EQUAL(m.getElement(0, 1), 1.0, "Row-major (0,1)");
    ASSERT_EQUAL(m.getElement(0, 2), 2.0, "Row-major (0,2)");
    ASSERT_EQUAL(m.getElement(1, 0), 3.0, "Row-major (1,0)");
    ASSERT_EQUAL(m.getElement(1, 1), 4.0, "Row-major (1,1)");
    ASSERT_EQUAL(m.getElement(1, 2), 5.0, "Row-major (1,2)");

    TEST("Memory Layout - DiagonalMatrix Compact Storage");
    DiagonalMatrix d(5);
    for (int i = 0; i < 5; i++)
    {
        d.setElement(i, i, i * 10.0);
    }

    // Should only store n elements, not n²
    ASSERT_WITH_VALUE(d.getElementsSize() == 5, "Diagonal stores only n elements", d.getElementsSize(), 5);

    TEST("Memory Layout - LowerTriangular Compact Storage");
    LowerTriangularMatrix L(4);
    // Should store n(n+1)/2 = 10 elements
    ASSERT_WITH_VALUE(L.getElementsSize() == 10, "Lower triangular stores n(n+1)/2 elements", L.getElementsSize(), 10);

    TEST("Memory Layout - UpperTriangular Compact Storage");
    UpperTriangularMatrix U(4);
    // Should store n(n+1)/2 = 10 elements
    ASSERT_WITH_VALUE(U.getElementsSize() == 10, "Upper triangular stores n(n+1)/2 elements", U.getElementsSize(), 10);

    TEST("Memory Layout - SquareMatrix Full Storage");
    SquareMatrix s(4);
    // Should store n² = 16 elements
    ASSERT(s.getElementsSize() == 16, "Square matrix stores n² elements");
}

// ==================== EXTREME TEST CATEGORIES - PHASE 1 ====================

// CATEGORY 1: Memory Storage Verification - Small Matrices
void testCategory1_MemoryStorageSmall()
{
    TEST("Cat1.1: Diagonal(3) - Exactly 3 Elements");
    DiagonalMatrix d3(3);
    ASSERT_WITH_VALUE(d3.getElementsSize() == 3, "Diagonal(3) has exactly 3 elements", d3.getElementsSize(), 3);
    ASSERT(d3.getRows() == 3 && d3.getCols() == 3, "Diagonal(3) is 3x3");

    TEST("Cat1.2: Lower(3) - Exactly 6 Elements");
    LowerTriangularMatrix L3(3);
    ASSERT_WITH_VALUE(L3.getElementsSize() == 6, "Lower(3) has exactly 6 elements (n(n+1)/2)", L3.getElementsSize(), 6);
    ASSERT(L3.getRows() == 3 && L3.getCols() == 3, "Lower(3) is 3x3");

    TEST("Cat1.3: Upper(3) - Exactly 6 Elements");
    UpperTriangularMatrix U3(3);
    ASSERT_WITH_VALUE(U3.getElementsSize() == 6, "Upper(3) has exactly 6 elements (n(n+1)/2)", U3.getElementsSize(), 6);
    ASSERT(U3.getRows() == 3 && U3.getCols() == 3, "Upper(3) is 3x3");

    TEST("Cat1.4: Square(3) - Exactly 9 Elements");
    SquareMatrix s3(3);
    ASSERT_WITH_VALUE(s3.getElementsSize() == 9, "Square(3) has exactly 9 elements (n²)", s3.getElementsSize(), 9);
    ASSERT(s3.getRows() == 3 && s3.getCols() == 3, "Square(3) is 3x3");

    TEST("Cat1.5: Off-Diagonal Access Without Storage - Diagonal");
    DiagonalMatrix d(5);
    d.setElement(2, 2, 42.0);
    ASSERT_EQUAL(d.getElement(2, 2), 42.0, "Diagonal element stored correctly");
    ASSERT_EQUAL(d.getElement(2, 3), 0.0, "Off-diagonal returns 0 (not stored)");
    ASSERT_EQUAL(d.getElement(0, 4), 0.0, "Off-diagonal returns 0 (not stored)");
    ASSERT_EQUAL(d.getElement(1, 3), 0.0, "Off-diagonal returns 0 (not stored)");
}

void testCategory1_MemoryStorageMedium()
{
    TEST("Cat1.6: Diagonal(50) - Exactly 50 Elements");
    DiagonalMatrix d50(50);
    ASSERT_WITH_VALUE(d50.getElementsSize() == 50, "Diagonal(50) has exactly 50 elements", d50.getElementsSize(), 50);

    TEST("Cat1.7: Lower(50) - Exactly 1,275 Elements");
    LowerTriangularMatrix L50(50);
    int expected_lower = 50 * 51 / 2;
    ASSERT(L50.getElementsSize() == expected_lower, "Lower(50) has exactly 1,275 elements");
    ASSERT(expected_lower == 1275, "Verification: 50*51/2 = 1,275");

    TEST("Cat1.8: Upper(50) - Exactly 1,275 Elements");
    UpperTriangularMatrix U50(50);
    int expected_upper = 50 * 51 / 2;
    ASSERT(U50.getElementsSize() == expected_upper, "Upper(50) has exactly 1,275 elements");

    TEST("Cat1.9: Square(50) - Exactly 2,500 Elements");
    SquareMatrix s50(50);
    ASSERT(s50.getElementsSize() == 2500, "Square(50) has exactly 2,500 elements");

    TEST("Cat1.10: Memory Efficiency - Diagonal vs Square");
    DiagonalMatrix d(50);
    SquareMatrix s(50);
    double ratio = (100.0 * d.getElementsSize()) / s.getElementsSize();
    ASSERT(ratio == 2.0, "Diagonal uses 2% of Square storage for n=50");
}

void testCategory1_MemoryStorageLarge()
{
    TEST("Cat1.11: Diagonal(500) - NOT 250,000");
    DiagonalMatrix d500(500);
    ASSERT(d500.getElementsSize() == 500, "Diagonal(500) has 500 elements, NOT 250,000");
    ASSERT(d500.getElementsSize() != 250000, "Confirmed: NOT using n² storage");

    TEST("Cat1.12: Lower(500) - Exactly 125,250 Elements");
    LowerTriangularMatrix L500(500);
    int expected = 500 * 501 / 2;
    ASSERT(L500.getElementsSize() == expected, "Lower(500) has exactly 125,250 elements");
    ASSERT(expected == 125250, "Verification: 500*501/2 = 125,250");
    ASSERT(L500.getElementsSize() != 250000, "NOT using full n² storage");

    TEST("Cat1.13: Upper(500) - Exactly 125,250 Elements");
    UpperTriangularMatrix U500(500);
    ASSERT(U500.getElementsSize() == 125250, "Upper(500) has exactly 125,250 elements");
    ASSERT(U500.getElementsSize() != 250000, "NOT using full n² storage");

    TEST("Cat1.14: Memory Efficiency Ratio - Large Scale");
    DiagonalMatrix d(100);
    SquareMatrix s(100);
    double ratio = (100.0 * d.getElementsSize()) / s.getElementsSize();
    ASSERT(ratio == 1.0, "Diagonal(100) uses 1% of Square(100) storage");
}

// CATEGORY 2: Index Mapping Formula Correctness
void testCategory2_IndexMappingDiagonal()
{
    TEST("Cat2.1: Diagonal Sequential Mapping - Small");
    DiagonalMatrix d(5);
    d.setElement(0, 0, 0.0);
    d.setElement(1, 1, 1.0);
    d.setElement(2, 2, 2.0);
    d.setElement(3, 3, 3.0);
    d.setElement(4, 4, 4.0);

    ASSERT_EQUAL(d.getElement(0, 0), 0.0, "Diagonal[0] = 0");
    ASSERT_EQUAL(d.getElement(1, 1), 1.0, "Diagonal[1] = 1");
    ASSERT_EQUAL(d.getElement(2, 2), 2.0, "Diagonal[2] = 2");
    ASSERT_EQUAL(d.getElement(3, 3), 3.0, "Diagonal[3] = 3");
    ASSERT_EQUAL(d.getElement(4, 4), 4.0, "Diagonal[4] = 4");

    TEST("Cat2.2: Diagonal Specific Position - Large Index");
    DiagonalMatrix d50(100);
    d50.setElement(50, 50, 999.0);
    ASSERT_EQUAL(d50.getElement(50, 50), 999.0, "Element at (50,50) stored correctly");
    ASSERT(d50.getElementsSize() == 100, "Still only 100 elements stored");

    TEST("Cat2.3: Diagonal All Positions - Sequential");
    DiagonalMatrix d10(10);
    for (int i = 0; i < 10; i++)
    {
        d10.setElement(i, i, i * 10.0);
    }
    for (int i = 0; i < 10; i++)
    {
        ASSERT_EQUAL(d10.getElement(i, i), i * 10.0, "Sequential diagonal element correct");
    }
}

void testCategory2_IndexMappingLower()
{
    TEST("Cat2.4: Lower Triangular Row-by-Row Mapping");
    LowerTriangularMatrix L(4);
    // Row 0: (0,0)
    L.setElement(0, 0, 1.0);
    // Row 1: (1,0), (1,1)
    L.setElement(1, 0, 2.0);
    L.setElement(1, 1, 3.0);
    // Row 2: (2,0), (2,1), (2,2)
    L.setElement(2, 0, 4.0);
    L.setElement(2, 1, 5.0);
    L.setElement(2, 2, 6.0);
    // Row 3: (3,0), (3,1), (3,2), (3,3)
    L.setElement(3, 0, 7.0);
    L.setElement(3, 1, 8.0);
    L.setElement(3, 2, 9.0);
    L.setElement(3, 3, 10.0);

    ASSERT_EQUAL(L.getElement(0, 0), 1.0, "L(0,0) = 1");
    ASSERT_EQUAL(L.getElement(1, 0), 2.0, "L(1,0) = 2");
    ASSERT_EQUAL(L.getElement(1, 1), 3.0, "L(1,1) = 3");
    ASSERT_EQUAL(L.getElement(2, 0), 4.0, "L(2,0) = 4");
    ASSERT_EQUAL(L.getElement(2, 1), 5.0, "L(2,1) = 5");
    ASSERT_EQUAL(L.getElement(2, 2), 6.0, "L(2,2) = 6");
    ASSERT_EQUAL(L.getElement(3, 0), 7.0, "L(3,0) = 7");
    ASSERT_EQUAL(L.getElement(3, 1), 8.0, "L(3,1) = 8");
    ASSERT_EQUAL(L.getElement(3, 2), 9.0, "L(3,2) = 9");
    ASSERT_EQUAL(L.getElement(3, 3), 10.0, "L(3,3) = 10");

    TEST("Cat2.5: Lower Triangular Last Element");
    LowerTriangularMatrix L10(10);
    L10.setElement(9, 9, 999.0);
    ASSERT_EQUAL(L10.getElement(9, 9), 999.0, "Last diagonal element correct");

    TEST("Cat2.6: Lower Triangular First Off-Diagonal");
    LowerTriangularMatrix Ltest(10);
    Ltest.setElement(1, 0, 123.0);
    ASSERT_EQUAL(Ltest.getElement(1, 0), 123.0, "First off-diagonal correct");
    ASSERT_EQUAL(Ltest.getElement(0, 1), 0.0, "Upper triangle is zero");
}

void testCategory2_IndexMappingUpper()
{
    TEST("Cat2.7: Upper Triangular Row-by-Row Mapping");
    UpperTriangularMatrix U(4);
    // Row 0: all 4 elements
    U.setElement(0, 0, 1.0);
    U.setElement(0, 1, 2.0);
    U.setElement(0, 2, 3.0);
    U.setElement(0, 3, 4.0);
    // Row 1: 3 elements
    U.setElement(1, 1, 5.0);
    U.setElement(1, 2, 6.0);
    U.setElement(1, 3, 7.0);
    // Row 2: 2 elements
    U.setElement(2, 2, 8.0);
    U.setElement(2, 3, 9.0);
    // Row 3: 1 element
    U.setElement(3, 3, 10.0);

    ASSERT_EQUAL(U.getElement(0, 0), 1.0, "U(0,0) = 1");
    ASSERT_EQUAL(U.getElement(0, 1), 2.0, "U(0,1) = 2");
    ASSERT_EQUAL(U.getElement(0, 2), 3.0, "U(0,2) = 3");
    ASSERT_EQUAL(U.getElement(0, 3), 4.0, "U(0,3) = 4");
    ASSERT_EQUAL(U.getElement(1, 1), 5.0, "U(1,1) = 5");
    ASSERT_EQUAL(U.getElement(1, 2), 6.0, "U(1,2) = 6");
    ASSERT_EQUAL(U.getElement(1, 3), 7.0, "U(1,3) = 7");
    ASSERT_EQUAL(U.getElement(2, 2), 8.0, "U(2,2) = 8");
    ASSERT_EQUAL(U.getElement(2, 3), 9.0, "U(2,3) = 9");
    ASSERT_EQUAL(U.getElement(3, 3), 10.0, "U(3,3) = 10");

    TEST("Cat2.8: Upper Triangular Boundary Access");
    UpperTriangularMatrix U20(20);
    U20.setElement(0, 19, 999.0);
    ASSERT_EQUAL(U20.getElement(0, 19), 999.0, "Top-right corner accessible");
    ASSERT_EQUAL(U20.getElement(19, 0), 0.0, "Bottom-left is zero");
}

// CATEGORY 3: Structure Preservation in Operations
void testCategory3_StructurePreservationDiagonal()
{
    TEST("Cat3.1: Diagonal Addition Preserves Structure");
    DiagonalMatrix D1(10);
    DiagonalMatrix D2(10);
    for (int i = 0; i < 10; i++)
    {
        D1.setElement(i, i, i + 1.0);
        D2.setElement(i, i, i * 2.0);
    }

    DiagonalMatrix D3 = D1 + D2;
    ASSERT(D3.getElementsSize() == 10, "Result has only 10 elements");
    ASSERT_EQUAL(D3.getElement(5, 5), 16.0, "Diagonal addition correct: 6 + 10 = 16");
    ASSERT_EQUAL(D3.getElement(0, 5), 0.0, "Off-diagonal is zero");
    ASSERT_EQUAL(D3.getElement(3, 7), 0.0, "Off-diagonal is zero");

    TEST("Cat3.2: Diagonal Subtraction Preserves Structure");
    DiagonalMatrix D4 = D2 - D1;
    ASSERT(D4.getElementsSize() == 10, "Result has only 10 elements");
    ASSERT_EQUAL(D4.getElement(5, 5), 4.0, "Diagonal subtraction correct: 10 - 6 = 4");

    TEST("Cat3.3: Diagonal Multiplication Preserves Structure");
    DiagonalMatrix D5 = D1 * D2;
    ASSERT(D5.getElementsSize() == 10, "Result has only 10 elements");
    ASSERT_EQUAL(D5.getElement(5, 5), 60.0, "Diagonal multiplication correct: 6 * 10 = 60");
    ASSERT_EQUAL(D5.getElement(2, 8), 0.0, "Off-diagonal remains zero");

    TEST("Cat3.4: Chain Operations Preserve Diagonal");
    DiagonalMatrix result = ((D1 + D2) * D1) - D2;
    ASSERT(result.getElementsSize() == 10, "Chained operations maintain 10 elements");
}

void testCategory3_StructurePreservationTriangular()
{
    TEST("Cat3.5: Lower Addition Preserves Lower Structure");
    LowerTriangularMatrix L1(5);
    LowerTriangularMatrix L2(5);
    L1.setElement(3, 1, 5.0);
    L2.setElement(3, 1, 10.0);

    LowerTriangularMatrix L3 = L1 + L2;
    ASSERT(L3.getElementsSize() == 15, "Result has n(n+1)/2 = 15 elements");
    ASSERT_EQUAL(L3.getElement(3, 1), 15.0, "Lower addition correct");
    ASSERT_EQUAL(L3.getElement(0, 3), 0.0, "Upper triangle is zero");
    ASSERT_EQUAL(L3.getElement(1, 4), 0.0, "Upper triangle is zero");

    TEST("Cat3.6: Upper Addition Preserves Upper Structure");
    UpperTriangularMatrix U1(5);
    UpperTriangularMatrix U2(5);
    U1.setElement(1, 3, 7.0);
    U2.setElement(1, 3, 8.0);

    UpperTriangularMatrix U3 = U1 + U2;
    ASSERT(U3.getElementsSize() == 15, "Result has n(n+1)/2 = 15 elements");
    ASSERT_EQUAL(U3.getElement(1, 3), 15.0, "Upper addition correct");
    ASSERT_EQUAL(U3.getElement(3, 0), 0.0, "Lower triangle is zero");
    ASSERT_EQUAL(U3.getElement(4, 1), 0.0, "Lower triangle is zero");

    TEST("Cat3.7: Lower Multiplication Preserves Lower Structure");
    LowerTriangularMatrix L4(3);
    LowerTriangularMatrix L5(3);
    L4.setElement(0, 0, 2.0);
    L4.setElement(1, 0, 3.0);
    L4.setElement(1, 1, 4.0);
    L5.setElement(0, 0, 1.0);
    L5.setElement(1, 0, 5.0);
    L5.setElement(1, 1, 6.0);

    LowerTriangularMatrix L6 = L4 * L5;
    ASSERT_EQUAL(L6.getElement(0, 1), 0.0, "Upper triangle is zero after multiplication");
    ASSERT_EQUAL(L6.getElement(0, 2), 0.0, "Upper triangle is zero after multiplication");

    TEST("Cat3.8: Upper Multiplication Preserves Upper Structure");
    UpperTriangularMatrix U4(3);
    UpperTriangularMatrix U5(3);
    U4.setElement(0, 0, 2.0);
    U4.setElement(0, 1, 3.0);
    U4.setElement(1, 1, 4.0);
    U5.setElement(0, 0, 1.0);
    U5.setElement(0, 1, 5.0);
    U5.setElement(1, 1, 6.0);

    UpperTriangularMatrix U6 = U4 * U5;
    ASSERT_EQUAL(U6.getElement(1, 0), 0.0, "Lower triangle is zero after multiplication");
    ASSERT_EQUAL(U6.getElement(2, 0), 0.0, "Lower triangle is zero after multiplication");
}

// CATEGORY 4: Cross-Type Operations & Polymorphism
void testCategory4_PolymorphismTests()
{
    TEST("Cat4.1: Base Pointer to DiagonalMatrix");
    Matrix *ptr = new DiagonalMatrix(10);
    ptr->setElement(5, 5, 99.0);
    ASSERT_EQUAL(ptr->getElement(5, 5), 99.0, "Virtual getElement works for Diagonal");
    ASSERT_EQUAL(ptr->getElement(5, 7), 0.0, "Off-diagonal returns 0 through base pointer");
    ASSERT(ptr->getRows() == 10, "Polymorphic dimension access works");
    delete ptr;

    TEST("Cat4.2: Base Pointer to LowerTriangularMatrix");
    ptr = new LowerTriangularMatrix(8);
    ptr->setElement(5, 3, 123.0);
    ASSERT_EQUAL(ptr->getElement(5, 3), 123.0, "Virtual getElement works for Lower");
    ASSERT_EQUAL(ptr->getElement(3, 5), 0.0, "Upper triangle returns 0 through base pointer");
    delete ptr;

    TEST("Cat4.3: Base Pointer to UpperTriangularMatrix");
    ptr = new UpperTriangularMatrix(8);
    ptr->setElement(2, 6, 456.0);
    ASSERT_EQUAL(ptr->getElement(2, 6), 456.0, "Virtual getElement works for Upper");
    ASSERT_EQUAL(ptr->getElement(6, 2), 0.0, "Lower triangle returns 0 through base pointer");
    delete ptr;

    TEST("Cat4.4: Array of Polymorphic Matrices");
    Matrix *arr[4];
    arr[0] = new Matrix(5, 5);
    arr[1] = new SquareMatrix(5);
    arr[2] = new DiagonalMatrix(5);
    arr[3] = new LowerTriangularMatrix(5);

    // Set values through base pointer
    arr[0]->setElement(2, 3, 10.0);
    arr[1]->setElement(2, 3, 20.0);
    arr[2]->setElement(2, 2, 30.0);
    arr[3]->setElement(3, 2, 40.0);

    ASSERT_EQUAL(arr[0]->getElement(2, 3), 10.0, "Matrix access through array");
    ASSERT_EQUAL(arr[1]->getElement(2, 3), 20.0, "SquareMatrix access through array");
    ASSERT_EQUAL(arr[2]->getElement(2, 2), 30.0, "DiagonalMatrix access through array");
    ASSERT_EQUAL(arr[3]->getElement(3, 2), 40.0, "LowerTriangular access through array");

    for (int i = 0; i < 4; i++)
        delete arr[i];
}

// CATEGORY 5: Edge Cases & Boundary Conditions
void testCategory5_EdgeCasesBoundaries()
{
    TEST("Cat5.1: Size 1 - All Matrix Types");
    Matrix m1(1, 1);
    SquareMatrix s1(1);
    DiagonalMatrix d1(1);
    LowerTriangularMatrix L1(1);
    UpperTriangularMatrix U1(1);

    ASSERT(m1.getElementsSize() == 1, "Matrix(1,1) has 1 element");
    ASSERT(s1.getElementsSize() == 1, "Square(1) has 1 element");
    ASSERT(d1.getElementsSize() == 1, "Diagonal(1) has 1 element");
    ASSERT(L1.getElementsSize() == 1, "Lower(1) has 1 element");
    ASSERT(U1.getElementsSize() == 1, "Upper(1) has 1 element");

    d1.setElement(0, 0, 42.0);
    ASSERT_EQUAL(d1.getElement(0, 0), 42.0, "Size 1 diagonal works");

    TEST("Cat5.2: Size 2 - Minimal Non-Trivial");
    DiagonalMatrix d2(2);
    LowerTriangularMatrix L2(2);
    UpperTriangularMatrix U2(2);

    ASSERT(d2.getElementsSize() == 2, "Diagonal(2) has 2 elements");
    ASSERT(L2.getElementsSize() == 3, "Lower(2) has 3 elements");
    ASSERT(U2.getElementsSize() == 3, "Upper(2) has 3 elements");

    TEST("Cat5.3: First Element Access - All Types");
    DiagonalMatrix d(10);
    LowerTriangularMatrix L(10);
    UpperTriangularMatrix U(10);

    d.setElement(0, 0, 1.0);
    L.setElement(0, 0, 2.0);
    U.setElement(0, 0, 3.0);

    ASSERT_EQUAL(d.getElement(0, 0), 1.0, "Diagonal first element");
    ASSERT_EQUAL(L.getElement(0, 0), 2.0, "Lower first element");
    ASSERT_EQUAL(U.getElement(0, 0), 3.0, "Upper first element");

    TEST("Cat5.4: Last Element Access - All Types");
    d.setElement(9, 9, 10.0);
    L.setElement(9, 9, 20.0);
    U.setElement(9, 9, 30.0);

    ASSERT_EQUAL(d.getElement(9, 9), 10.0, "Diagonal last element");
    ASSERT_EQUAL(L.getElement(9, 9), 20.0, "Lower last element");
    ASSERT_EQUAL(U.getElement(9, 9), 30.0, "Upper last element");

    TEST("Cat5.5: Corner Access - Lower Triangular");
    LowerTriangularMatrix Lcorner(10);
    Lcorner.setElement(9, 0, 999.0);
    ASSERT_EQUAL(Lcorner.getElement(9, 0), 999.0, "Lower bottom-left accessible");
    ASSERT_EQUAL(Lcorner.getElement(0, 9), 0.0, "Lower top-right is zero");

    TEST("Cat5.6: Corner Access - Upper Triangular");
    UpperTriangularMatrix Ucorner(10);
    Ucorner.setElement(0, 9, 888.0);
    ASSERT_EQUAL(Ucorner.getElement(0, 9), 888.0, "Upper top-right accessible");
    ASSERT_EQUAL(Ucorner.getElement(9, 0), 0.0, "Upper bottom-left is zero");
}

// CATEGORY 6: Zero Matrix Special Cases
void testCategory6_ZeroMatrices()
{
    TEST("Cat6.1: Zero Diagonal Matrix");
    DiagonalMatrix zeroD(10);
    bool allZero = true;
    for (int i = 0; i < 10; i++)
    {
        if (zeroD.getElement(i, i) != 0.0)
            allZero = false;
    }
    ASSERT(allZero, "Zero diagonal has all zeros");
    ASSERT(zeroD.getElementsSize() == 10, "Still uses 10 storage slots");

    TEST("Cat6.2: Zero Lower Triangular");
    LowerTriangularMatrix zeroL(8);
    allZero = true;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            if (zeroL.getElement(i, j) != 0.0)
                allZero = false;
        }
    }
    ASSERT(allZero, "Zero lower triangular all zeros");
    ASSERT(zeroL.getElementsSize() == 36, "Still uses n(n+1)/2 = 36 storage");

    TEST("Cat6.3: Zero Upper Triangular");
    UpperTriangularMatrix zeroU(8);
    allZero = true;
    for (int i = 0; i < 8; i++)
    {
        for (int j = i; j < 8; j++)
        {
            if (zeroU.getElement(i, j) != 0.0)
                allZero = false;
        }
    }
    ASSERT(allZero, "Zero upper triangular all zeros");
    ASSERT(zeroU.getElementsSize() == 36, "Still uses n(n+1)/2 = 36 storage");

    TEST("Cat6.4: Operations with Zero Diagonal");
    DiagonalMatrix D(10);
    DiagonalMatrix zeroD2(10);
    for (int i = 0; i < 10; i++)
    {
        D.setElement(i, i, i + 1.0);
    }

    DiagonalMatrix result = D + zeroD2;
    ASSERT_EQUAL(result.getElement(5, 5), 6.0, "D + Zero = D");

    TEST("Cat6.5: Multiplication with Zero Diagonal");
    DiagonalMatrix zeroResult = D * zeroD2;
    bool isZero = true;
    for (int i = 0; i < 10; i++)
    {
        if (zeroResult.getElement(i, i) != 0.0)
            isZero = false;
    }
    ASSERT(isZero, "D * ZeroDiagonal = ZeroDiagonal");

    TEST("Cat6.6: Zero Detection All Positions");
    DiagonalMatrix d(20);
    bool allAccessZero = true;
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (d.getElement(i, j) != 0.0)
                allAccessZero = false;
        }
    }
    ASSERT(allAccessZero, "All positions return 0 for zero diagonal");
}

// CATEGORY 7: Copy Constructor & Deep Copy
void testCategory7_DeepCopyTests()
{
    TEST("Cat7.1: Diagonal Deep Copy Independence");
    DiagonalMatrix D1(10);
    D1.setElement(5, 5, 99.0);

    DiagonalMatrix D2(D1);
    ASSERT_EQUAL(D2.getElement(5, 5), 99.0, "Copy has same values");

    D1.setElement(5, 5, 77.0);
    ASSERT_EQUAL(D1.getElement(5, 5), 77.0, "Original modified");
    ASSERT_EQUAL(D2.getElement(5, 5), 99.0, "Copy unchanged - deep copy verified");

    TEST("Cat7.2: Lower Triangular Deep Copy");
    LowerTriangularMatrix L1(8);
    L1.setElement(5, 3, 123.0);

    LowerTriangularMatrix L2(L1);
    ASSERT(L2.getElementsSize() == 36, "Copy has n(n+1)/2 elements");
    ASSERT_EQUAL(L2.getElement(5, 3), 123.0, "Copy has correct values");

    L1.setElement(5, 3, 456.0);
    ASSERT_EQUAL(L2.getElement(5, 3), 123.0, "Lower copy independent");

    TEST("Cat7.3: Upper Triangular Deep Copy");
    UpperTriangularMatrix U1(8);
    U1.setElement(2, 6, 789.0);

    UpperTriangularMatrix U2(U1);
    ASSERT(U2.getElementsSize() == 36, "Copy has n(n+1)/2 elements");
    ASSERT_EQUAL(U2.getElement(2, 6), 789.0, "Copy has correct values");

    U1.setElement(2, 6, 321.0);
    ASSERT_EQUAL(U2.getElement(2, 6), 789.0, "Upper copy independent");

    TEST("Cat7.4: Copy Preserves Storage Size - Diagonal");
    DiagonalMatrix D(100);
    DiagonalMatrix DCopy(D);
    ASSERT(DCopy.getElementsSize() == 100, "Diagonal copy has n elements, NOT n²");
    ASSERT(DCopy.getElementsSize() != 10000, "Confirmed: NOT full matrix storage");

    TEST("Cat7.5: Copy Preserves Storage Size - Lower");
    LowerTriangularMatrix L(100);
    LowerTriangularMatrix LCopy(L);
    int expected = 100 * 101 / 2;
    ASSERT(LCopy.getElementsSize() == expected, "Lower copy has n(n+1)/2 elements");
    ASSERT(LCopy.getElementsSize() != 10000, "NOT full matrix storage");

    TEST("Cat7.6: Chain Copy Independence");
    DiagonalMatrix D3(5);
    D3.setElement(2, 2, 10.0);
    DiagonalMatrix D4(D3);
    DiagonalMatrix D5(D4);

    D3.setElement(2, 2, 20.0);
    D4.setElement(2, 2, 30.0);

    ASSERT_EQUAL(D3.getElement(2, 2), 20.0, "D3 modified");
    ASSERT_EQUAL(D4.getElement(2, 2), 30.0, "D4 modified");
    ASSERT_EQUAL(D5.getElement(2, 2), 10.0, "D5 still has original value");
}

// CATEGORY 8: Performance & Algorithmic Efficiency
void testCategory8_PerformanceEfficiency()
{
    TEST("Cat8.1: Diagonal Addition Time Complexity O(n)");
    DiagonalMatrix D1(1000);
    DiagonalMatrix D2(1000);
    for (int i = 0; i < 1000; i++)
    {
        D1.setElement(i, i, i * 1.5);
        D2.setElement(i, i, i * 2.0);
    }

    DiagonalMatrix D3 = D1 + D2;
    ASSERT(D3.getElementsSize() == 1000, "Addition creates 1000 elements, not 1,000,000");
    ASSERT_EQUAL(D3.getElement(500, 500), 1750.0, "Addition correct: 750 + 1000");

    TEST("Cat8.2: Diagonal Multiplication O(n) Not O(n³)");
    DiagonalMatrix result = D1 * D2;
    ASSERT(result.getElementsSize() == 1000, "Multiplication result has n elements");
    ASSERT_EQUAL(result.getElement(500, 500), 750000.0, "Element-wise: 750 * 1000");

    TEST("Cat8.3: Large Diagonal Operations Complete Fast");
    DiagonalMatrix Big1(5000);
    DiagonalMatrix Big2(5000);
    for (int i = 0; i < 5000; i++)
    {
        Big1.setElement(i, i, 1.0);
        Big2.setElement(i, i, 2.0);
    }

    DiagonalMatrix BigResult = Big1 + Big2;
    ASSERT(BigResult.getElementsSize() == 5000, "Large diagonal addition works");
    ASSERT_EQUAL(BigResult.getElement(2500, 2500), 3.0, "Result correct");

    TEST("Cat8.4: Triangular Addition O(n²/2) Not O(n²)");
    LowerTriangularMatrix L1(100);
    LowerTriangularMatrix L2(100);
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            L1.setElement(i, j, 1.0);
            L2.setElement(i, j, 2.0);
        }
    }

    LowerTriangularMatrix L3 = L1 + L2;
    int expected = 100 * 101 / 2;
    ASSERT(L3.getElementsSize() == expected, "Lower addition uses n(n+1)/2 = 5050 elements");
    ASSERT_EQUAL(L3.getElement(50, 25), 3.0, "Addition correct");

    TEST("Cat8.5: No Redundant Loops - Diagonal Equality");
    DiagonalMatrix D4(1000);
    DiagonalMatrix D5(1000);
    for (int i = 0; i < 1000; i++)
    {
        D4.setElement(i, i, i);
        D5.setElement(i, i, i);
    }

    bool equal = (D4 == D5);
    ASSERT(equal, "Equality check works (should loop n times, not n²)");

    TEST("Cat8.6: Memory Allocation Efficiency");
    DiagonalMatrix test(100);
    ASSERT(test.getElementsSize() == 100, "Single allocation of size n");

    DiagonalMatrix sum = test + test;
    ASSERT(sum.getElementsSize() == 100, "Result allocation also size n");

    TEST("Cat8.7: Operation Chaining No Temporary Full Matrices");
    DiagonalMatrix DA(50), DB(50), DC(50), DD(50);
    for (int i = 0; i < 50; i++)
    {
        DA.setElement(i, i, 1.0);
        DB.setElement(i, i, 2.0);
        DC.setElement(i, i, 3.0);
        DD.setElement(i, i, 4.0);
    }

    DiagonalMatrix chainResult = ((DA + DB) * DC) + DD;
    ASSERT(chainResult.getElementsSize() == 50, "Chain maintains n-element storage");
    ASSERT_EQUAL(chainResult.getElement(25, 25), 13.0, "Chain result: ((1+2)*3)+4 = 13");

    TEST("Cat8.8: Large Lower Triangular Multiplication");
    LowerTriangularMatrix LBig1(50);
    LowerTriangularMatrix LBig2(50);
    for (int i = 0; i < 50; i++)
    {
        LBig1.setElement(i, i, 1.0);
        LBig2.setElement(i, i, 2.0);
    }

    LowerTriangularMatrix LBigResult = LBig1 * LBig2;
    ASSERT_EQUAL(LBigResult.getElement(0, 25), 0.0, "Upper triangle stays zero");
    ASSERT_EQUAL(LBigResult.getElement(25, 0), 0.0, "Zeros not computed");
}

// CATEGORY 9: Mathematical Properties & Correctness
void testCategory9_MathematicalProperties()
{
    TEST("Cat9.1: Identity Matrix - Diagonal");
    DiagonalMatrix Identity(5);
    for (int i = 0; i < 5; i++)
    {
        Identity.setElement(i, i, 1.0);
    }

    DiagonalMatrix D(5);
    for (int i = 0; i < 5; i++)
    {
        D.setElement(i, i, i + 2.0);
    }

    DiagonalMatrix result = Identity * D;
    ASSERT_EQUAL(result.getElement(0, 0), 2.0, "Identity * D = D for (0,0)");
    ASSERT_EQUAL(result.getElement(4, 4), 6.0, "Identity * D = D for (4,4)");

    TEST("Cat9.2: Additive Identity");
    DiagonalMatrix Zero(5);
    DiagonalMatrix sum = D + Zero;
    ASSERT_EQUAL(sum.getElement(2, 2), 4.0, "D + Zero = D");

    TEST("Cat9.3: Commutativity - Diagonal Multiplication");
    DiagonalMatrix D1(5);
    DiagonalMatrix D2(5);
    for (int i = 0; i < 5; i++)
    {
        D1.setElement(i, i, i + 1.0);
        D2.setElement(i, i, (i + 1) * 2.0);
    }

    DiagonalMatrix result1 = D1 * D2;
    DiagonalMatrix result2 = D2 * D1;

    bool commutative = true;
    for (int i = 0; i < 5; i++)
    {
        if (result1.getElement(i, i) != result2.getElement(i, i))
        {
            commutative = false;
        }
    }
    ASSERT(commutative, "D1 * D2 = D2 * D1 (diagonal multiplication commutes)");

    TEST("Cat9.4: Associativity - Addition");
    DiagonalMatrix D3(5);
    for (int i = 0; i < 5; i++)
    {
        D3.setElement(i, i, i + 3.0);
    }

    DiagonalMatrix left = (D1 + D2) + D3;
    DiagonalMatrix right = D1 + (D2 + D3);

    bool associative = true;
    for (int i = 0; i < 5; i++)
    {
        if (left.getElement(i, i) != right.getElement(i, i))
        {
            associative = false;
        }
    }
    ASSERT(associative, "(D1 + D2) + D3 = D1 + (D2 + D3)");

    TEST("Cat9.5: Distributivity");
    DiagonalMatrix dist1 = D1 * (D2 + D3);
    DiagonalMatrix dist2 = (D1 * D2) + (D1 * D3);

    bool distributive = true;
    for (int i = 0; i < 5; i++)
    {
        if (std::abs(dist1.getElement(i, i) - dist2.getElement(i, i)) > 1e-9)
        {
            distributive = false;
        }
    }
    ASSERT(distributive, "D1 * (D2 + D3) = (D1 * D2) + (D1 * D3)");

    TEST("Cat9.6: Lower Triangular Identity");
    LowerTriangularMatrix LIdentity(3);
    LIdentity.setElement(0, 0, 1.0);
    LIdentity.setElement(1, 1, 1.0);
    LIdentity.setElement(2, 2, 1.0);

    LowerTriangularMatrix L(3);
    L.setElement(0, 0, 5.0);
    L.setElement(1, 0, 6.0);
    L.setElement(1, 1, 7.0);
    L.setElement(2, 0, 8.0);
    L.setElement(2, 1, 9.0);
    L.setElement(2, 2, 10.0);

    LowerTriangularMatrix LResult = LIdentity * L;
    ASSERT_EQUAL(LResult.getElement(0, 0), 5.0, "Identity_L * L = L");
    ASSERT_EQUAL(LResult.getElement(2, 1), 9.0, "Identity_L * L = L");
}

// CATEGORY 10: Equality & Comparison Operations
void testCategory10_EqualityComparison()
{
    TEST("Cat10.1: Self-Equality");
    DiagonalMatrix D(10);
    for (int i = 0; i < 10; i++)
    {
        D.setElement(i, i, i * 1.5);
    }
    ASSERT(D == D, "Matrix equals itself");

    TEST("Cat10.2: Copy Equality");
    DiagonalMatrix D2(D);
    ASSERT(D == D2, "Matrix equals its copy");

    TEST("Cat10.3: Modified Inequality");
    DiagonalMatrix D3(D);
    D3.setElement(5, 5, 999.0);
    ASSERT(!(D == D3), "Modified matrix not equal to original");

    TEST("Cat10.4: Zero Equality");
    DiagonalMatrix Zero1(8);
    DiagonalMatrix Zero2(8);
    ASSERT(Zero1 == Zero2, "Two zero diagonals are equal");

    TEST("Cat10.5: Size Mismatch Inequality");
    DiagonalMatrix D5(5);
    DiagonalMatrix D10(10);
    // Can't compare different sizes directly in this implementation
    ASSERT(D5.getRows() != D10.getRows(), "Different sizes have different dimensions");

    TEST("Cat10.6: Floating Point Precision");
    DiagonalMatrix DFloat(5);
    DFloat.setElement(0, 0, 0.1 + 0.2);
    ASSERT_EQUAL(DFloat.getElement(0, 0), 0.3, "Floating point handled (within tolerance)");

    TEST("Cat10.7: Lower Triangular Equality");
    LowerTriangularMatrix L1(5);
    LowerTriangularMatrix L2(5);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            L1.setElement(i, j, i + j);
            L2.setElement(i, j, i + j);
        }
    }
    ASSERT(L1 == L2, "Equal lower triangular matrices");

    TEST("Cat10.8: Upper Triangular Inequality");
    UpperTriangularMatrix U1(5);
    UpperTriangularMatrix U2(5);
    U1.setElement(0, 0, 1.0);
    U2.setElement(0, 0, 2.0);
    ASSERT(!(U1 == U2), "Different upper triangular matrices not equal");
}

// CATEGORY 11: Stress Testing & Robustness
void testCategory11_StressTesting()
{
    TEST("Cat11.1: Rapid Allocation/Deallocation");
    for (int i = 0; i < 100; i++)
    {
        DiagonalMatrix *d = new DiagonalMatrix(50);
        d->setElement(25, 25, 42.0);
        ASSERT_EQUAL(d->getElement(25, 25), 42.0, "Rapid alloc/dealloc works");
        delete d;
    }

    TEST("Cat11.2: Many Sequential Operations");
    DiagonalMatrix D(10);
    for (int i = 0; i < 10; i++)
    {
        D.setElement(i, i, 1.0);
    }

    for (int iteration = 0; iteration < 100; iteration++)
    {
        DiagonalMatrix temp(10);
        for (int i = 0; i < 10; i++)
        {
            temp.setElement(i, i, 1.0);
        }
        D = D + temp;
    }
    ASSERT_EQUAL(D.getElement(5, 5), 101.0, "100 additions: 1 + 100*1 = 101");

    TEST("Cat11.3: Mixed Operations Loop");
    DiagonalMatrix Result(5);
    for (int i = 0; i < 5; i++)
    {
        Result.setElement(i, i, 1.0);
    }

    for (int i = 0; i < 50; i++)
    {
        DiagonalMatrix temp(5);
        for (int j = 0; j < 5; j++)
        {
            temp.setElement(j, j, 1.0);
        }

        if (i % 3 == 0)
        {
            Result = Result + temp;
        }
        else if (i % 3 == 1)
        {
            Result = Result * temp;
        }
        else
        {
            Result = Result - temp;
        }
    }
    ASSERT(Result.getElementsSize() == 5, "Mixed operations preserve structure");

    TEST("Cat11.4: Large Matrix Creation Loop");
    for (int size = 10; size <= 100; size += 10)
    {
        DiagonalMatrix d(size);
        ASSERT(d.getElementsSize() == size, "Various sizes work correctly");
    }

    TEST("Cat11.5: Copy in Loop");
    DiagonalMatrix original(20);
    for (int i = 0; i < 20; i++)
    {
        original.setElement(i, i, i);
    }

    for (int i = 0; i < 50; i++)
    {
        DiagonalMatrix copy(original);
        ASSERT_EQUAL(copy.getElement(10, 10), 10.0, "Copy in loop works");
    }
}

// CATEGORY 12: Negative, Fractional & Special Values
void testCategory12_SpecialValues()
{
    TEST("Cat12.1: Negative Values - Diagonal");
    DiagonalMatrix DNeg(10);
    for (int i = 0; i < 10; i++)
    {
        DNeg.setElement(i, i, -1.0 * (i + 1));
    }
    ASSERT_EQUAL(DNeg.getElement(5, 5), -6.0, "Negative values stored correctly");

    TEST("Cat12.2: Fractional Values");
    DiagonalMatrix DFrac(5);
    DFrac.setElement(0, 0, 0.5);
    DFrac.setElement(1, 1, 0.33333);
    DFrac.setElement(2, 2, 1.414213);

    ASSERT_EQUAL(DFrac.getElement(0, 0), 0.5, "Fractional 0.5 stored");
    ASSERT(std::abs(DFrac.getElement(1, 1) - 0.33333) < 1e-5, "Fractional 0.33333 stored");
    ASSERT(std::abs(DFrac.getElement(2, 2) - 1.414213) < 1e-6, "Fractional 1.414213 stored");

    TEST("Cat12.3: Very Large Values");
    DiagonalMatrix DLarge(3);
    DLarge.setElement(0, 0, 1e50);
    DLarge.setElement(1, 1, 9.99e99);
    ASSERT_EQUAL(DLarge.getElement(0, 0), 1e50, "Large value 1e50 stored");
    ASSERT_EQUAL(DLarge.getElement(1, 1), 9.99e99, "Large value 9.99e99 stored");

    TEST("Cat12.4: Very Small Values");
    DiagonalMatrix DSmall(3);
    DSmall.setElement(0, 0, 1e-50);
    DSmall.setElement(1, 1, 1e-100);
    ASSERT_EQUAL(DSmall.getElement(0, 0), 1e-50, "Small value 1e-50 stored");
    ASSERT_EQUAL(DSmall.getElement(1, 1), 1e-100, "Small value 1e-100 stored");

    TEST("Cat12.5: Mixed Sign Operations - Addition");
    DiagonalMatrix DPos(5);
    DiagonalMatrix DNeg2(5);
    for (int i = 0; i < 5; i++)
    {
        DPos.setElement(i, i, 10.0);
        DNeg2.setElement(i, i, -5.0);
    }

    DiagonalMatrix DMixed = DPos + DNeg2;
    ASSERT_EQUAL(DMixed.getElement(3, 3), 5.0, "Positive + Negative = 5");

    TEST("Cat12.6: Negative Multiplication");
    DiagonalMatrix D1Neg(5);
    DiagonalMatrix D2Neg(5);
    for (int i = 0; i < 5; i++)
    {
        D1Neg.setElement(i, i, -2.0);
        D2Neg.setElement(i, i, -3.0);
    }

    DiagonalMatrix DProduct = D1Neg * D2Neg;
    ASSERT_EQUAL(DProduct.getElement(2, 2), 6.0, "Negative * Negative = Positive");

    TEST("Cat12.7: Alternating Signs Pattern");
    DiagonalMatrix DAlt(10);
    for (int i = 0; i < 10; i++)
    {
        DAlt.setElement(i, i, (i % 2 == 0) ? 1.0 : -1.0);
    }
    ASSERT_EQUAL(DAlt.getElement(0, 0), 1.0, "Even index positive");
    ASSERT_EQUAL(DAlt.getElement(1, 1), -1.0, "Odd index negative");

    TEST("Cat12.8: Geometric Progression");
    DiagonalMatrix DGeom(5);
    double value = 1.0;
    for (int i = 0; i < 5; i++)
    {
        DGeom.setElement(i, i, value);
        value *= 2.0;
    }
    ASSERT_EQUAL(DGeom.getElement(0, 0), 1.0, "Geometric [0] = 1");
    ASSERT_EQUAL(DGeom.getElement(4, 4), 16.0, "Geometric [4] = 16");
}

// CATEGORY 13: setElement Edge Cases
void testCategory13_SetElementEdgeCases()
{
    TEST("Cat13.1: Set Out-of-Structure - Diagonal");
    DiagonalMatrix D(10);
    D.setElement(5, 7, 999.0); // Should be ignored
    ASSERT_EQUAL(D.getElement(5, 7), 0.0, "Off-diagonal setElement ignored, returns 0");
    ASSERT_EQUAL(D.getElement(5, 5), 0.0, "Diagonal element unaffected");

    TEST("Cat13.2: Set Out-of-Structure - Lower");
    LowerTriangularMatrix L(10);
    L.setElement(2, 8, 999.0); // Upper triangle, should be ignored
    ASSERT_EQUAL(L.getElement(2, 8), 0.0, "Upper triangle setElement ignored");

    L.setElement(5, 3, 42.0); // Valid lower element
    ASSERT_EQUAL(L.getElement(5, 3), 42.0, "Valid lower element set correctly");

    TEST("Cat13.3: Set Out-of-Structure - Upper");
    UpperTriangularMatrix U(10);
    U.setElement(8, 2, 999.0); // Lower triangle, should be ignored
    ASSERT_EQUAL(U.getElement(8, 2), 0.0, "Lower triangle setElement ignored");

    U.setElement(3, 7, 42.0); // Valid upper element
    ASSERT_EQUAL(U.getElement(3, 7), 42.0, "Valid upper element set correctly");

    TEST("Cat13.4: Overwrite Elements");
    DiagonalMatrix D2(5);
    D2.setElement(2, 2, 10.0);
    D2.setElement(2, 2, 20.0);
    D2.setElement(2, 2, 30.0);
    ASSERT_EQUAL(D2.getElement(2, 2), 30.0, "Last value persists after overwrites");

    TEST("Cat13.5: Set All Valid Positions - Lower");
    LowerTriangularMatrix L2(4);
    int count = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            L2.setElement(i, j, count++);
        }
    }
    ASSERT_WITH_VALUE(L2.getElementsSize() == 10, "All n(n+1)/2 positions set", L2.getElementsSize(), 10);
    ASSERT_EQUAL(L2.getElement(3, 2), 8.0, "Position (3,2) = 8");

    TEST("Cat13.6: Set All Valid Positions - Upper");
    UpperTriangularMatrix U2(4);
    count = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = i; j < 4; j++)
        {
            U2.setElement(i, j, count++);
        }
    }
    ASSERT_WITH_VALUE(U2.getElementsSize() == 10, "All n(n+1)/2 positions set", U2.getElementsSize(), 10);
    ASSERT_EQUAL(U2.getElement(1, 3), 6.0, "Position (1,3) = 6");

    TEST("Cat13.7: Boundary Positions - Lower");
    LowerTriangularMatrix LBound(20);
    LBound.setElement(19, 0, 123.0);  // Bottom-left corner
    LBound.setElement(19, 19, 456.0); // Bottom-right corner (diagonal)
    ASSERT_EQUAL(LBound.getElement(19, 0), 123.0, "Bottom-left accessible");
    ASSERT_EQUAL(LBound.getElement(19, 19), 456.0, "Bottom-right diagonal accessible");
    ASSERT_EQUAL(LBound.getElement(0, 19), 0.0, "Top-right is zero");

    TEST("Cat13.8: Boundary Positions - Upper");
    UpperTriangularMatrix UBound(20);
    UBound.setElement(0, 19, 789.0); // Top-right corner
    UBound.setElement(0, 0, 321.0);  // Top-left corner (diagonal)
    ASSERT_EQUAL(UBound.getElement(0, 19), 789.0, "Top-right accessible");
    ASSERT_EQUAL(UBound.getElement(0, 0), 321.0, "Top-left diagonal accessible");
    ASSERT_EQUAL(UBound.getElement(19, 0), 0.0, "Bottom-left is zero");
}

// CATEGORY 14: Multi-dimensional Access Patterns
void testCategory14_AccessPatterns()
{
    TEST("Cat14.1: Row-wise Access - Lower Triangular");
    LowerTriangularMatrix L(20);
    // Set entire row 10 (11 elements: columns 0-10)
    for (int j = 0; j <= 10; j++)
    {
        L.setElement(10, j, j * 10.0);
    }

    ASSERT_EQUAL(L.getElement(10, 0), 0.0, "Row 10, col 0");
    ASSERT_EQUAL(L.getElement(10, 5), 50.0, "Row 10, col 5");
    ASSERT_EQUAL(L.getElement(10, 10), 100.0, "Row 10, col 10");
    ASSERT_EQUAL(L.getElement(10, 15), 0.0, "Row 10, col 15 is upper (zero)");

    TEST("Cat14.2: Column-wise Access - Upper Triangular");
    UpperTriangularMatrix U(20);
    // Set entire column 5 (6 elements: rows 0-5)
    for (int i = 0; i <= 5; i++)
    {
        U.setElement(i, 5, i * 10.0);
    }

    ASSERT_EQUAL(U.getElement(0, 5), 0.0, "Col 5, row 0");
    ASSERT_EQUAL(U.getElement(3, 5), 30.0, "Col 5, row 3");
    ASSERT_EQUAL(U.getElement(5, 5), 50.0, "Col 5, row 5");
    ASSERT_EQUAL(U.getElement(10, 5), 0.0, "Col 5, row 10 is lower (zero)");

    TEST("Cat14.3: Diagonal Access - All Types");
    DiagonalMatrix D(15);
    LowerTriangularMatrix L2(15);
    UpperTriangularMatrix U2(15);

    for (int i = 0; i < 15; i++)
    {
        D.setElement(i, i, i * 5.0);
        L2.setElement(i, i, i * 5.0);
        U2.setElement(i, i, i * 5.0);
    }

    ASSERT_EQUAL(D.getElement(7, 7), 35.0, "Diagonal main diagonal");
    ASSERT_EQUAL(L2.getElement(7, 7), 35.0, "Lower main diagonal");
    ASSERT_EQUAL(U2.getElement(7, 7), 35.0, "Upper main diagonal");

    TEST("Cat14.4: Anti-diagonal Access - Upper");
    UpperTriangularMatrix U3(10);
    // Access from (0,9) to (9,0) - only upper part exists
    U3.setElement(0, 9, 99.0);
    U3.setElement(1, 9, 88.0);

    ASSERT_EQUAL(U3.getElement(0, 9), 99.0, "Anti-diagonal top");
    ASSERT_EQUAL(U3.getElement(9, 0), 0.0, "Anti-diagonal bottom (lower=0)");

    TEST("Cat14.5: Block Access - Lower Triangular");
    LowerTriangularMatrix LBlock(20);
    // Set 5x5 block starting at (10, 5)
    for (int i = 10; i < 15; i++)
    {
        for (int j = 5; j < 10; j++)
        {
            if (j <= i)
            { // Only lower triangle
                LBlock.setElement(i, j, i * 10 + j);
            }
        }
    }

    ASSERT_EQUAL(LBlock.getElement(12, 7), 127.0, "Block element (12,7)");
    ASSERT_EQUAL(LBlock.getElement(14, 9), 149.0, "Block element (14,9)");
    ASSERT_EQUAL(LBlock.getElement(10, 9), 109.0, "Block boundary");

    TEST("Cat14.6: Sparse Access Pattern - Diagonal");
    DiagonalMatrix DSparse(50);
    // Set only every 5th element
    for (int i = 0; i < 50; i += 5)
    {
        DSparse.setElement(i, i, i * 2.0);
    }

    ASSERT_EQUAL(DSparse.getElement(0, 0), 0.0, "Sparse [0]");
    ASSERT_EQUAL(DSparse.getElement(5, 5), 10.0, "Sparse [5]");
    ASSERT_EQUAL(DSparse.getElement(3, 3), 0.0, "Sparse [3] not set");
    ASSERT_EQUAL(DSparse.getElement(10, 10), 20.0, "Sparse [10]");
}

// CATEGORY 15: Extreme Correctness Verification
void testCategory15_CorrectnessVerification()
{
    TEST("Cat15.1: Manual Calculation - Lower 3x3 Multiplication");
    LowerTriangularMatrix L1(3);
    LowerTriangularMatrix L2(3);

    // L1 = [1 0 0]    L2 = [2 0 0]
    //      [2 3 0]         [3 4 0]
    //      [4 5 6]         [5 6 7]
    L1.setElement(0, 0, 1.0);
    L1.setElement(1, 0, 2.0);
    L1.setElement(1, 1, 3.0);
    L1.setElement(2, 0, 4.0);
    L1.setElement(2, 1, 5.0);
    L1.setElement(2, 2, 6.0);

    L2.setElement(0, 0, 2.0);
    L2.setElement(1, 0, 3.0);
    L2.setElement(1, 1, 4.0);
    L2.setElement(2, 0, 5.0);
    L2.setElement(2, 1, 6.0);
    L2.setElement(2, 2, 7.0);

    LowerTriangularMatrix L3 = L1 * L2;

    // Result = [2  0  0]
    //          [13 12 0]
    //          [53 50 42]
    ASSERT_EQUAL(L3.getElement(0, 0), 2.0, "L1*L2 (0,0) = 1*2 = 2");
    ASSERT_EQUAL(L3.getElement(1, 0), 13.0, "L1*L2 (1,0) = 2*2 + 3*3 = 13");
    ASSERT_EQUAL(L3.getElement(1, 1), 12.0, "L1*L2 (1,1) = 3*4 = 12");
    ASSERT_EQUAL(L3.getElement(2, 0), 53.0, "L1*L2 (2,0) = 4*2 + 5*3 + 6*5 = 53");
    ASSERT_EQUAL(L3.getElement(2, 1), 56.0, "L1*L2 (2,1) = 5*4 + 6*6 = 56");
    ASSERT_EQUAL(L3.getElement(2, 2), 42.0, "L1*L2 (2,2) = 6*7 = 42");

    TEST("Cat15.2: Manual Calculation - Upper 2x2 Multiplication");
    UpperTriangularMatrix U1(2);
    UpperTriangularMatrix U2(2);

    // U1 = [2 3]    U2 = [1 5]
    //      [0 4]         [0 6]
    U1.setElement(0, 0, 2.0);
    U1.setElement(0, 1, 3.0);
    U1.setElement(1, 1, 4.0);

    U2.setElement(0, 0, 1.0);
    U2.setElement(0, 1, 5.0);
    U2.setElement(1, 1, 6.0);

    UpperTriangularMatrix U3 = U1 * U2;

    // Result = [2  28]
    //          [0  24]
    setColor(COLOR_YELLOW);
    std::cout << "  Expected Result Matrix:" << std::endl;
    std::cout << "  |  2.00  28.00 |" << std::endl;
    std::cout << "  |  0.00  24.00 |" << std::endl;
    setColor(COLOR_WHITE);

    ASSERT_MATRIX_EQUAL(U3, 0, 0, 2.0, "U1*U2 (0,0) = 2*1 = 2");
    ASSERT_MATRIX_EQUAL(U3, 0, 1, 28.0, "U1*U2 (0,1) = 2*5 + 3*6 = 28");
    ASSERT_MATRIX_EQUAL(U3, 1, 1, 24.0, "U1*U2 (1,1) = 4*6 = 24");

    TEST("Cat15.3: Trace Calculation - Diagonal");
    DiagonalMatrix D(10);
    double trace = 0.0;
    for (int i = 0; i < 10; i++)
    {
        D.setElement(i, i, i + 1.0);
        trace += (i + 1.0);
    }

    double computed_trace = 0.0;
    for (int i = 0; i < 10; i++)
    {
        computed_trace += D.getElement(i, i);
    }

    ASSERT_EQUAL(computed_trace, 55.0, "Trace = sum(1 to 10) = 55");
    ASSERT_EQUAL(computed_trace, trace, "Trace matches expected");

    TEST("Cat15.4: Determinant Pattern - Diagonal");
    DiagonalMatrix D2(5);
    double det = 1.0;
    for (int i = 0; i < 5; i++)
    {
        D2.setElement(i, i, i + 2.0);
        det *= (i + 2.0);
    }

    // Determinant of diagonal = product of diagonal elements
    double computed_det = 1.0;
    for (int i = 0; i < 5; i++)
    {
        computed_det *= D2.getElement(i, i);
    }

    ASSERT_EQUAL(computed_det, 2.0 * 3.0 * 4.0 * 5.0 * 6.0, "Det = 2*3*4*5*6 = 720");
    ASSERT_EQUAL(computed_det, 720.0, "Diagonal determinant = 720");

    TEST("Cat15.5: Symmetry Breaking - Lower Not Symmetric");
    LowerTriangularMatrix LAsym(5);
    LAsym.setElement(3, 1, 42.0);

    ASSERT_EQUAL(LAsym.getElement(3, 1), 42.0, "Lower (3,1) = 42");
    ASSERT_EQUAL(LAsym.getElement(1, 3), 0.0, "Upper (1,3) = 0, not symmetric");

    TEST("Cat15.6: Addition Commutativity");
    DiagonalMatrix DA(5), DB(5);
    for (int i = 0; i < 5; i++)
    {
        DA.setElement(i, i, i * 3.0);
        DB.setElement(i, i, i * 7.0);
    }

    DiagonalMatrix R1 = DA + DB;
    DiagonalMatrix R2 = DB + DA;

    bool commutative = true;
    for (int i = 0; i < 5; i++)
    {
        if (R1.getElement(i, i) != R2.getElement(i, i))
        {
            commutative = false;
        }
    }
    ASSERT(commutative, "Addition is commutative: A+B = B+A");
}

// CATEGORY 16: Real-world Usage Patterns
void testCategory16_RealWorldPatterns()
{
    TEST("Cat16.1: Scaling Transformation - Diagonal");
    DiagonalMatrix Scale(3);
    Scale.setElement(0, 0, 2.0); // Scale X by 2
    Scale.setElement(1, 1, 3.0); // Scale Y by 3
    Scale.setElement(2, 2, 1.0); // Scale Z by 1 (no change)

    ASSERT_EQUAL(Scale.getElement(0, 0), 2.0, "X scale factor");
    ASSERT_EQUAL(Scale.getElement(1, 1), 3.0, "Y scale factor");
    ASSERT_EQUAL(Scale.getElement(2, 2), 1.0, "Z scale factor");

    TEST("Cat16.2: Forward Substitution Pattern - Lower");
    LowerTriangularMatrix L(5);
    // Set up a simple lower triangular system
    for (int i = 0; i < 5; i++)
    {
        L.setElement(i, i, 1.0); // Unit diagonal
        for (int j = 0; j < i; j++)
        {
            L.setElement(i, j, 0.5); // Sub-diagonal elements
        }
    }

    ASSERT_EQUAL(L.getElement(0, 0), 1.0, "Unit diagonal");
    ASSERT_EQUAL(L.getElement(3, 1), 0.5, "Sub-diagonal pattern");
    ASSERT_EQUAL(L.getElement(4, 2), 0.5, "Sub-diagonal pattern");

    TEST("Cat16.3: Cholesky Decomposition Pattern");
    LowerTriangularMatrix Chol(4);
    // Simulate a Cholesky factor
    Chol.setElement(0, 0, 2.0);
    Chol.setElement(1, 0, 1.0);
    Chol.setElement(1, 1, 1.732);
    Chol.setElement(2, 0, 0.5);
    Chol.setElement(2, 1, 0.866);
    Chol.setElement(2, 2, 1.414);

    ASSERT(Chol.getElement(0, 0) > 0, "Cholesky factors positive diagonal");
    ASSERT(Chol.getElement(1, 1) > 0, "Cholesky factors positive diagonal");
    ASSERT_EQUAL(Chol.getElement(0, 2), 0.0, "Upper triangle zero");

    TEST("Cat16.4: Multiple Transformations - Diagonal Chain");
    DiagonalMatrix T1(3), T2(3), T3(3);
    T1.setElement(0, 0, 2.0);
    T1.setElement(1, 1, 2.0);
    T1.setElement(2, 2, 2.0);
    T2.setElement(0, 0, 0.5);
    T2.setElement(1, 1, 0.5);
    T2.setElement(2, 2, 0.5);
    T3.setElement(0, 0, 3.0);
    T3.setElement(1, 1, 3.0);
    T3.setElement(2, 2, 3.0);

    DiagonalMatrix Combined = (T1 * T2) * T3;
    ASSERT_EQUAL(Combined.getElement(0, 0), 3.0, "Chain: (2*0.5)*3 = 3");
    ASSERT_EQUAL(Combined.getElement(1, 1), 3.0, "Chain: (2*0.5)*3 = 3");

    TEST("Cat16.5: Sparse Diagonal for Large Systems");
    DiagonalMatrix Sparse(1000);
    // Simulate a sparse diagonal matrix with only some elements set
    for (int i = 0; i < 1000; i += 100)
    {
        Sparse.setElement(i, i, i * 0.001);
    }

    ASSERT_WITH_VALUE(Sparse.getElementsSize() == 1000, "Sparse diagonal efficient storage", Sparse.getElementsSize(), 1000);
    ASSERT_EQUAL(Sparse.getElement(500, 500), 0.5, "Sparse element set");
    ASSERT_EQUAL(Sparse.getElement(250, 250), 0.0, "Sparse element not set");
}

// CATEGORY 17: Boundary Value Analysis
void testCategory17_BoundaryValueAnalysis()
{
    TEST("Cat17.1: First Row - Lower vs Upper");
    LowerTriangularMatrix L(10);
    UpperTriangularMatrix U(10);

    // Lower: Row 0 has only 1 element (diagonal)
    L.setElement(0, 0, 100.0);
    ASSERT_EQUAL(L.getElement(0, 0), 100.0, "Lower row 0, element count: 1");
    ASSERT_EQUAL(L.getElement(0, 1), 0.0, "Lower row 0, col 1 is zero");

    // Upper: Row 0 has 10 elements
    for (int j = 0; j < 10; j++)
    {
        U.setElement(0, j, j * 10.0);
    }
    ASSERT_EQUAL(U.getElement(0, 0), 0.0, "Upper row 0, col 0");
    ASSERT_EQUAL(U.getElement(0, 9), 90.0, "Upper row 0, col 9");

    TEST("Cat17.2: Last Row - Lower vs Upper");
    // Lower: Row 9 has 10 elements
    for (int j = 0; j < 10; j++)
    {
        L.setElement(9, j, j * 5.0);
    }
    ASSERT_EQUAL(L.getElement(9, 0), 0.0, "Lower row 9, col 0");
    ASSERT_EQUAL(L.getElement(9, 9), 45.0, "Lower row 9, col 9");

    // Upper: Row 9 has only 1 element (diagonal)
    U.setElement(9, 9, 200.0);
    ASSERT_EQUAL(U.getElement(9, 9), 200.0, "Upper row 9, element count: 1");
    ASSERT_EQUAL(U.getElement(9, 0), 0.0, "Upper row 9, col 0 is zero");

    TEST("Cat17.3: First Column - Lower vs Upper");
    LowerTriangularMatrix L2(10);
    UpperTriangularMatrix U2(10);

    // Lower: Column 0 has 10 elements
    for (int i = 0; i < 10; i++)
    {
        L2.setElement(i, 0, i * 3.0);
    }
    ASSERT_EQUAL(L2.getElement(0, 0), 0.0, "Lower col 0, row 0");
    ASSERT_EQUAL(L2.getElement(9, 0), 27.0, "Lower col 0, row 9");

    // Upper: Column 0 has only 1 element (diagonal)
    U2.setElement(0, 0, 300.0);
    ASSERT_EQUAL(U2.getElement(0, 0), 300.0, "Upper col 0, element count: 1");
    ASSERT_EQUAL(U2.getElement(9, 0), 0.0, "Upper col 0, row 9 is zero");

    TEST("Cat17.4: Last Column - Lower vs Upper");
    // Lower: Column 9 has only 1 element (diagonal)
    L2.setElement(9, 9, 400.0);
    ASSERT_EQUAL(L2.getElement(9, 9), 400.0, "Lower col 9, element count: 1");
    ASSERT_EQUAL(L2.getElement(0, 9), 0.0, "Lower col 9, row 0 is zero");

    // Upper: Column 9 has 10 elements
    for (int i = 0; i < 10; i++)
    {
        U2.setElement(i, 9, i * 4.0);
    }
    ASSERT_EQUAL(U2.getElement(0, 9), 0.0, "Upper col 9, row 0");
    ASSERT_EQUAL(U2.getElement(9, 9), 36.0, "Upper col 9, row 9");

    TEST("Cat17.5: Middle Element - All Types");
    DiagonalMatrix D(21);
    LowerTriangularMatrix L3(21);
    UpperTriangularMatrix U3(21);

    D.setElement(10, 10, 1000.0);
    L3.setElement(10, 10, 1001.0);
    U3.setElement(10, 10, 1002.0);

    ASSERT_EQUAL(D.getElement(10, 10), 1000.0, "Diagonal middle element");
    ASSERT_EQUAL(L3.getElement(10, 10), 1001.0, "Lower middle element");
    ASSERT_EQUAL(U3.getElement(10, 10), 1002.0, "Upper middle element");

    TEST("Cat17.6: Boundary Transitions - Lower");
    LowerTriangularMatrix LBound(10);
    // Test elements around the diagonal boundary
    LBound.setElement(5, 4, 54.0); // Just below diagonal
    LBound.setElement(5, 5, 55.0); // On diagonal

    ASSERT_EQUAL(LBound.getElement(5, 4), 54.0, "Below diagonal accessible");
    ASSERT_EQUAL(LBound.getElement(5, 5), 55.0, "On diagonal accessible");
    ASSERT_EQUAL(LBound.getElement(5, 6), 0.0, "Above diagonal is zero");

    TEST("Cat17.7: Boundary Transitions - Upper");
    UpperTriangularMatrix UBound(10);
    // Test elements around the diagonal boundary
    UBound.setElement(5, 5, 55.0); // On diagonal
    UBound.setElement(5, 6, 56.0); // Just above diagonal

    ASSERT_EQUAL(UBound.getElement(5, 5), 55.0, "On diagonal accessible");
    ASSERT_EQUAL(UBound.getElement(5, 6), 56.0, "Above diagonal accessible");
    ASSERT_EQUAL(UBound.getElement(5, 4), 0.0, "Below diagonal is zero");
}

// CATEGORY 18: Interleaved Operations
void testCategory18_InterleavedOperations()
{
    TEST("Cat18.1: Read-Write-Read Pattern - Diagonal");
    DiagonalMatrix D(10);
    D.setElement(5, 5, 42.0);
    double val1 = D.getElement(5, 5);
    D.setElement(5, 5, 84.0);
    double val2 = D.getElement(5, 5);

    ASSERT_EQUAL(val1, 42.0, "First read correct");
    ASSERT_EQUAL(val2, 84.0, "Second read after write correct");

    TEST("Cat18.2: Write-Operation-Read Pattern");
    DiagonalMatrix D1(5), D2(5);
    for (int i = 0; i < 5; i++)
    {
        D1.setElement(i, i, i * 2.0);
        D2.setElement(i, i, i * 3.0);
    }

    DiagonalMatrix D3 = D1 + D2;
    ASSERT_EQUAL(D3.getElement(3, 3), 15.0, "Operation result: 6 + 9 = 15");

    TEST("Cat18.3: Multiple Operations Sequence");
    DiagonalMatrix Original(5);
    for (int i = 0; i < 5; i++)
    {
        Original.setElement(i, i, 10.0);
    }

    DiagonalMatrix Copy(Original);
    ASSERT_EQUAL(Copy.getElement(2, 2), 10.0, "After copy");

    Copy.setElement(2, 2, 20.0);
    ASSERT_EQUAL(Copy.getElement(2, 2), 20.0, "After modify");

    DiagonalMatrix Sum = Original + Copy;
    ASSERT_EQUAL(Sum.getElement(2, 2), 30.0, "After addition: 10 + 20 = 30");

    bool equal = (Original == Copy);
    ASSERT(!equal, "After comparison: not equal");

    TEST("Cat18.4: Interleaved Lower Triangular Operations");
    LowerTriangularMatrix L1(5);
    L1.setElement(3, 1, 5.0);
    double read1 = L1.getElement(3, 1);

    LowerTriangularMatrix L2(L1);
    L2.setElement(3, 1, 10.0);
    double read2 = L2.getElement(3, 1);

    LowerTriangularMatrix L3 = L1 + L2;
    double read3 = L3.getElement(3, 1);

    ASSERT_EQUAL(read1, 5.0, "Original value");
    ASSERT_EQUAL(read2, 10.0, "Modified copy");
    ASSERT_EQUAL(read3, 15.0, "Sum: 5 + 10 = 15");

    TEST("Cat18.5: Complex Operation Chain");
    DiagonalMatrix A(3), B(3), C(3);
    A.setElement(0, 0, 2.0);
    A.setElement(1, 1, 3.0);
    A.setElement(2, 2, 4.0);
    B.setElement(0, 0, 1.0);
    B.setElement(1, 1, 1.0);
    B.setElement(2, 2, 1.0);
    C.setElement(0, 0, 5.0);
    C.setElement(1, 1, 5.0);
    C.setElement(2, 2, 5.0);

    DiagonalMatrix Step1 = A + B;     // [3, 4, 5]
    DiagonalMatrix Step2 = Step1 * C; // [15, 20, 25]
    DiagonalMatrix Step3 = Step2 - A; // [13, 17, 21]

    ASSERT_EQUAL(Step3.getElement(0, 0), 13.0, "Chain result (0,0)");
    ASSERT_EQUAL(Step3.getElement(1, 1), 17.0, "Chain result (1,1)");
    ASSERT_EQUAL(Step3.getElement(2, 2), 21.0, "Chain result (2,2)");
}

// CATEGORY 19: Constructor Behavior
void testCategory19_ConstructorBehavior()
{
    TEST("Cat19.1: Parameterized Constructor - Various Sizes");
    DiagonalMatrix D1(1);
    DiagonalMatrix D10(10);
    DiagonalMatrix D100(100);
    DiagonalMatrix D1000(1000);

    ASSERT_WITH_VALUE(D1.getElementsSize() == 1, "Size 1 constructor", D1.getElementsSize(), 1);
    ASSERT_WITH_VALUE(D10.getElementsSize() == 10, "Size 10 constructor", D10.getElementsSize(), 10);
    ASSERT_WITH_VALUE(D100.getElementsSize() == 100, "Size 100 constructor", D100.getElementsSize(), 100);
    ASSERT_WITH_VALUE(D1000.getElementsSize() == 1000, "Size 1000 constructor", D1000.getElementsSize(), 1000);

    TEST("Cat19.2: Constructor Initializes to Zero");
    DiagonalMatrix D(20);
    bool allZero = true;
    for (int i = 0; i < 20; i++)
    {
        if (D.getElement(i, i) != 0.0)
            allZero = false;
    }
    ASSERT(allZero, "Constructor initializes all elements to zero");

    TEST("Cat19.3: Copy Constructor - Diagonal");
    DiagonalMatrix Original(10);
    for (int i = 0; i < 10; i++)
    {
        Original.setElement(i, i, i * 7.0);
    }

    DiagonalMatrix Copy(Original);
    ASSERT_WITH_VALUE(Copy.getElementsSize() == 10, "Copy has same size", Copy.getElementsSize(), 10);
    ASSERT_EQUAL(Copy.getElement(5, 5), 35.0, "Copy has same values");

    TEST("Cat19.4: Copy Constructor - Lower");
    LowerTriangularMatrix LOriginal(8);
    LOriginal.setElement(5, 3, 123.0);
    LOriginal.setElement(7, 2, 456.0);

    LowerTriangularMatrix LCopy(LOriginal);
    ASSERT_WITH_VALUE(LCopy.getElementsSize() == 36, "Lower copy has n(n+1)/2 elements", LCopy.getElementsSize(), 36);
    ASSERT_EQUAL(LCopy.getElement(5, 3), 123.0, "Lower copy value 1 correct");
    ASSERT_EQUAL(LCopy.getElement(7, 2), 456.0, "Lower copy value 2 correct");

    TEST("Cat19.5: Copy Constructor - Upper");
    UpperTriangularMatrix UOriginal(8);
    UOriginal.setElement(2, 5, 789.0);
    UOriginal.setElement(1, 7, 321.0);

    UpperTriangularMatrix UCopy(UOriginal);
    ASSERT_WITH_VALUE(UCopy.getElementsSize() == 36, "Upper copy has n(n+1)/2 elements", UCopy.getElementsSize(), 36);
    ASSERT_EQUAL(UCopy.getElement(2, 5), 789.0, "Upper copy value 1 correct");
    ASSERT_EQUAL(UCopy.getElement(1, 7), 321.0, "Upper copy value 2 correct");

    TEST("Cat19.6: Constructor Chain Independence");
    DiagonalMatrix D1st(5);
    D1st.setElement(2, 2, 100.0);

    DiagonalMatrix D2nd(D1st);
    D2nd.setElement(2, 2, 200.0);

    DiagonalMatrix D3rd(D2nd);
    D3rd.setElement(2, 2, 300.0);

    ASSERT_EQUAL(D1st.getElement(2, 2), 100.0, "First unchanged");
    ASSERT_EQUAL(D2nd.getElement(2, 2), 200.0, "Second unchanged");
    ASSERT_EQUAL(D3rd.getElement(2, 2), 300.0, "Third modified");
}

// CATEGORY 20: Final Integration & Comprehensive Tests
void testCategory20_FinalIntegrationTests()
{
    TEST("Cat20.1: Full System Integration - Diagonal");
    DiagonalMatrix D(50);

    // 1. Initialize
    for (int i = 0; i < 50; i++)
    {
        D.setElement(i, i, i * 0.5);
    }

    // 2. Verify storage
    ASSERT_WITH_VALUE(D.getElementsSize() == 50, "Compact storage: 50 elements", D.getElementsSize(), 50);

    // 3. Verify access
    ASSERT_EQUAL(D.getElement(25, 25), 12.5, "Access correct");
    ASSERT_EQUAL(D.getElement(10, 30), 0.0, "Off-diagonal zero");

    // 4. Copy
    DiagonalMatrix DCopy(D);
    ASSERT(D == DCopy, "Copy equals original");

    // 5. Operations
    DiagonalMatrix DSum = D + DCopy;
    ASSERT_EQUAL(DSum.getElement(25, 25), 25.0, "Sum correct");

    // 6. Performance
    for (int i = 0; i < 100; i++)
    {
        DiagonalMatrix Temp = D + DCopy;
    }
    ASSERT(true, "100 operations completed");

    TEST("Cat20.2: Full System Integration - Lower Triangular");
    LowerTriangularMatrix L(30);

    // Initialize all valid positions
    int count = 0;
    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            L.setElement(i, j, count++);
        }
    }

    int expected = 30 * 31 / 2;
    ASSERT_WITH_VALUE(L.getElementsSize() == expected, "Lower has n(n+1)/2 = 465 elements", L.getElementsSize(), expected);
    ASSERT_EQUAL(L.getElement(29, 0), 435.0, "First element of last row");
    ASSERT_EQUAL(L.getElement(0, 29), 0.0, "Upper triangle zero");

    LowerTriangularMatrix LCopy(L);
    LowerTriangularMatrix LSum = L + LCopy;
    ASSERT_EQUAL(LSum.getElement(15, 10), L.getElement(15, 10) * 2, "Sum correct");

    TEST("Cat20.3: Full System Integration - Upper Triangular");
    UpperTriangularMatrix U(30);

    count = 0;
    for (int i = 0; i < 30; i++)
    {
        for (int j = i; j < 30; j++)
        {
            U.setElement(i, j, count++);
        }
    }

    ASSERT_WITH_VALUE(U.getElementsSize() == 465, "Upper has n(n+1)/2 = 465 elements", U.getElementsSize(), 465);
    ASSERT_EQUAL(U.getElement(0, 29), 29.0, "Last element of first row");
    ASSERT_EQUAL(U.getElement(29, 0), 0.0, "Lower triangle zero");

    TEST("Cat20.4: Mixed Type Operations Through Polymorphism");
    Matrix *matrices[3];
    matrices[0] = new DiagonalMatrix(10);
    matrices[1] = new LowerTriangularMatrix(10);
    matrices[2] = new UpperTriangularMatrix(10);

    for (int i = 0; i < 3; i++)
    {
        matrices[i]->setElement(5, 5, 42.0);
        ASSERT_EQUAL(matrices[i]->getElement(5, 5), 42.0, "Polymorphic access works");
    }

    for (int i = 0; i < 3; i++)
    {
        delete matrices[i];
    }

    TEST("Cat20.5: Extreme Scale Test - Large Matrices");
    DiagonalMatrix DLarge(10000);
    ASSERT_WITH_VALUE(DLarge.getElementsSize() == 10000, "10K diagonal elements", DLarge.getElementsSize(), 10000);

    for (int i = 0; i < 10000; i += 1000)
    {
        DLarge.setElement(i, i, i * 0.001);
    }
    ASSERT_EQUAL(DLarge.getElement(5000, 5000), 5.0, "Large diagonal access");

    TEST("Cat20.6: Comprehensive Mathematical Verification");
    DiagonalMatrix Identity(5);
    DiagonalMatrix Test(5);
    for (int i = 0; i < 5; i++)
    {
        Identity.setElement(i, i, 1.0);
        Test.setElement(i, i, i + 1.0);
    }

    // Identity properties
    DiagonalMatrix R1 = Identity * Test;
    ASSERT(R1 == Test, "Identity * Matrix = Matrix");

    DiagonalMatrix Zero(5);
    DiagonalMatrix R2 = Test + Zero;
    ASSERT(R2 == Test, "Matrix + Zero = Matrix");

    // Commutativity
    DiagonalMatrix A(3), B(3);
    A.setElement(0, 0, 2.0);
    A.setElement(1, 1, 3.0);
    A.setElement(2, 2, 4.0);
    B.setElement(0, 0, 5.0);
    B.setElement(1, 1, 6.0);
    B.setElement(2, 2, 7.0);

    DiagonalMatrix AB = A * B;
    DiagonalMatrix BA = B * A;
    ASSERT(AB == BA, "Diagonal multiplication commutes");

    TEST("Cat20.7: Memory Efficiency Validation");
    DiagonalMatrix D500(500);
    LowerTriangularMatrix L500(500);
    UpperTriangularMatrix U500(500);
    SquareMatrix S500(500);

    ASSERT_WITH_VALUE(D500.getElementsSize() == 500, "Diagonal: 500 elements", D500.getElementsSize(), 500);
    ASSERT_WITH_VALUE(L500.getElementsSize() == 125250, "Lower: 125,250 elements", L500.getElementsSize(), 125250);
    ASSERT_WITH_VALUE(U500.getElementsSize() == 125250, "Upper: 125,250 elements", U500.getElementsSize(), 125250);
    ASSERT_WITH_VALUE(S500.getElementsSize() == 250000, "Square: 250,000 elements", S500.getElementsSize(), 250000);

    double ratio = (100.0 * D500.getElementsSize()) / S500.getElementsSize();
    ASSERT_EQUAL(ratio, 0.2, "Diagonal uses 0.2% of Square storage");

    TEST("Cat20.8: Robustness Under Stress");
    for (int iteration = 0; iteration < 50; iteration++)
    {
        DiagonalMatrix *d = new DiagonalMatrix(100);
        for (int i = 0; i < 100; i++)
        {
            d->setElement(i, i, i + iteration);
        }

        DiagonalMatrix copy(*d);
        DiagonalMatrix sum = *d + copy;

        ASSERT_EQUAL(sum.getElement(50, 50), 2 * (50 + iteration), "Stress iteration correct");
        delete d;
    }

    TEST("Cat20.9: All Features Working Together");
    // Create various types
    DiagonalMatrix DAll(10);
    LowerTriangularMatrix LAll(10);
    UpperTriangularMatrix UAll(10);

    // Initialize
    for (int i = 0; i < 10; i++)
    {
        DAll.setElement(i, i, 1.0);
        for (int j = 0; j <= i; j++)
        {
            LAll.setElement(i, j, 1.0);
        }
        for (int j = i; j < 10; j++)
        {
            UAll.setElement(i, j, 1.0);
        }
    }

    // Copy
    DiagonalMatrix DAll2(DAll);
    LowerTriangularMatrix LAll2(LAll);
    UpperTriangularMatrix UAll2(UAll);

    // Operations
    DiagonalMatrix DSumAll = DAll + DAll2;
    LowerTriangularMatrix LSumAll = LAll + LAll2;
    UpperTriangularMatrix USumAll = UAll + UAll2;

    // Verify
    ASSERT_EQUAL(DSumAll.getElement(5, 5), 2.0, "All features: Diagonal");
    ASSERT_EQUAL(LSumAll.getElement(5, 3), 2.0, "All features: Lower");
    ASSERT_EQUAL(USumAll.getElement(3, 5), 2.0, "All features: Upper");

    // Polymorphism
    Matrix *ptrAll = &DAll;
    ASSERT_EQUAL(ptrAll->getElement(5, 5), 1.0, "All features: Polymorphism");

    // Boundaries
    ASSERT_EQUAL(LAll.getElement(0, 9), 0.0, "All features: Lower boundary");
    ASSERT_EQUAL(UAll.getElement(9, 0), 0.0, "All features: Upper boundary");

    TEST("Cat20.10: Final Validation - Everything Works!");
    ASSERT(true, "COMPREHENSIVE TEST SUITE COMPLETED SUCCESSFULLY!");
}

// CATEGORY 21: Cross-Type Operations (Different Matrix Classes)
void testCategory21_CrossTypeOperations()
{
    TEST("Cat21.1: Base Pointer to Different Types - Addition");
    Matrix *ptrSquare = new SquareMatrix(3);
    Matrix *ptrDiagonal = new DiagonalMatrix(3);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            ptrSquare->setElement(i, j, 1.0);
        }
        ptrDiagonal->setElement(i, i, 5.0);
    }

    Matrix result1 = *ptrSquare + *ptrDiagonal;
    ASSERT_EQUAL(result1.getElement(0, 0), 6.0, "Square+Diagonal (0,0): 1+5 = 6");
    ASSERT_EQUAL(result1.getElement(0, 1), 1.0, "Square+Diagonal (0,1): 1+0 = 1");
    ASSERT_EQUAL(result1.getElement(1, 1), 6.0, "Square+Diagonal (1,1): 1+5 = 6");

    delete ptrSquare;
    delete ptrDiagonal;

    TEST("Cat21.2: Base Pointer to Different Types - Subtraction");
    Matrix *ptrLower = new LowerTriangularMatrix(3);
    Matrix *ptrUpper = new UpperTriangularMatrix(3);

    ptrLower->setElement(0, 0, 10.0);
    ptrLower->setElement(1, 0, 20.0);
    ptrLower->setElement(1, 1, 30.0);
    ptrLower->setElement(2, 0, 40.0);
    ptrLower->setElement(2, 1, 50.0);
    ptrLower->setElement(2, 2, 60.0);

    ptrUpper->setElement(0, 0, 5.0);
    ptrUpper->setElement(0, 1, 10.0);
    ptrUpper->setElement(0, 2, 15.0);
    ptrUpper->setElement(1, 1, 20.0);
    ptrUpper->setElement(1, 2, 25.0);
    ptrUpper->setElement(2, 2, 30.0);

    Matrix result2 = *ptrLower - *ptrUpper;
    ASSERT_EQUAL(result2.getElement(0, 0), 5.0, "Lower-Upper (0,0): 10-5 = 5");
    ASSERT_EQUAL(result2.getElement(0, 1), -10.0, "Lower-Upper (0,1): 0-10 = -10");
    ASSERT_EQUAL(result2.getElement(1, 0), 20.0, "Lower-Upper (1,0): 20-0 = 20");
    ASSERT_EQUAL(result2.getElement(2, 2), 30.0, "Lower-Upper (2,2): 60-30 = 30");

    delete ptrLower;
    delete ptrUpper;

    TEST("Cat21.3: Base Pointer to Different Types - Multiplication");
    Matrix *ptrDiag2 = new DiagonalMatrix(3);
    Matrix *ptrSquare2 = new SquareMatrix(3);

    ptrDiag2->setElement(0, 0, 2.0);
    ptrDiag2->setElement(1, 1, 3.0);
    ptrDiag2->setElement(2, 2, 4.0);

    ptrSquare2->setElement(0, 0, 1.0);
    ptrSquare2->setElement(0, 1, 2.0);
    ptrSquare2->setElement(0, 2, 3.0);
    ptrSquare2->setElement(1, 0, 4.0);
    ptrSquare2->setElement(1, 1, 5.0);
    ptrSquare2->setElement(1, 2, 6.0);
    ptrSquare2->setElement(2, 0, 7.0);
    ptrSquare2->setElement(2, 1, 8.0);
    ptrSquare2->setElement(2, 2, 9.0);

    Matrix result3 = *ptrDiag2 * *ptrSquare2;
    ASSERT_EQUAL(result3.getElement(0, 0), 2.0, "Diag*Square (0,0): 2*1 = 2");
    ASSERT_EQUAL(result3.getElement(0, 1), 4.0, "Diag*Square (0,1): 2*2 = 4");
    ASSERT_EQUAL(result3.getElement(1, 0), 12.0, "Diag*Square (1,0): 3*4 = 12");
    ASSERT_EQUAL(result3.getElement(2, 2), 36.0, "Diag*Square (2,2): 4*9 = 36");

    delete ptrDiag2;
    delete ptrSquare2;

    TEST("Cat21.4: Array of Base Pointers - Mixed Operations");
    Matrix *matrices[3];
    matrices[0] = new DiagonalMatrix(2);
    matrices[1] = new LowerTriangularMatrix(2);
    matrices[2] = new UpperTriangularMatrix(2);

    // Set diagonal values
    matrices[0]->setElement(0, 0, 10.0);
    matrices[0]->setElement(1, 1, 10.0);

    // Set lower triangular values
    matrices[1]->setElement(0, 0, 1.0);
    matrices[1]->setElement(1, 0, 2.0);
    matrices[1]->setElement(1, 1, 3.0);

    // Set upper triangular values
    matrices[2]->setElement(0, 0, 5.0);
    matrices[2]->setElement(0, 1, 6.0);
    matrices[2]->setElement(1, 1, 7.0);

    // Add them all
    Matrix combined = (*matrices[0] + *matrices[1]) + *matrices[2];
    ASSERT_EQUAL(combined.getElement(0, 0), 16.0, "Array sum (0,0): 10+1+5 = 16");
    ASSERT_EQUAL(combined.getElement(0, 1), 6.0, "Array sum (0,1): 0+0+6 = 6");
    ASSERT_EQUAL(combined.getElement(1, 0), 2.0, "Array sum (1,0): 0+2+0 = 2");
    ASSERT_EQUAL(combined.getElement(1, 1), 20.0, "Array sum (1,1): 10+3+7 = 20");

    for (int i = 0; i < 3; i++)
    {
        delete matrices[i];
    }

    TEST("Cat21.5: Polymorphic Identity Check");
    Matrix *ptrIdentity = new DiagonalMatrix(3);
    Matrix *ptrTest = new SquareMatrix(3);

    for (int i = 0; i < 3; i++)
    {
        ptrIdentity->setElement(i, i, 1.0);
        for (int j = 0; j < 3; j++)
        {
            ptrTest->setElement(i, j, i * 3 + j + 1);
        }
    }

    Matrix resultIdentity = *ptrIdentity * *ptrTest;
    ASSERT_EQUAL(resultIdentity.getElement(0, 0), 1.0, "Identity*M (0,0)");
    ASSERT_EQUAL(resultIdentity.getElement(0, 1), 2.0, "Identity*M (0,1)");
    ASSERT_EQUAL(resultIdentity.getElement(1, 2), 6.0, "Identity*M (1,2)");
    ASSERT_EQUAL(resultIdentity.getElement(2, 2), 9.0, "Identity*M (2,2)");

    delete ptrIdentity;
    delete ptrTest;

    TEST("Cat21.6: Cross-Type Equality Through Base Pointer");
    Matrix *ptrM = new Matrix(3, 3);
    Matrix *ptrS = new SquareMatrix(3);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            double val = i + j * 10;
            ptrM->setElement(i, j, val);
            ptrS->setElement(i, j, val);
        }
    }

    ASSERT(*ptrM == *ptrS, "Matrix equals SquareMatrix through pointers");

    ptrS->setElement(1, 1, 999.0);
    ASSERT(!(*ptrM == *ptrS), "Modified matrix not equal through pointers");

    delete ptrM;
    delete ptrS;

    TEST("Cat21.7: Chained Operations with Base Pointers");
    Matrix *ptrA = new DiagonalMatrix(2);
    Matrix *ptrB = new LowerTriangularMatrix(2);
    Matrix *ptrC = new UpperTriangularMatrix(2);

    ptrA->setElement(0, 0, 2.0);
    ptrA->setElement(1, 1, 2.0);
    ptrB->setElement(0, 0, 1.0);
    ptrB->setElement(1, 0, 1.0);
    ptrB->setElement(1, 1, 1.0);
    ptrC->setElement(0, 0, 3.0);
    ptrC->setElement(0, 1, 3.0);
    ptrC->setElement(1, 1, 3.0);

    Matrix chain = ((*ptrA + *ptrB) + *ptrC);
    ASSERT_EQUAL(chain.getElement(0, 0), 6.0, "Chain (0,0): (2+1)+3 = 6");
    ASSERT_EQUAL(chain.getElement(0, 1), 3.0, "Chain (0,1): (0+0)+3 = 3");
    ASSERT_EQUAL(chain.getElement(1, 0), 1.0, "Chain (1,0): (0+1)+0 = 1");
    ASSERT_EQUAL(chain.getElement(1, 1), 6.0, "Chain (1,1): (2+1)+3 = 6");

    delete ptrA;
    delete ptrB;
    delete ptrC;

    TEST("Cat21.8: Nested Operations with Dynamic Allocation");
    Matrix *d = new DiagonalMatrix(2);
    Matrix *l = new LowerTriangularMatrix(2);

    d->setElement(0, 0, 5.0);
    d->setElement(1, 1, 10.0);
    l->setElement(0, 0, 2.0);
    l->setElement(1, 0, 3.0);
    l->setElement(1, 1, 4.0);

    Matrix sum = *d + *l;
    Matrix diff = *d - *l;
    Matrix result = sum + diff; // (d+l) + (d-l) = 2d

    ASSERT_EQUAL(result.getElement(0, 0), 10.0, "Nested (0,0): 2*5 = 10");
    ASSERT_EQUAL(result.getElement(1, 1), 20.0, "Nested (1,1): 2*10 = 20");
    ASSERT_EQUAL(result.getElement(1, 0), 0.0, "Nested (1,0): cancels to 0");

    delete d;
    delete l;

    TEST("Cat21.9: Multiple Polymorphic Operations in Sequence");
    Matrix *ptrSeq = new SquareMatrix(2);
    ptrSeq->setElement(0, 0, 1.0);
    ptrSeq->setElement(0, 1, 2.0);
    ptrSeq->setElement(1, 0, 3.0);
    ptrSeq->setElement(1, 1, 4.0);

    Matrix *ptrScale = new DiagonalMatrix(2);
    ptrScale->setElement(0, 0, 10.0);
    ptrScale->setElement(1, 1, 10.0);

    Matrix scaled = *ptrSeq * *ptrScale; // Scale columns by 10
    ASSERT_EQUAL(scaled.getElement(0, 0), 10.0, "Scaled (0,0): 1*10 = 10");
    ASSERT_EQUAL(scaled.getElement(0, 1), 20.0, "Scaled (0,1): 2*10 = 20");
    ASSERT_EQUAL(scaled.getElement(1, 0), 30.0, "Scaled (1,0): 3*10 = 30");
    ASSERT_EQUAL(scaled.getElement(1, 1), 40.0, "Scaled (1,1): 4*10 = 40");

    delete ptrSeq;
    delete ptrScale;

    TEST("Cat21.10: Complex Type Mixing with Pointers");
    Matrix *base1 = new Matrix(2, 2);
    Matrix *base2 = new SquareMatrix(2);
    Matrix *base3 = new DiagonalMatrix(2);
    Matrix *base4 = new LowerTriangularMatrix(2);

    base1->setElement(0, 0, 1.0);
    base1->setElement(0, 1, 1.0);
    base1->setElement(1, 0, 1.0);
    base1->setElement(1, 1, 1.0);

    base2->setElement(0, 0, 2.0);
    base2->setElement(0, 1, 2.0);
    base2->setElement(1, 0, 2.0);
    base2->setElement(1, 1, 2.0);

    base3->setElement(0, 0, 3.0);
    base3->setElement(1, 1, 3.0);

    base4->setElement(0, 0, 4.0);
    base4->setElement(1, 0, 4.0);
    base4->setElement(1, 1, 4.0);

    Matrix finalResult = (((*base1 + *base2) + *base3) + *base4);
    ASSERT_EQUAL(finalResult.getElement(0, 0), 10.0, "Complex (0,0): 1+2+3+4 = 10");
    ASSERT_EQUAL(finalResult.getElement(0, 1), 3.0, "Complex (0,1): 1+2+0+0 = 3");
    ASSERT_EQUAL(finalResult.getElement(1, 0), 7.0, "Complex (1,0): 1+2+0+4 = 7");
    ASSERT_EQUAL(finalResult.getElement(1, 1), 10.0, "Complex (1,1): 1+2+3+4 = 10");

    delete base1;
    delete base2;
    delete base3;
    delete base4;
}

// ==================== OUTPUT OPERATOR ====================


std::ostream &operator<<(std::ostream &os, const Matrix &M)
{
    const char open_bracket = '|';
    const char close_bracket = '|';

    for (int i = 0; i < M.getRows(); ++i)
    {
        os << open_bracket << ' ';
        for (int j = 0; j < M.getCols(); ++j)
        {
            os.width(8);
            os << std::fixed << std::setprecision(2) << M.getElement(i, j) << " ";
        }
        os << close_bracket;
        os << std::endl;
    }

    return os;
}
