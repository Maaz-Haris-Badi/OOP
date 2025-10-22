#ifndef TEST_Q2
#define TEST_Q2

#include <gtest/gtest.h>

#include <cmath>

class QuadraticEquation {
public:

    // Constructor
    QuadraticEquation(const double, const double, const double);

    // Check if real solutions exist
    bool has_solutions() const;

    // Get the smaller root
    double get_solution1() const;

    // Get the larger root
    double get_solution2() const;

private:

    double a, b, c;
};

class QuadraticEquationTests
    : public ::testing::TestWithParam<std::tuple<double, double, double>> {
protected:

    QuadraticEquation* quad_eq;

    void SetUp() override {
        const auto [a, b, c] = GetParam();
        quad_eq              = new QuadraticEquation(a, b, c);
    }

    void TearDown() override { delete quad_eq; }
};

constexpr double EPS        = 1e-7;
const auto       test_cases = ::testing::Values(
    std::make_tuple(1.0, -3.0, 2.0),  // Two distinct real roots: x1=1, x2=2
    std::make_tuple(1.0, -2.0, 1.0),  // One real root (double root): x1=x2=1
    std::make_tuple(1.0, 2.0, 5.0),  // No real roots
    std::make_tuple(1.0, 0.0, -4.0),  // Two distinct real roots: x1=-2, x2=2
    std::make_tuple(1.0, 4.0, 4.0),  // One real root (double root): x1=x2=-2
    std::make_tuple(1.0, 0.0, 4.0),  // No real roots
    std::make_tuple(2.0, -7.0, 3.0),  // Two distinct real roots: x1=1.5, x2=1
    std::make_tuple(1.0, -1e8, 1.0),  // Two distinct real roots: x1~0, x2~1e8
    std::make_tuple(1.0, 1e8, 1.0),  // Two distinct real roots: x1~-1e8, x2~0
    std::make_tuple(1.0, 1e-8, 1.0)  // No real roots
);

INSTANTIATE_TEST_SUITE_P(, QuadraticEquationTests, test_cases);

TEST_P(QuadraticEquationTests, TestSolutions) {
    const auto [a, b, c] = GetParam();
    const double D       = b * b - 4 * a * c;

    if (D > EPS) {
        EXPECT_TRUE(quad_eq->has_solutions());
        double x1 = (-b - sqrt(D)) / (2 * a);
        double x2 = (-b + sqrt(D)) / (2 * a);
        if (x1 > x2) {
            std::swap(x1, x2);
        }
        EXPECT_NEAR(quad_eq->get_solution1(), x1, EPS);
        EXPECT_NEAR(quad_eq->get_solution2(), x2, EPS);
    } else if (std::abs(D) <= EPS) {
        EXPECT_TRUE(quad_eq->has_solutions());
        const double x = -b / (2 * a);
        EXPECT_NEAR(quad_eq->get_solution1(), x, EPS);
        EXPECT_NEAR(quad_eq->get_solution2(), x, EPS);
    } else {
        EXPECT_FALSE(quad_eq->has_solutions());
    }
}

#endif