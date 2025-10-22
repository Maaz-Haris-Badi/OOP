#include <iostream>

int main()
{
    std::cout << "Welcome to a simple Calculator" << std::endl;
    int num1, num2;
    char op;

    do
    {
        std::cout << "Enter first number: ";
        std::cin >> num1;
        std::cout << "Enter the second number: ";
        std::cin >> num2;
    } while ((num1 < 0) or (num2 < 0));
    std::cout << "Enter the operator (+, -, *, /): ";
    std::cin >> op;

    switch (op)
    {
    case '+':
        std::cout << "Result: " << (num1 + num2) << std::endl;
        break;
    case '-':
        std::cout << "Result: " << (num1 - num2) << std::endl;
        break;
    case '*':
        std::cout << "Result: " << (num1 * num2) << std::endl;
        break;
    case '/':
        if (num2 != 0)
            std::cout << "Result: " << (static_cast<float>(num1) / num2)
                      << std::endl;
        else
            std::cout << "Error: Division by zero is not allowed."
                      << std::endl;
        break;
    default:
        std::cout << "Error: Invalid operator." << std::endl;
        break;
    }
    return 0;
}