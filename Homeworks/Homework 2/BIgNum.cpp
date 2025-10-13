#include "BigNum.h"

#include <cctype>
#include <iostream>

//* Constructor and Destructor Functions

//! Function to set the digits to "0" and isNegative to false
BigNum::BigNum() {
    this->digits     = "0";
    this->isNegative = false;
}

//! Function to copy the given BigNum
BigNum::BigNum(const BigNum &bigNum) {
    this->digits     = bigNum.digits;
    this->isNegative = bigNum.isNegative;
}

//! Function to copy the given Big Num to a new BigNum
BigNum::BigNum(const std::string &bigStr) {
    //? Checks whether the string is empty or not and assigns the correct values
    if (bigStr.empty()) {
        this->digits     = "0";
        this->isNegative = false;
        return;
    }

    std::string temp_string;
    //? Checks for the negative sign and assigns the correct values
    if (bigStr.front() == '-') {
        temp_string      = bigStr.substr(1);
        this->isNegative = true;
    } else {
        temp_string      = bigStr;
        this->isNegative = false;
    }

    //? Validates that all the values in the string are digits and not any
    //? alphabet
    for (char c : temp_string) {
        if (!isdigit(c)) {
            this->digits     = "0";
            this->isNegative = false;
            return;
        }
    }

    //? Finds the leading zeros in this digit so only correct values are added
    size_t starting_digit = 0;
    bool   non_zero_found = false;

    for (int i = 0; i < temp_string.length(); i++) {
        if (temp_string[i] != '0') {
            starting_digit = i;
            non_zero_found = true;
            break;
        }
    }

    //? Assigns the correct value to digits avoiding any leading zeros
    if (non_zero_found) {
        this->digits = temp_string.substr(starting_digit);
    } else {
        // This now correctly handles "0", "000", and an empty temp_string (from
        // input "-")
        this->digits = "0";
    }

    //? Ensures that if digits are zero then the isNegative is false
    if (this->digits == "0") {
        this->isNegative = false;
    }
}

//! Function to create a BigNum from an integer
BigNum::BigNum(const int num) {
    if (num < 0) {
        this->digits     = std::to_string(-static_cast<long long>(num));
        this->isNegative = true;
    } else {
        this->digits     = std::to_string(num);
        this->isNegative = false;
    }
}

BigNum::~BigNum() {
    //? As I am not using dynamic memory allocation, I don't need to use any
    //? destructor as it is only required for dynamic memory allocation
}

//* Input/Output Functions

//! Function to make the user input into a BigNum
void BigNum::input() {
    std::string input;
    std::cin >> input;

    BigNum temp(input);
    this->digits     = temp.digits;
    this->isNegative = temp.isNegative;
}

void BigNum::print() {
    if (this->isNegative && this->digits != "0") {
        std::cout << "-";
    }

    int length = this->digits.length();
    //? checking the whether the the length is multiple of 3 or not and is not
    //? the checking the how many values are left
    int check_for_multiple = length % 3;

    //? if check for multiple is not zero and length is greater than zero
    if (length > 0 && check_for_multiple == 0) {
        check_for_multiple = 3;
    }

    std::cout << this->digits.substr(0, check_for_multiple);

    for (int i = check_for_multiple; i < length; i = i + 3) {
        std::cout << "," << digits.substr(i, 3);
    }

    std::cout << std::endl;
}

