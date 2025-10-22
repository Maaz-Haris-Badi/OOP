cmake_minimum_required(VERSION 3.0)

set(TestRectangle RECTANGLE)
set(TestQuadraticEquation QUADRATIC_EQUATION)
set(TestStudents STUDENTS)

set(CMAKE_BUILD_TYPE Release)

add_executable(${TestRectangle} test_1_rectangle.cpp)
add_executable(${TestQuadraticEquation} test_2_quadratic_equation.cpp)
add_executable(${TestStudents} test_3_students.cpp)

target_link_libraries(
    ${TestRectangle} PUBLIC
    gtest
    gtest_main
    MakeUpLab
)

target_link_libraries(
    ${TestQuadraticEquation} PUBLIC
    gtest
    gtest_main
    MakeUpLab
)

target_link_libraries(
    ${TestStudents} PUBLIC
    gtest
    gtest_main
    MakeUpLab
)

enable_testing()

add_test(
    NAME ${TestRectangle}
    COMMAND ${TestRectangle}
)

add_test(
    NAME ${TestQuadraticEquation}
    COMMAND ${TestQuadraticEquation}
)

add_test(
    NAME ${TestStudents}
    COMMAND ${TestStudents}
)