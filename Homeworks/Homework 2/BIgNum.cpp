#include "BigNum.h"

#include <cctype>
#include <fstream>
#include <iostream>

void BigNum::removeLeadingZeros() {
    int  starting_digit = 0;
    bool non_zero_found = false;

    for (int i = 0; i < this->digits.length(); i++) {
        if (this->digits[i] != '0') {
            starting_digit = i;
            non_zero_found = true;
            break;
        }
    }

    if (non_zero_found) {
        this->digits = this->digits.substr(starting_digit);
    } else {
        this->digits = "0";
    }
}

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

    this->digits = temp_string;

    removeLeadingZeros();

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

void BigNum::inputFromFile(const std::string &fileName) {
    std::ifstream inFile(fileName);
    std::string   inputStr;

    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open file " << fileName << std::endl;
        return;
    }

    inFile >> inputStr;
    inFile.close();

    BigNum temp(inputStr);
    this->digits     = temp.digits;
    this->isNegative = temp.isNegative;
}

void BigNum::printToFile(const std::string &fileName) {
    //? creating an outfile
    std::ofstream outFile(fileName);

    //? Checking whether the file is open for writing
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file " << fileName << std::endl;
        return;
    }

    //? Used the same logic as printing just used outfile instead of std::cout
    if (this->isNegative && this->digits != "0") {
        outFile << "-";
    }

    int length = this->digits.length();

    int check_for_multiple = length % 3;

    if (length > 0 && check_for_multiple == 0) {
        check_for_multiple = 3;
    }

    outFile << this->digits.substr(0, check_for_multiple);

    for (int i = check_for_multiple; i < length; i = i + 3) {
        outFile << "," << digits.substr(i, 3);
    }

    outFile << std::endl;
}
//* Initialization/Assignment Operations
//! Function to copy objects of BigNum to another
void BigNum::copy(const BigNum &bigNum) {
    this->digits     = bigNum.digits;
    this->isNegative = bigNum.isNegative;
}

void BigNum::operator=(const BigNum &bigNum) { copy(bigNum); }

void BigNum::zerofy() {
    this->digits     = "0";
    this->isNegative = false;
}

void BigNum::clear() { zerofy(); }

//* Arithmetic Operations
//^ Addition

void BigNum::increment() {
    //? We will access the last digit of BigNum and 1 and check whether the
    //? addition makes it more than 10; if it does then we would access the
    //? second last digit and continue the process untill addtion is not less
    //? than 10

    if (this->isNegative) {
        int borrow = 1;

        for (int i = this->digits.length() - 1; i >= 0; i--) {
            int digit = (this->digits[i] - '0') - borrow;

            if (digit < 0) {
                this->digits[i] = (digit + 10) + '0';
                borrow          = 1;
            } else {
                this->digits[i] = digit + '0';
                borrow          = 0;
                break;
            }
        }

        removeLeadingZeros();

        if (this->digits == "0") {
            this->isNegative = false;
        }

    } else {
        int carry = 1;

        for (int i = this->digits.length() - 1; i >= 0; i--) {
            int digit       = (this->digits[i] - '0') + carry;
            this->digits[i] = (digit % 10) + '0';
            carry           = digit / 10;
            if (carry == 0) {
                break;
            }
        }

        if (carry == 1) {
            this->digits.insert(0, "1");
        }
    }
}

