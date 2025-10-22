# MakeUp Lab

- [MakeUp Lab](#makeup-lab)
  - [Questions](#questions)
    - [Rectangle](#rectangle)
    - [Quadratic Formula](#quadratic-formula)
    - [Student class](#student-class)
  - [Automated Testing](#automated-testing)

> [!IMPORTANT]
>
> If you want to test your code locally, you can create a `main.cpp` file in the `src` directory and import your files there. Make sure to include the necessary headers and use the appropriate namespaces if needed.

## Questions

### Rectangle

Implement a `class Rectangle`. Provide a constructor to construct a rectangle with a given width and height, member functions `get_length`, `get_width`, `get_perimeter` and `get_area` that compute/returns the length, width, perimeter and area respectively, and a member function `void resize(double factor)` that resizes the rectangle by multiplying the width and height by the given factor.

### Quadratic Formula

Write a program that prints all real solutions to the quadratic equation $ax^2 + bx + c = 0$. Read in $a$, $b$, $c$ and use the quadratic formula. You may assume that $a \neq 0$. If the discriminant $b^2 – 4ac$ is negative, display a message stating that there are no real solutions.

Implement a class `QuadraticEquation` whose constructor receives the coefficients `a`, `b`, `c` of the quadratic equation. Supply member functions `get_solution1` and `get_solution2` that get the solutions, using the quadratic formula, or `0` if no solution exists. The `get_solution1` function should return the smaller of the two solutions. Supply a function `bool has_solutions() const`
that returns `false` if the discriminant is negative.

### Student class

Implement a class `Student`. For the purpose of this exercise, a student has a name and a total quiz score. Supply an appropriate constructor and functions `get_name()`, `add_quiz(int score)`, `get_total_score()`, and `get_average_score()`. To compute the latter, you also need to store the number of quizzes that the student took.

## Automated Testing

We have used Gtest to create automated tests for your implementations. You can find the test files in the [`tests`](../tests) directory. To run the tests, you can use the following command from the root directory of the project:

```bash
make TEST=RECTANGLE          # for Rectangle tests
make TEST=QUADRATIC_EQUATION # for QuadraticEquation tests
make TEST=STUDENTS           # for Student tests
make                         # to run all tests
```

This will compile  the test files and run the tests, displaying the results in the terminal. Make sure to fix any issues that arise during testing to ensure your implementations are correct.
