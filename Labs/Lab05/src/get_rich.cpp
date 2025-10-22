#ifndef GET_RICH
#define GET_RICH

#include <iostream>

class TollBooth {
private:

    unsigned int total_cars;
    unsigned int total_amount;

public:

    TollBooth() : total_cars(0), total_amount(0) {}

    void paying_cars() {
        total_cars++;
        total_amount += 50;
    }

    void nopay_cars() { total_cars++; }

    void display() const {
        std::cout << "Total cars passed: " << total_cars << std::endl;
        std::cout << "Total toll collected: Rs " << total_amount << std::endl;
    }
};

int main() {
    TollBooth booth=TollBooth();
    char      choice;

    do {
        std::cout << "Enter 'p' for paying car, 'n' for non-paying car, 'q' to "
                     "quit: ";
        std::cin >> choice;

        if (choice == 'p') {
            booth.paying_cars();
        } else if (choice == 'n') {
            booth.nopay_cars();
        } else if (choice != 'q') {
            std::cout << "Invalid input. Please try again." << std::endl;
        }
    } while (choice != 'q');

    booth.display();
    return 0;
}

#endif  // GET_RICH
