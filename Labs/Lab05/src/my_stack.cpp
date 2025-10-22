#ifndef MY_STACK
#define MY_STACK

/*
Write your solution here.
*/
#include <iostream>
class MyStack {
private:

    int *arr;
    int  top;
    int  capacity;

public:

    MyStack(int size) {
        arr      = new int[size];
        capacity = size;
        top      = -1;
    }

    void push(int x) {
        if (top == capacity - 1) {
            std::cout << "Stack Overflow\n";
            return;
        }
        arr[++top] = x;
    }

    int pop() {
        if (top == -1) {
            std::cout << "Stack Underflow\n";
            return -1;
        }
        return arr[top--];
    }

    int topElement() {
        if (top == -1) {
            std::cout << "Stack is empty\n";
            return -1;
        }
        return arr[top];
    }

    bool isEmpty() { return top == -1; }

    void display() {
        if (top == -1) {
            std::cout << "Stack is empty\n";
            return;
        }
        for (int i = top; i >= 0; i--) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }

    ~MyStack() { delete[] arr; }
};

int main() {
    MyStack stack(100);
    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.display();
    std::cout << "Top element is: " << stack.topElement() << std::endl;
    stack.pop();
    stack.push(40);
    stack.display();
    stack.pop();
    std::cout << "Top element is: " << stack.topElement() << std::endl;
    stack.pop();
    stack.push(50);
    std::cout << "Top element is: " << stack.topElement() << std::endl;
    stack.display();
    return 0;
}

#endif  // MY_STACK
