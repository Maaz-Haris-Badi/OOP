#include <iostream>
using namespace std;

class Payment {
private:

    double m_amount;

public:

    double get_m_amount();

    void set_m_amount(double &other);

    virtual void paymentDetails();
};

class CashPayment : public Payment {
public:

    CashPayment(double other);

    void paymentDetails() override;
};

class CreditCardPayment : public Payment {
private:

    std::string m_name_on_the_card, m_expiration_date, m_credit_card_number;

public:

    std::string get_name_of_the_card();

    std::string get_expiry_of_the_card();

    std::string get_card_number();

    void set_name_of_card(const std::string &other);

    void set_expiration_date(const std::string &other);

    void set_credit_card_number(const std::string &other);

    CreditCardPayment(double other, const std::string &name,
                      const std::string &expire, const std::string &cardnum);

    void paymentDetails() override;
};

void Payment::set_m_amount(double &other) { this->m_amount = other; };

double Payment::get_m_amount() { return this->m_amount; };

void Payment::paymentDetails() {
    double payment = Payment::get_m_amount();

    std::cout << "Details of the Payment: Rs." << payment << "/=" << std::endl;
};

CashPayment::CashPayment(double other) { Payment::set_m_amount(other); };

void CashPayment::paymentDetails() {
    double amount = Payment::get_m_amount();
    std::cout << "Amount of the cash payment was " << amount << std::endl;
};

std::string CreditCardPayment::get_name_of_the_card() {
    return this->m_name_on_the_card;
};

std::string CreditCardPayment::get_expiry_of_the_card() {
    return this->m_expiration_date;
};

std::string CreditCardPayment::get_card_number() {
    return this->m_credit_card_number;
};

void CreditCardPayment::set_name_of_card(const std::string &other) {
    this->m_name_on_the_card = other;
}

void CreditCardPayment::set_expiration_date(const std::string &other) {
    this->m_expiration_date = other;
}

void CreditCardPayment::set_credit_card_number(const std::string &other) {
    this->m_credit_card_number = other;
}

CreditCardPayment::CreditCardPayment(double other, const std::string &name,
                                     const std::string &expire,
                                     const std::string &cardnum) {
    Payment::set_m_amount(other);
    CreditCardPayment::set_name_of_card(name);
    CreditCardPayment::set_expiration_date(expire);
    CreditCardPayment::set_credit_card_number(cardnum);
}

void CreditCardPayment::paymentDetails() {
    double      amount;
    std::string name, expiry, cardnumber;
    amount     = Payment::get_m_amount();
    name       = CreditCardPayment::get_name_of_the_card();
    expiry     = CreditCardPayment::get_expiry_of_the_card();
    cardnumber = CreditCardPayment::get_card_number();

    std::cout << "Amount of Credit Card Payment: " << amount << std::endl;
    std::cout << "Name on the Credit Card: " << name << std::endl;
    std::cout << "Epiration Date: " << expiry << std::endl;
    std::cout << "Credit Card Number: " << cardnumber << std::endl;
}

// Write Your Code Here

int main() {
    CashPayment       cp1(75.25);
    CashPayment       cp2(36.95);
    CreditCardPayment ccp1(95.15, "Smith", "12/21/2009", "321654987");
    CreditCardPayment ccp2(45.75, "James", "10/30/2008", "963852741");

    cout << "Details of Cash #1..." << endl;
    cp1.paymentDetails();

    cout << "\nDetails of Cash #2..." << endl;
    cp2.paymentDetails();

    cout << "\nDetails of Credit Card #1..." << endl;
    ccp1.paymentDetails();

    cout << "\nDetails of Credit Card #2..." << endl;
    ccp2.paymentDetails();

    return 0;
};