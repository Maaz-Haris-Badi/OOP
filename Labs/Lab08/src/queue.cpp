#include <iostream>
using namespace std;

// Node class
class Node {
public:

    int   data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

// Queue class
class Queue {
private:

    Node* front;
    Node* rear;

public:

    Queue() : front(nullptr), rear(nullptr) {}

    // Function to insert an element at the rear
    void enqueue(int value);

    // Function to remove an element from the front
    void dequeue();

    // Function to print the queue
    void print_queue();

    // Helper: Check if queue is empty
    bool isEmpty();
};

bool Queue::isEmpty() { return front == nullptr; }

void Queue::enqueue(int value) {
    Node* newNode = new Node(value);
    if (rear == nullptr) {
        front = rear = newNode;
        return;
    }
    rear->next = newNode;
    rear       = newNode;
}

void Queue::dequeue() {
    if (isEmpty()) {
        cout << "Queue is empty. Cannot dequeue." << endl;
        return;
    }
    Node* temp = front;
    front      = front->next;

    if (front == nullptr) {
        rear = nullptr;
    }

    delete temp;
}

void Queue::print_queue() {
    if (isEmpty()) {
        cout << "Queue is empty." << endl;
        return;
    }
    Node* temp = front;

    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

// Main function
int main() {
    Queue q;
    int   n, val;

    cout << "Enter number of elements to enqueue: ";
    cin >> n;
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) {
        cin >> val;
        q.enqueue(val);
    }

    cout << "Queue after enqueue: ";
    q.print_queue();

    int d;
    cout << "Enter number of elements to dequeue: ";
    cin >> d;
    for (int i = 0; i < d; i++) {
        q.dequeue();
    }

    cout << "Queue after dequeue: ";
    q.print_queue();

    return 0;
}
