#include <iostream>
#include <string>

int hole_one(std::string str)
{
    if (str[0] == 'B')
    {
        return 2;
    }
    else if (str[0] == 'A' || str[0] == 'D' || str[0] == 'O' || str[0] == 'P' || str[0] == 'Q' || str[0] == 'R')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int hole_one_int(int num)
{
    if (num == 8)
    {
        return 2;
    }
    else if (num == 0 || num == 4 || num == 6 || num == 9)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int hole_int(int num)
{
    if (num == 0)
    {
        return 0;
    }
    return hole_one_int(num % 10) + hole_int(num / 10);
}

int hole(std::string str)
{
    if (str.length() == 0)
    {
        return 0;
    }
    return hole_one(str.substr(0, 1)) + hole(str.substr(1, str.length() - 1));
}
int main()
{
    std::string str;
    int num, option;
    std::cout << "Enter 1 for integer input and 2 for string input: ";
    std::cin >> option;
    std::cin.clear();
    if (option == 1)
    {
        std::cout << "Enter an integer: ";
        std::cin >> num;
        std::cout << hole_int(num) << std::endl;
        return 0;
    }
    else if (option == 2)
    {
        std::cout << "Enter a string: ";
        std::cin >> str;
        std::cout << hole(str) << std::endl;
        return 1;
    }

    std::cout << hole(str) << std::endl;
    return 0;
}