#include "BigNum.h"

#include <cctype>
#include <fstream>
#include <iostream>

//* Constructor and Destructor Functions

//! Function to set the digits to "0" and is_negative to false
BigNum::BigNum() {
    this->digits      = "0";
    this->is_negative = false;
}

//! Function to copy the given BigNum
BigNum::BigNum(const BigNum &bigNum) {
    this->digits      = bigNum.digits;
    this->is_negative = bigNum.is_negative;
}

//! Function to copy the given Big Num to a new BigNum
BigNum::BigNum(const std::string &bigStr) {
    //? Checks whether the string is empty or not and assigns the correct values
    if (bigStr.empty()) {
        this->digits      = "0";
        this->is_negative = false;
        return;
    }

    std::string temp_string;
    //? Checks for the negative sign and assigns the correct values
    if (bigStr.front() == '-') {
        temp_string       = bigStr.substr(1);
        this->is_negative = true;
    } else {
        temp_string       = bigStr;
        this->is_negative = false;
    }

    //? Validates that all the values in the string are digits and not any
    //? alphabet
    for (char c : temp_string) {
        if (!isdigit(c)) {
            this->digits      = "0";
            this->is_negative = false;
            return;
        }
    }

    this->digits = temp_string;

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

    //? Ensures that if digits are zero then the is_negative is false
    if (this->digits == "0") {
        this->is_negative = false;
    }
}

