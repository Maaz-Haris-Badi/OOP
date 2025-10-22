#include <iostream>

void average(int arr[], int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += arr[i];
    }
    std::cout << "Average Price: " << (static_cast<double>(sum) / size) << "PKR"
              << std::endl;
}

void maximum(int arr[], int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] >= sum)
        {
            sum = arr[i];
        }
    }
    std::cout << "Maximum Price: " << sum << "PKR" << std::endl;
}

void minimum(int arr[], int size)
{
    int sum = 100000;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] < sum)
        {
            sum = arr[i];
        }
    }

    std::cout << "Minimum Price: " << sum << "PKR" << std::endl;
}

void Prices(int arr1[], int arr2[], int arr3[], int index)
{
    int Array[3];
    Array[0] = arr1[index];
    Array[1] = arr2[index];
    Array[2] = arr3[index];
    std::cout << std::endl
              << "Prices: " << Array[0] << ", " << Array[1] << ", " << Array[2]
              << std::endl;
    average(Array, 3);
    maximum(Array, 3);
    minimum(Array, 3);
}

int main()
{
    int North[] = {500, 900, 1600, 300, 600, 1100, 200, 450, 800};
    int Central[] = {550, 950, 1700, 320, 620, 1150, 220, 470, 850};
    int South[] = {600, 1000, 1800, 350, 650, 1200, 250, 500, 900};

    char Service;
    int Cargo, index;

    std::cout << "Service: ";
    std::cin >> Service;
    std::cout << "Cargo: ";
    std::cin >> Cargo;

    switch (Service)
    {
    case 'U':
        switch (Cargo)
        {
        case 1:
            std::cout << "Category: Urgent Service, Documents"
                      << std::endl;
            index = (0 * 3) + 0;
            break;
        case 2:
            std::cout << "Category: Urgent Service, Parcel < 5kg";
            index = (0 * 3) + 1;
            break;
        case 3:
            std::cout << "Category: Urgent Service, Parcel >= 5kg";
            index = (0 * 3) + 2;
            break;
        default:
            std::cout << "Invalid Cargo Number";
            break;
        }
        break;
    case 'N':
        switch (Cargo)
        {
        case 1:
            std::cout << "Category: Normal Service, Documents"
                      << std::endl;
            index = (1 * 3) + 0;
            break;
        case 2:
            std::cout << "Category: Normal Service, Parcel < 5kg";
            index = (1 * 3) + 1;
            break;
        case 3:
            std::cout << "Category: Normal Service, Parcel >= 5kg";
            index = (1 * 3) + 2;
            break;
        default:
            std::cout << "Invalid Cargo Number";
            break;
        }
        break;
    case 'E':
        switch (Cargo)
        {
        case 1:
            std::cout << "Category: Economy Service, Documents"
                      << std::endl;
            index = (2 * 3) + 0;
            break;
        case 2:
            std::cout << "Category: Economy Service, Parcel < 5kg";
            index = (2 * 3) + 1;
            break;
        case 3:
            std::cout << "Category: Economy Service, Parcel >= 5kg";
            index = (2 * 3) + 2;
            break;
        default:
            std::cout << "Invalid Cargo Number";
            break;
        }
        break;
    default:
        std::cout << "Invalid Service Type";
        break;
    }
    Prices(North, Central, South, index);
    return 0;
}