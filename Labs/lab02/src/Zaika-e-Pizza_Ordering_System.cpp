#include <iostream>

int main()
{
    int day, amount;
    char flavor_1, flavor_2, size_1, size_2;
    std::cout << "Enter a day number (1-7): ";
    std::cin >> day;

    std::cout << "Enter first flavour pizza (c/b/v/p/a): ";
    std::cin >> flavor_1;
    std::cout << "Enter first size pizza (s/m/l): ";
    std::cin >> size_1;
    std::cout << "Enter second flavour pizza (c/b/v/p/a): ";
    std::cin >> flavor_2;
    std::cout << "Enter second size pizza (s/m/l): ";
    std::cin >> size_2;

    std::cout << "You Ordered: " << std::endl;
    switch (flavor_1)
    {
    case 'c':
        switch (size_1)
        {
        case 's':
            amount += 800;
            std::cout << "-- Small Chicken Pizza: 800 PKR" << std::endl;
            break;
        case 'm':
            amount += 1000;
            std::cout << "-- Medium Chicken Pizza: 1000 PKR"
                      << std::endl;
            break;
        case 'l':
            amount += 1200;
            std::cout << "-- Large Chicken Pizza: 1200 PKR"
                      << std::endl;
            break;
        default:
            std::cout << "Error: Invalid size." << std::endl;
            break;
        }
        break;
    case 'b':
        switch (size_1)
        {
        case 's':
            amount += 900;
            std::cout << "-- Small Beef Pizza: 900 PKR" << std::endl;
            break;
        case 'm':
            amount += 1100;
            std::cout << "-- Medium Beef Pizza: 1100 PKR" << std::endl;
            break;
        case 'l':
            amount += 1300;
            std::cout << "-- Large Beef Pizza: 1300 PKR" << std::endl;
            break;
        default:
            std::cout << "Error: Invalid size." << std::endl;
            break;
        }
        break;
    case 'v':
        switch (size_1)
        {
        case 's':
            amount += 700;
            std::cout << "-- Small Vegetarian Pizza: 700 PKR"
                      << std::endl;
            break;
        case 'm':
            amount += 900;
            std::cout << "-- Medium Vegetarian Pizza: 900 PKR"
                      << std::endl;
            break;
        case 'l':
            amount += 1100;
            std::cout << "-- Large Vegetarian Pizza: 1100 PKR"
                      << std::endl;
            break;
        default:
            std::cout << "Error: Invalid size." << std::endl;
            break;
        }
        break;
    case 'p':
        switch (size_1)
        {
        case 's':
            amount += 600;
            std::cout << "-- Small Plain Pizza: 600 PKR" << std::endl;
            break;
        case 'm':
            amount += 800;
            std::cout << "-- Medium Plain Pizza: 800 PKR" << std::endl;
            break;
        case 'l':
            amount += 1000;
            std::cout << "-- Large Plain Pizza: 1000 PKR" << std::endl;
            break;
        default:
            std::cout << "Error: Invalid size." << std::endl;
            break;
        }
        break;
    case 'a':
        switch (size_1)
        {
        case 's':
            amount += 1000;
            std::cout << "-- Small Assorted Pizza: 1000 PKR"
                      << std::endl;
            break;
        case 'm':
            amount += 1200;
            std::cout << "-- Medium Assorted Pizza: 1200 PKR"
                      << std::endl;
            break;
        case 'l':
            amount += 1400;
            std::cout << "-- Large Assorted Pizza: 1400 PKR"
                      << std::endl;
            break;
        default:
            std::cout << "Error: Invalid size." << std::endl;
            break;
        }
        break;
    default:
        std::cout << "Error: Invalid flavour." << std::endl;
        break;
    }
    switch (flavor_2)
    {
    case 'c':
        switch (size_2)
        {
        case 's':
            amount += 800;
            std::cout << "-- Small Chicken Pizza: 800 PKR" << std::endl;
            break;
        case 'm':
            amount += 1000;
            std::cout << "-- Medium Chicken Pizza: 1000 PKR"
                      << std::endl;
            break;
        case 'l':
            amount += 1200;
            std::cout << "-- Large Chicken Pizza: 1200 PKR"
                      << std::endl;
            break;
        default:
            std::cout << "Error: Invalid size." << std::endl;
            break;
        }
        break;
    case 'b':
        switch (size_2)
        {
        case 's':
            amount += 900;
            std::cout << "-- Small Beef Pizza: 900 PKR" << std::endl;
            break;
        case 'm':
            amount += 1100;
            std::cout << "-- Medium Beef Pizza: 1100 PKR" << std::endl;
            break;
        case 'l':
            amount += 1300;
            std::cout << "-- Large Beef Pizza: 1300 PKR" << std::endl;
            break;
        default:
            std::cout << "Error: Invalid size." << std::endl;
            break;
        }
        break;
    case 'v':
        switch (size_2)
        {
        case 's':
            amount += 700;
            std::cout << "-- Small Vegetarian Pizza: 700 PKR"
                      << std::endl;
            break;
        case 'm':
            amount += 900;
            std::cout << "-- Medium Vegetarian Pizza: 900 PKR"
                      << std::endl;
            break;
        case 'l':
            amount += 1100;
            std::cout << "-- Large Vegetarian Pizza: 1100 PKR"
                      << std::endl;
            break;
        default:
            std::cout << "Error: Invalid size." << std::endl;
            break;
        }
        break;
    case 'p':
        switch (size_2)
        {
        case 's':
            amount += 600;
            std::cout << "-- Small Plain Pizza: 600 PKR" << std::endl;
            break;
        case 'm':
            amount += 800;
            std::cout << "-- Medium Plain Pizza: 800 PKR" << std::endl;
            break;
        case 'l':
            amount += 1000;
            std::cout << "-- Large Plain Pizza: 1000 PKR" << std::endl;
            break;
        default:
            std::cout << "Error: Invalid size." << std::endl;
            break;
        }
        break;
    case 'a':
        switch (size_2)
        {
        case 's':
            amount += 1000;
            std::cout << "-- Small Assorted Pizza: 1000 PKR"
                      << std::endl;
            break;
        case 'm':
            amount += 1200;
            std::cout << "-- Medium Assorted Pizza: 1200 PKR"
                      << std::endl;
            break;
        case 'l':
            amount += 1400;
            std::cout << "-- Large Assorted Pizza: 1400 PKR"
                      << std::endl;
            break;
        default:
            std::cout << "Error: Invalid size." << std::endl;
            break;
        }
        break;
    default:
        std::cout << "Error: Invalid flavour." << std::endl;
        break;
    }

    switch (day)
    {
    case 1:
        std::cout << "Monday Deal Applied: Buy 1 Medium Chicken Pizza, get "
                     "1 Small Chicken Pizza free"
                  << std::endl;
        if (((flavor_1 == 'c' && size_1 == 'm') &&
             (flavor_2 == 'c' && size_2 == 's')) ||
            ((flavor_1 == 'c' && size_1 == 's') &&
             (flavor_2 == 'c' && size_2 == 'm')))
        {
            amount -= 800;
            std::cout << "Total Bill: " << amount << std::endl;
        }
        else
        {
            std::cout << "Total Bill: " << amount << std::endl;
        }
        break;
    case 2:
        std::cout << "Tuesday Deal Applied: Buy 1 Large Pizza (any "
                     "flavor), get 1 free (same "
                     "flavor and size)"
                  << std::endl;
        if (((flavor_1 == flavor_2) && (size_1 == 'l') &&
             (size_2 == 'l')))
        {
            amount /= 2;
            std::cout << "Total Bill: " << amount << std::endl;
        }
        else
        {
            std::cout << "Total Bill: " << amount << std::endl;
        }
        break;
    case 3:
        std::cout << "Wednesday Deal Applied: Buy 2 Small Pizzas (any "
                     "flavors), get 20% off"
                  << std::endl;
        if ((size_1 == 's') && (size_2 == 's'))
        {
            amount *= 0.80;
            std::cout << "Total Bill: " << amount << std::endl;
        }
        else
        {
            std::cout << "Total Bill: " << amount << std::endl;
        }
        break;
    case 4:
        std::cout << "Thursday Deal Applied: Buy 1 Beef Pizza of any size, "
                     "get 1 Small Plain Pizza free"
                  << std::endl;
        if (((flavor_1 == 'b') || (flavor_2 == 'b')) &&
            ((flavor_1 == 'p' && size_1 == 's') ||
             (flavor_2 == 'p' && size_2 == 's')))
        {
            amount -= 550;
            std::cout << "Total Bill: " << amount << std::endl;
        }
        else
        {
            std::cout << "Total Bill: " << amount << std::endl;
        }
        break;
    case 5:
        std::cout << "Friday Deal Applied: Buy 1 Large Assorted Pizza, get "
                     "1 Medium Vegetarian Pizza free"
                  << std::endl;
        if (((flavor_1 == 'a' && size_1 == 'l') &&
             (flavor_2 == 'v' && size_2 == 'm')) ||
            ((flavor_1 == 'v' && size_1 == 'm') &&
             (flavor_2 == 'a' && size_2 == 'l')))
        {
            amount -= 900;
            std::cout << "Total Bill: " << amount << std::endl;
        }
        else
        {
            std::cout << "Total Bill: " << amount << std::endl;
        }
        break;
    case 6:
        std::cout << "Saturday Deal Applied: No deal" << std::endl;
        std::cout << "Total Bill: " << amount << std::endl;
        break;
    case 7:
        std::cout << "Sunday Deal Applied: Buy 1 Medium Pizza (any "
                     "flavor), get 1 Small "
                     "Vegetarian Pizza free"
                  << std::endl;
        if (((size_1 == 'm') && (flavor_2 == 'v' && size_2 == 's')) ||
            ((size_2 == 'm') && (flavor_1 == 'v' && size_1 == 's')))
        {
            amount -= 700;
            std::cout << "Total Bill: " << amount << std::endl;
        }
        else
        {
            std::cout << "Total Bill: " << amount << std::endl;
        }
        break;
    default:
        std::cout << "Error: Invalid day." << std::endl;
        break;
    }
    return 0;
}
