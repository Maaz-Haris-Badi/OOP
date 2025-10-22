#include <cmath>
#include <iostream>

int main()
{
    int size_of_array;
    int sum = 0;
    // We will initialize min and max *after* getting the first number
    int max, min;

    float average, stnd = 0;

    std::cout << "Enter the size of array: ";
    std::cin >> size_of_array;

    // --- CHANGE 1: Use new[] to create the array on the heap ---
    // array_num is now a pointer (int*) to the first element
    int *array_num = new int[size_of_array];

    // --- This line still works perfectly ---
    int *poi = array_num;

    // --- Fill the array ---
    for (int i = 0; i < size_of_array; i++)
    {
        std::cout << "Enter the number " << i + 1 << ": ";
        std::cin >> array_num[i]; // Usage is identical
    }

    // --- Initialize min and max to the first element (Robust Fix) ---
    max = array_num[0];
    min = array_num[0];

    // --- Process the array ---
    for (int j = 0; j < size_of_array; j++)
    {
        // Using array_num[j] is cleaner, but *(poi + j) also works
        sum = sum + array_num[j];

        if (array_num[j] > max)
        {
            max = array_num[j];
        }
        if (array_num[j] < min)
        {
            min = array_num[j];
        }
    }

    average = static_cast<float>(sum) / size_of_array;

    for (int k = 0; k < size_of_array; k++)
    {
        stnd += (array_num[k] - average) * (array_num[k] - average);
    }

    stnd = sqrt(static_cast<float>(stnd) / size_of_array);

    std::cout << "Maximum: " << max << std::endl;
    std::cout << "Minimum: " << min << std::endl;
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Average: " << average << std::endl;
    std::cout << "Standard Deviation: " << stnd << std::endl;

    // --- CHANGE 2: Free the memory you allocated with new[] ---
    // This prevents a memory leak.
    delete[] array_num;

    // --- CHANGE 3: Set pointers to null after deleting (Good Practice) ---
    array_num = nullptr;
    poi = nullptr;

    return 0;
}