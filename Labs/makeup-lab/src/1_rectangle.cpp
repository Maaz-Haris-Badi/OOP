#ifndef RECTANGLE
#define RECTANGLE

#include <iostream>

class Rectangle {
public:

    // Constructor
    Rectangle(const double w, const double h);

    // Getters
    double get_length() const;

    double get_width() const;

    // Geometry
    double get_perimeter() const;
    double get_area() const;

    // Resize by factor
    void resize(const double);

private:

    double width, height;
};

// ---- Definitions with scope resolution ----
Rectangle::Rectangle(const double w, const double h) {
    // TODO: Initialize width and height
    width  = w;
    height = h;
}

double Rectangle::get_length() const { return height; }

double Rectangle::get_width() const { return width; }

double Rectangle::get_perimeter() const { return ((2 * height) + (2 * width)); }

double Rectangle::get_area() const { return (width * height); }

void Rectangle::resize(const double factor) {
    width  = width * factor;
    height = height * factor;
}

#endif
