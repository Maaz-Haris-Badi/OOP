#include <iostream>
#include <string>

int main() {
    std::cout << "Character Counter Initialized." << std::endl;
    std::string input;
    char        letter;
    int         count = 0;
    std::cout << "Enter a string: ";
    std::getline(std::cin, input);
    std::cout << "Enter a character to count: ";
    std::cin >> letter;
    int n = input.length();
    for (int i = 0; i < n   ; i++) {
        if (input[i] == letter) {
            count++;
        }
    }
    std::cout << "The character '" << letter << "' appears " << count
              << " times." << std::endl;
    return 0;
}