BigNum BigNum::add(const BigNum &bigNum) {
    //? if Signs are same,we will perfome additions and give sign of any of the
    //? numbers.
    if (this->isNegative == bigNum.isNegative) {
        std::string a       = this->digits;
        std::string b       = bigNum.digits;
        std::string sum_str = "";

        //? Making sure that the length of both the numbers is same
        if (a.length() < b.length()) {
            a.insert(0, b.length() - a.length(), '0');
        } else if (b.length() < a.length()) {
            b.insert(0, a.length() - b.length(), '0');
        }

        int carry = 0;
        int len   = a.length();

        for (int i = len - 1; i >= 0; i--) {
            int digit1     = a[i] - '0';
            int digit2     = b[i] - '0';
            int currentSum = digit1 + digit2 + carry;

            sum_str += std::to_string(currentSum % 10);
            carry = currentSum / 10;
        }

        //? Makes sure that if the final carry is greater than 0 than it is
        //? added to the number
        if (carry > 0) {
            sum_str += std::to_string(carry);
        }

        //? Reversing the string as we have calculated the answer in the reverse
        //? order
        for (int i = 0; i < sum_str.length() / 2; ++i) {
            std::swap(sum_str[i], sum_str[sum_str.length() - 1 - i]);
        }

        //? makes a new BigNum and make sure that the sign is set to correct
        //? value
        BigNum result(sum_str);
        result.isNegative = this->isNegative;

        result.removeLeadingZeros();

        if (result.digits == "0") {
            result.isNegative = false;
        }

        return result;

    } else {
        //? if the signs of both the numbers are different we will perfome
        // subtraction
        std::string s1               = this->digits;
        std::string s2               = bigNum.digits;
        bool        resultIsNegative = false;

        //? We will determine which number is bigger and use the sign of the
        //? bigger number
        bool s1_is_bigger = (s1.length() > s2.length()) ||
                            (s1.length() == s2.length() && s1 > s2);

        if (s1_is_bigger) {
            resultIsNegative = this->isNegative;
        } else {
            std::swap(s1, s2);
            resultIsNegative = bigNum.isNegative;
        }

        //? We will make subtract two numbers from right to left
        std::string diff_str = "";
        int         borrow   = 0;
        int         len1     = s1.length();
        int         len2     = s2.length();

        for (int i = len1 - 1, j = len2 - 1; i >= 0; i--, j--) {
            int digit1 = s1[i] - '0';
            int digit2 = (j >= 0) ? s2[j] - '0' : 0;

            int currentDiff = digit1 - digit2 - borrow;

            if (currentDiff < 0) {
                currentDiff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            diff_str += std::to_string(currentDiff);
        }

        //? Reversing the string as we have calculated the answer in the reverse
        //? order
        for (size_t i = 0; i < diff_str.length() / 2; ++i) {
            std::swap(diff_str[i], diff_str[diff_str.length() - 1 - i]);
        }

        BigNum result(diff_str);
        result.isNegative = resultIsNegative;

        result.removeLeadingZeros();

        if (result.digits == "0") {
            result.isNegative = false;
        }
        return result;
    }
}

BigNum BigNum::add(const int num) {
    BigNum temp(num);
    return this->add(temp);
}

void BigNum::compoundAdd(const BigNum &bigNum) { *this = this->add(bigNum); }

void BigNum::compoundAdd(const int num) {
    BigNum temp(num);
    *this = this->add(temp);
}

bool BigNum::equals(const BigNum &other) {
    return (this->digits == other.digits) &&
           (this->isNegative == other.isNegative);
}

void BigNum::decrement() { this->compoundSubtract(1); }

BigNum BigNum::subtract(const BigNum &bigNum) {
    BigNum temp     = bigNum;
    temp.isNegative = !temp.isNegative;
    if (temp.digits == "0") temp.isNegative = false;
    return this->add(temp);
}

BigNum BigNum::subtract(const int num) {
    BigNum temp(num);
    return this->subtract(temp);
}

void BigNum::compoundSubtract(const BigNum &bigNum) {
    *this = this->subtract(bigNum);
}

void BigNum::compoundSubtract(const int num) {
    BigNum temp(num);
    *this = this->subtract(temp);
}

BigNum BigNum::multiply(const BigNum &bigNum) {
    //? Checking if any value is zero so just assign the answer "0" as it will
    //? be zero
    if (this->digits == "0" || bigNum.digits == "0") {
        return BigNum("0");
    }

    bool resultNegative = (this->isNegative != bigNum.isNegative);

    std::string str1 = this->digits;
    std::string str2 = bigNum.digits;

    int n1 = str1.length();
    int n2 = str2.length();

    std::string res;
    res.insert(0, (n1 + n2), '0');

    for (int i = n1 - 1; i >= 0; --i) {
        int a = str1[i] - '0';
        for (int j = n2 - 1; j >= 0; --j) {
            int b = str2[j] - '0';

            int posLow  = i + j + 1;
            int posHigh = i + j;

            int sum      = (res[posLow] - '0') + a * b;
            res[posLow]  = '0' + (sum % 10);
            res[posHigh] = '0' + ((res[posHigh] - '0') + (sum / 10));
        }
    }

    //? remove leading zeros
    int  starting_digit = 0;
    bool non_zero_found = false;

    for (int i = 0; i < res.length(); i++) {
        if (res[i] != '0') {
            starting_digit = i;
            non_zero_found = true;
            break;
        }
    }

    if (non_zero_found) {
        res = res.substr(starting_digit);
    } else {
        res = "0";
    }

    if (resultNegative && res != "0") {
        res.insert(0, 1, '-');
    }

    return BigNum(res);
}