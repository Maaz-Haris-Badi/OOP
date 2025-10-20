#include <iostream>

int main(){
    int num1;
    int num2;
    int plus;
    int minus;
    int multiply;
    float divide;
    std::cout << "Welcome to the Mini Calculator!" << "\n";
    std::cout << "Enter the first number: ";
    std::cin >> num1;

    std::cout << "Enter the second number: ";
    std::cin >> num2;

    plus = num1 + num2;
    minus = num1 - num2;
    multiply = num1 * num2;
    divide = static_cast<float>(num1) / num2;

    std::cout << "Results:" << "\n";
    std::cout << "Addition: " << plus << "\n";
    std::cout << "Subtraction: " << minus << "\n";
    std::cout << "Multiplication: " << multiply << "\n";
    std::cout << "Division: " << divide << "\n";

    return 0;
}