//! Function to create a BigNum from an integer
BigNum::BigNum(const int num) {
    if (num < 0) {
        this->digits      = std::to_string(-static_cast<long long>(num));
        this->is_negative = true;
    } else {
        this->digits      = std::to_string(static_cast<long long>(num));
        this->is_negative = false;
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
    this->digits      = temp.digits;
    this->is_negative = temp.is_negative;
}

//! Function to print the BigNum in the required format
void BigNum::print() {
    if (this->is_negative && this->digits != "0") {
        std::cout << "-";
    }

    int length = this->digits.length();

    if (length == 0) {
        std::cout << "0" << std::endl;
        return;
    }
    //? checking the whether the the length is multiple of 3 or not and is not
    //? the checking the how many values are left
    int check_for_multiple = length % 3;

    //? if check for multiple is not zero and length is greater than zero
    if (length > 0 && check_for_multiple == 0) {
        check_for_multiple = 3;
    }

    std::cout << this->digits.substr(0, check_for_multiple);

    for (int i = check_for_multiple; i < length; i += 3) {
        std::cout << "," << this->digits.substr(i, 3);
    }

    std::cout << std::endl;
}

void BigNum::inputFromFile(const std::string &fileName) {
    std::ifstream in_File(fileName);
    std::string   input_Str;

    if (!in_File.is_open()) {
        std::cerr << "Error: Could not open file " << fileName << std::endl;
        return;
    }

    in_File >> input_Str;
    in_File.close();

    BigNum temp(input_Str);
    this->digits      = temp.digits;
    this->is_negative = temp.is_negative;
}

void BigNum::printToFile(const std::string &fileName) {
    //? creating an outfile
    std::ofstream out_File(fileName);

    //? Checking whether the file is open for writing
    if (!out_File.is_open()) {
        std::cerr << "Error: Could not open file " << fileName << std::endl;
        return;
    }

    //? Used the same logic as printing just used outfile instead of std::cout
    if (this->is_negative && this->digits != "0") {
        out_File << "-";
    }

    out_File << this->digits;
}

//* Initialization/Assignment Operations
//! Function to copy objects of BigNum to another
void BigNum::copy(const BigNum &bigNum) {
    this->digits      = bigNum.digits;
    this->is_negative = bigNum.is_negative;
}

void BigNum::operator=(const BigNum &bigNum) { copy(bigNum); }

void BigNum::zerofy() {
    this->digits      = "0";
    this->is_negative = false;
}

void BigNum::clear() { zerofy(); }

//* Arithmetic Operations
//^ Addition

void BigNum::increment() {
    //? We will access the last digit of BigNum and 1 and check whether the
    //? addition makes it more than 10; if it does then we would access the
    //? second last digit and continue the process untill addtion is not less
    //? than 10

    if (this->is_negative) {
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

        if (this->digits == "0") {
            this->is_negative = false;
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
    if (this->is_negative == bigNum.is_negative) {
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
        result.is_negative = this->is_negative;

        int  starting_digit = 0;
        bool non_zero_found = false;

        for (int i = 0; i < result.digits.length(); i++) {
            if (result.digits[i] != '0') {
                starting_digit = i;
                non_zero_found = true;
                break;
            }
        }

        if (non_zero_found) {
            result.digits = result.digits.substr(starting_digit);
        } else {
            result.digits = "0";
        }

        if (result.digits == "0") {
            result.is_negative = false;
        }

        return result;

    } else {
        //? if the signs of both the numbers are different we will perfome
        // subtraction
        std::string s1                = this->digits;
        std::string s2                = bigNum.digits;
        bool        resultis_negative = false;

        //? We will determine which number is bigger and use the sign of the
        //? bigger number
        bool s1_is_bigger = (s1.length() > s2.length()) ||
                            (s1.length() == s2.length() && s1 > s2);

        if (s1_is_bigger) {
            resultis_negative = this->is_negative;
        } else {
            std::swap(s1, s2);
            resultis_negative = bigNum.is_negative;
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
        result.is_negative = resultis_negative;

        int  starting_digit = 0;
        bool non_zero_found = false;

        for (int i = 0; i < result.digits.length(); i++) {
            if (result.digits[i] != '0') {
                starting_digit = i;
                non_zero_found = true;
                break;
            }
        }

        if (non_zero_found) {
            result.digits = result.digits.substr(starting_digit);
        } else {
            result.digits = "0";
        }

        if (result.digits == "0") {
            result.is_negative = false;
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

void BigNum::decrement() { this->compoundSubtract(1); }

BigNum BigNum::subtract(const BigNum &bigNum) {
    BigNum temp      = bigNum;
    temp.is_negative = !temp.is_negative;
    if (temp.digits == "0") temp.is_negative = false;
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

    bool resultNegative = (this->is_negative != bigNum.is_negative);

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

BigNum BigNum::div(const BigNum &bigNum) {
    //? if the divisor is zero we will thorw an error
    if (bigNum.digits == "0") {
        // std::cout << "Division by zero is not allowed." << std::endl;
        //? The pdf says to throw an exception in case of division by zero
        throw std::invalid_argument("Division by zero is not allowed.");
    }

    //? if the divident is zero we would return a zero
    if (this->digits == "0") {
        return BigNum("0");
    }

    //? We will determine the sign of result by checking if both the signs are
    //? different or not
    bool result_sign = this->is_negative != bigNum.is_negative;

    //? We will make absolute copy of both the numbers to work with
    //? and will assign the sign at the end
    BigNum dividend      = *this;
    dividend.is_negative = false;
    BigNum divisor       = bigNum;
    divisor.is_negative  = false;

    //? if the dividend is less than divisor the result is zero
    if (dividend.lessThan(divisor)) {
        BigNum result("0");
        result.is_negative = false;
        return result;

        //?if the dividend is equal to divisor the result is one
    } else if (dividend.equals(divisor)) {
        BigNum result("1");
        result.is_negative = result_sign;
        return result;
    }

    //? We will create a quotient string to store quotient
    //? and a current_chunk to store the part of dividend we are currently
    //? working with
    std::string quotient = "";
    BigNum      current_chunk("0");

    //? We are looping through each digit of dividend and adding it to current
    //? chunk only if current chunk is less than divisor and also if current
    //? chunk is "0" then we will make it empty so that we don't have leading
    //? zeros
    for (char digit : dividend.digits) {
        if (current_chunk.digits == "0") {
            current_chunk.digits = "";
        }
        //? Adding the next digit to current chunk
        current_chunk.digits += digit;

        //? If current chunk is still less than divisor then we will add a
        //? zero to the quotient if quotient is not empty and continue to the
        //? next digit
        if (current_chunk.lessThan(divisor)) {
            if (!quotient.empty()) {
                quotient += '0';
            }
            continue;
        }

        //? Now we will find how many times the divisor can go into current
        //? chunk by repeatedly subtracting divisor from current chunk and
        //? counting the number of times we can do this
        int times = 0;
        while (current_chunk.greaterThan(divisor) ||
               current_chunk.equals(divisor)) {
            current_chunk = current_chunk.subtract(divisor);
            times++;
        }

        quotient += ('0' + times);
    }

    //? Returning a BigNum with the quotient and the correct sign that we had
    //? determined before hand
    BigNum result(quotient);
    result.is_negative = result_sign;

    //? if the result is zero we will make sure that the sign is positive
    if (result.digits == "0") {
        result.is_negative = false;
    }

    return result;
}

BigNum BigNum::mod(const BigNum &bigNum) {
    //? Modulo can be calculated by subtracting the result of division and
    //? multiplying it back with the divisor
    BigNum divisionResult       = this->div(bigNum);
    BigNum multiplicationResult = divisionResult.multiply(bigNum);
    BigNum remainder            = this->subtract(multiplicationResult);
    return remainder;
}

bool BigNum::equals(const BigNum &bigNum) {
    //? First we will check wherther the lengths and signs are same or not
    if (this->digits.length() != bigNum.digits.length() ||
        this->is_negative != bigNum.is_negative) {
        return false;
    }

    //? Then we will check each digit one by one
    for (int i = 0; i < this->digits.length(); i++) {
        if (this->digits[i] != bigNum.digits[i]) {
            return false;
        }
    }
    return true;
}

bool BigNum::notEquals(const BigNum &bigNum) {
    //? A number is not equal to another if they are not equal
    return !this->equals(bigNum);
}

bool BigNum::greaterThan(const BigNum &bigNum) {
    //?  Compare signs first
    //? If this is positive and other is negative, this is greater.
    if (this->is_negative == false && bigNum.is_negative == true) {
        return true;
    }
    //? If this is negative and other is positive, this is smaller.
    if (this->is_negative == true && bigNum.is_negative == false) {
        return false;
    }

    //? At this point, both numbers have the same sign.

    //? Both numbers are positive
    if (this->is_negative == false) {
        //? Compare by length first
        if (this->digits.length() > bigNum.digits.length()) {
            return true;
        }
        if (this->digits.length() < bigNum.digits.length()) {
            return false;
        }
        //? If lengths are the same, compare the strings directly
        for (int i = 0; i < this->digits.length(); i++) {
            if (this->digits[i] > bigNum.digits[i]) {
                return true;
            }
            if (this->digits[i] < bigNum.digits[i]) {
                return false;
            }
            if (this->digits[i] == bigNum.digits[i]) {
                continue;
            }
        }
    }

    //? Both numbers are negative
    if (this->is_negative == true) {
        //? For negative numbers, the logic is reversed.
        //? The number with the shorter length is greater (e.g., -10 > -100).
        if (this->digits.length() < bigNum.digits.length()) {
            return true;
        }
        if (this->digits.length() > bigNum.digits.length()) {
            return false;
        }
        //? If lengths are the same, the smaller string represents the
        //? greater value.
        for (int i = 0; i < this->digits.length(); i++) {
            if (this->digits[i] > bigNum.digits[i]) {
                return true;
            }
            if (this->digits[i] < bigNum.digits[i]) {
                return false;
            }

            if (this->digits[i] == bigNum.digits[i]) {
                continue;
            }
        }
    }

    //? If all checks fail, the numbers are equal, so it's not "greater
    //? than".
    return false;
}

bool BigNum::lessThan(const BigNum &bigNum) {
    //? A number is less than another if it is neither greater nor equal
    return (!this->greaterThan(bigNum) && !this->equals(bigNum));
}
