#include "Stack.hpp"

#include <iostream>

#include "Node.hpp"

Stack::Stack() { head = nullptr; }

Stack::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

bool Stack::isEmpty() const { return head == nullptr; }

void Stack::push(const int& item) {
    Node* newNode = new Node(item);
    newNode->next = head;
    head          = newNode;
}

int Stack::pop() {
    if (isEmpty()) {
        std::cout << "Stack is empty. Cannot pop." << std::endl;
        return -1;
    }

    Node* temp        = head;
    int   poppedValue = head->data;
    head              = head->next;
    delete temp;
    return poppedValue;
}

int Stack::top() const {
    if (isEmpty()) {
        std::cout << "Stack is empty, so there is no top element." << std::endl;
        return -1;
    }
    return head->data;
}
