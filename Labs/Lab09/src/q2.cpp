#include <iostream>
using namespace std;

class publication {
private:

    std::string title;
    float       price;

public:

    virtual void getdata();

    virtual void putdata();

    std::string get_string();

    float get_price();

    void set_title(std::string &other);

    void set_price(float &other);
};

void publication::getdata() {
    std::string title_of_publication;
    float       price_of_publication;
    std::cout << "Welcome to the Publication" << std::endl;
    std::cout << "Enter the title of the publication" << std::endl;
    std::getline(std::cin, title_of_publication);
    std::cout << "Enter the price of the publication" << std::endl;
    std::cin >> price_of_publication;

    this->title = title_of_publication;
    this->price = price_of_publication;
}

void publication::putdata() {
    std::cout << "Title of the Publication is: " << this->title << std::endl;

    std::cout << "Price of the Publicationn is: " << this->price << std::endl;
}

std::string publication::get_string() { return this->title; };

float publication::get_price() { return this->price; };

void publication::set_title(std::string &other) { this->title = other; };

void publication::set_price(float &other) { this->price = other; };

class book : public publication {
private:

    int pagecount;

public:

    void getdata() override;

    void putdata() override;

    int get_page_count();

    void set_page_count(int &other);
};

int book::get_page_count() { return this->pagecount; };

void book::set_page_count(int &other) { this->pagecount = other; };

void book::getdata() {
    std::string title_of_book;
    float       price_of_book;
    int         page_count_of_book;
    std::cout << "Welcome to the Book" << std::endl;
    std::cout << "Enter the title of the Book" << std::endl;
    std::getline(std::cin, title_of_book);
    std::cout << "Enter the price of the publication" << std::endl;
    std::cin >> price_of_book;
    std::cout << "Enter the page count of the book" << std::endl;
    std::cin >> page_count_of_book;

    publication::set_title(title_of_book);
    publication::set_price(price_of_book);
    book::set_page_count(page_count_of_book);
};

void book::putdata() {
    std::cout << "Title of the Book is: " << publication::get_string()
              << std::endl;

    std::cout << "Price of the Book is: " << publication::get_price()
              << std::endl;

    std::cout << "Page count of the Book " << book::get_page_count()
              << std::endl;
}

class tape : public publication {
private:

    int playingtime;

public:

    void getdata() override;

    void putdata() override;

    int get_playing_time();

    void set_playing_time(int &other);
};

int tape::get_playing_time() { return this->playingtime; };

void tape::set_playing_time(int &other) { this->playingtime = other; };

void tape::getdata() {
    std::string title_of_tape;
    float       price_of_tape;
    int         time_of_tape;
    std::cout << "Welcome to the Tape" << std::endl;
    std::cout << "Enter the title of the tape " << std::endl;
    std::getline(std::cin, title_of_tape);
    std::cout << "Enter the price of the tape " << std::endl;
    std::cin >> price_of_tape;
    std::cout << "Enter the palying time of tape " << std::endl;
    std::cin >> time_of_tape;

    publication::set_title(title_of_tape);
    publication::set_price(price_of_tape);
    tape::set_playing_time(time_of_tape);
};

void tape::putdata() {
    std::cout << "Title of the tape is: " << publication::get_string()
              << std::endl;

    std::cout << "Price of the tape is: " << publication::get_price()
              << std::endl;

    std::cout << "Page count of the tape " << tape::get_playing_time()
              << std::endl;
}

// Write Your Code Here

int main() {
    book b;
    tape t;
    b.getdata();
    cin.ignore();
    t.getdata();
    b.putdata();
    t.putdata();
}