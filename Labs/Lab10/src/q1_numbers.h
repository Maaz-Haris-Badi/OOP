#include <iostream>

class NumInterface {
public:

    virtual void display() const = 0;

    virtual void increment() = 0;

    virtual ~NumInterface() {};
};
