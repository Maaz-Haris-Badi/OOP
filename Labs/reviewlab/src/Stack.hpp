#ifndef STACK_HPP
#define STACK_HPP

#include "Node.hpp"

class Stack {
public:

    Stack();
    ~Stack();

    void push(const int& item);
    int  pop();
    int  top() const;
    bool isEmpty() const;

private:

    Node* head;
};

#endif  // STACK_HPP