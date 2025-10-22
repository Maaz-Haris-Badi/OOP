#include <iostream>

void print_vectors(int array[], int size)
{
    std::cout << "Array elements are: ";
    for (int i = 0; i < size; i++)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

void populate_array(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << "Enter element " << (i + 1) << ": ";
        std::cin >> array[i];
    }
}

void add_vectors(int array1[], int array2[], int result[], int size)
{
    for (int i = 0; i < size; i++)
    {
        result[i] = array1[i] + array2[i];
    }
}

void subtract_vectors(int array1[], int array2[], int result[], int size)
{
    for (int i = 0; i < size; i++)
    {
        result[i] = array1[i] - array2[i];
    }
}

void compare_vectors(int array1[], int array2[], int size)
{
    bool are_equal = true;
    for (int i = 0; i < size; i++)
    {
        if (array1[i] != array2[i])
        {
            are_equal = false;
            break;
        }
    }
    if (are_equal)
    {
        std::cout << "The two arrays are equal." << std::endl;
    }
    else
    {
        std::cout << "The two arrays are not equal." << std::endl;
    }
}

int main()
{
    int size;
    char oper;
    std::cout << "Enter the size of the array: ";
    std::cin >> size;

    int array_1[size], array_2[size], result[size];
    std::cout << "Populate first array:" << std::endl;
    populate_array(array_1, size);
    std::cout << "Populate second array:" << std::endl;
    populate_array(array_2, size);

    std::cout << "Enter the operation (+, -, =): ";
    std::cin >> oper;

    switch (oper)
    {
    case '+':
        add_vectors(array_1, array_2, result, size);
        print_vectors(result, size);
        break;
    case '-':
        subtract_vectors(array_1, array_2, result, size);
        print_vectors(result, size);
        break;
    case '=':
        compare_vectors(array_1, array_2, size);
        break;
    default:
        std::cout << "Invalid operation." << std::endl;
        break;
    }

    return 0;
}
