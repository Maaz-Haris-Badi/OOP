#include "Complex.hpp"
#include <iostream>
#include <cassert>  // For assert()
#include <cmath>    // For std::abs, std::isnan, INFINITY, NAN
#include <limits>   // For numeric_limits

// --- Test Helper Functions ---

/**
 * @brief Utility function to check if two doubles are "close enough".
 * Floating-point math is not exact, so we should never use ==.
 */
bool areClose(double a, double b) {
    // std::abs(a - b) checks the difference.
    // std::numeric_limits<double>::epsilon() is a very small number.
    // We check if the difference is smaller than a small multiple of epsilon.
    return std::abs(a - b) < 1e-9; 
}

/**
 * @brief Utility function to check if two Complex numbers are "close enough".
 */
bool complexAreClose(const Complex& a, const Complex& b) {
    return areClose(a.getReal(), b.getReal()) && 
           areClose(a.getImag(), b.getImag());
}

// --- Test Suite ---

int main() {
    std::cout << "--- Complex Number Test Suite ---" << std::endl;

    // Test 1: Constructor and Getters
    std::cout << "\n--- Test 1: Constructor & Getters ---" << std::endl;
    Complex c1(5.5, -10.1);
    assert(c1.getReal() == 5.5);
    assert(c1.getImag() == -10.1);
    Complex c2(0, 0);
    assert(c2.getReal() == 0.0);
    assert(c2.getImag() == 0.0);
    std::cout << "Passed." << std::endl;

    // Test 2: Basic Arithmetic
    std::cout << "\n--- Test 2: Basic Arithmetic (+, -, *, /) ---" << std::endl;
    Complex a(2, 3);
    Complex b(4, 5);

    // Test Addition: (2+3i) + (4+5i) = 6 + 8i
    Complex sum = a + b;
    assert(complexAreClose(sum, Complex(6, 8)));

    // Test Subtraction: (2+3i) - (4+5i) = -2 - 2i
    Complex diff = a - b;
    assert(complexAreClose(diff, Complex(-2, -2)));

    // Test Multiplication: (2+3i) * (4+5i) = (8 - 15) + (10 + 12)i = -7 + 22i
    Complex prod = a * b;
    assert(complexAreClose(prod, Complex(-7, 22)));

    // Test Division: (-7+22i) / (4+5i) should give (2+3i) back
    Complex quot = prod / b;
    assert(complexAreClose(quot, a));
    std::cout << "Passed." << std::endl;


    // Test 3: Extreme - Operations with Zero (Identities)
    std::cout << "\n--- Test 3: Operations with Zero ---" << std::endl;
    Complex z(0, 0);
    Complex a2(123.4, -567.8);

    assert(complexAreClose(a2 + z, a2)); // Additive identity
    assert(complexAreClose(a2 - z, a2));
    assert(complexAreClose(z - a2, Complex(-123.4, 567.8)));
    assert(complexAreClose(a2 * z, z)); // Multiplication by zero
    assert(complexAreClose(z * a2, z));
    assert(complexAreClose(z / a2, z)); // Zero divided by non-zero
    std::cout << "Passed." << std::endl;


    // Test 4: Extreme - Special Values (Identities)
    std::cout << "\n--- Test 4: Special Values (i*i = -1) ---" << std::endl;
    Complex one(1, 0);     // Multiplicative identity
    Complex i(0, 1);       // Imaginary unit
    
    assert(complexAreClose(a * one, a)); // a * 1 = a
    
    Complex i_squared = i * i;
    // (0+1i) * (0+1i) = (0*0 - 1*1) + (0*1 + 1*0)i = -1 + 0i
    assert(complexAreClose(i_squared, Complex(-1, 0)));
    
    // Test pure imaginary multiplication
    Complex j(0, 5); // 5i
    Complex k(0, 2); // 2i
    // (5i) * (2i) = 10 * (i*i) = -10
    assert(complexAreClose(j * k, Complex(-10, 0)));
    std::cout << "Passed." << std::endl;


    // Test 5: Extreme - Division by Zero (CRITICAL)
    std::cout << "\n--- Test 5: Division by Zero ---" << std::endl;
    std::cout << "Testing (5+5i) / (0+0i). Expecting (nan, nan)." << std::endl;
    
    Complex numerator(5, 5);
    Complex zero(0, 0);
    Complex div_by_zero = numerator / zero;
    
    // Your code does not check for a zero denominator.
    // This will result in 0/0, which in floating-point math is "NaN".
    // This test confirms that behavior.
    assert(std::isnan(div_by_zero.getReal()));
    assert(std::isnan(div_by_zero.getImag()));
    std::cout << "Passed (produced NaN as expected)." << std::endl;


    // Test 6: Extreme - Floating Point Limits (inf, nan)
    std::cout << "\n--- Test 6: Floating Point Limits (inf, nan) ---" << std::endl;
    double inf = INFINITY;
    double nan = NAN;

    Complex c_inf(inf, 10);
    Complex c_nan(nan, 10);
    Complex c_reg(2, 3);
    
    // inf + 2 = inf
    Complex res_inf = c_inf + c_reg;
    assert(std::isinf(res_inf.getReal()));

    // nan * 2 = nan
    Complex res_nan = c_nan * c_reg;
    assert(std::isnan(res_nan.getReal()));

    // (2+3i) / (inf+10i) = 0
    // As the denominator -> inf, the fraction -> 0
    Complex res_div_inf = c_reg / c_inf;
    assert(complexAreClose(res_div_inf, Complex(0, 0)));
    std::cout << "Passed." << std::endl;


    // Test 7: Chained Operations
    std::cout << "\n--- Test 7: Chained Operations ---" << std::endl;
    // Let's test: (a + b) * c - a / b
    // a = (1,1), b = (2,2), c = (3,3)
    Complex c_a(1, 1);
    Complex c_b(2, 2);
    Complex c_c(3, 3);

    // a + b = (3, 3)
    // (a + b) * c = (3,3) * (3,3) = (9 - 9) + (9 + 9)i = (0, 18)
    // a / b = (1,1) / (2,2) = ((2+2)/8) + ((2-2)/8)i = (4/8) + 0i = (0.5, 0)
    // (0, 18) - (0.5, 0) = (-0.5, 18)
    Complex chain_res = (c_a + c_b) * c_c - (c_a / c_b);
    assert(complexAreClose(chain_res, Complex(-0.5, 18)));
    std::cout << "Passed." << std::endl;


    std::cout << "\n--- All Extreme Tests Passed Successfully! ---" << std::endl;
    return 0;
}