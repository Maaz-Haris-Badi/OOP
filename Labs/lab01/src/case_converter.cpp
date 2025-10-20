#include <iostream>

int main (){
    char letter;
    int con;


    std::cout << "Welcome to case converter";
    std::cout << "Enter a lowercase letter: ";
    std::cin >> letter;

    con = static_cast<int>(letter) - 32;

    std::cout << "The uppercase letter is: " << static_cast<char>(con) << std::endl;
    return 0;
}