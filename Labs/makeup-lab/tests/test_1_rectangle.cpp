#ifndef TEST_Q1
#define TEST_Q1

#include <gtest/gtest.h>

class Rectangle {
public:

    // Constructor
    Rectangle(const double, const double);

    // Getters
    double get_length() const;
    double get_width() const;

    // Geometry
    double get_perimeter() const;
    double get_area() const;

    // Resize by factor
    void resize(const double);

private:

    double width, height;
};

class RectangleTests
    : public ::testing::TestWithParam<std::tuple<double, double>> {
protected:

    Rectangle* rect;

    void SetUp() override {
        const auto [width, height] = GetParam();
        rect                       = new Rectangle(width, height);
    }

    void TearDown() override { delete rect; }
};

const auto width_and_height =
    ::testing::Values(std::make_tuple(3.0, 4.0), std::make_tuple(5.5, 2.2),
                      std::make_tuple(10.0, 10.0), std::make_tuple(7.1, 3.3),
                      std::make_tuple(6.6, 4.4), std::make_tuple(1.1, 9.9),
                      std::make_tuple(8.8, 2.2), std::make_tuple(4.4, 5.5),
                      std::make_tuple(12.0, 3.0), std::make_tuple(9.9, 1.1));

INSTANTIATE_TEST_CASE_P(, RectangleTests, width_and_height);

TEST_P(RectangleTests, TEST_GETTERS) {
    const auto [width, height] = GetParam();

    EXPECT_DOUBLE_EQ(rect->get_width(), width);
    EXPECT_DOUBLE_EQ(rect->get_length(), height);
}

TEST_P(RectangleTests, TEST_GEOMETRY) {
    const auto [width, height] = GetParam();

    EXPECT_DOUBLE_EQ(rect->get_perimeter(), 2 * (width + height));
    EXPECT_DOUBLE_EQ(rect->get_area(), width * height);
}

TEST_P(RectangleTests, TEST_RESIZE) {
    const auto [width, height] = GetParam();
    const double factor        = width / height;

    rect->resize(factor);

    EXPECT_DOUBLE_EQ(rect->get_width(), width * factor);
    EXPECT_DOUBLE_EQ(rect->get_length(), height * factor);
    EXPECT_DOUBLE_EQ(rect->get_perimeter(), 2 * (width + height) * factor);
    EXPECT_DOUBLE_EQ(rect->get_area(), width * height * factor * factor);
}

#endif