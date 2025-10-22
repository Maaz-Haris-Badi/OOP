#include <iostream>
using namespace std;

// Node class representing each element in the linked list
class Node {
public:

    int   data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

// LinkedList class managing the linked list operations
class LinkedList {
private:

    Node* head;

public:

    LinkedList() : head(nullptr) {}

    // Function to insert a node at the end
    void insertAtEnd(int value);

    // Function to print all elements in the linked list
    void print();

    // Function to calculate the length of the linked list
    int length();

    // Function to insert before a specific value
    void insertBefore(int target, int newValue);

    // Function to insert after a specific value
    void insertAfter(int target, int newValue);

    // Function to delete node before a specific value
    void deleteBefore(int target);

    // Function to delete node after a specific value
    void deleteAfter(int target);
};

void LinkedList::insertAtEnd(int value) {
    Node* newNode = new Node(value);
    if (!head)
        head = newNode;
    else {
        Node* temp = head;
        while (temp->next != nullptr) temp = temp->next;
        temp->next = newNode;
    }
}

void LinkedList::print() {
    Node* temp = head;
    if (temp == nullptr) {
        std::cout << "List is empty." << endl;
        return;
    }
    while (temp != nullptr) {
        std::cout << temp->data << " -> ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

int LinkedList::length() {
    int   length = 0;
    Node* temp   = head;

    while (temp != nullptr) {
        length++;
        temp = temp->next;
    }

    return length;
}

void LinkedList::insertBefore(int target, int newValue) {
    if (!head) {
        std::cout << "List is empty. Cannot add before a target." << std::endl;
        return;
    }

    if (head->data == target) {
        Node* newNode = new Node(newValue);
        newNode->next = head;
        head          = newNode;
        return;
    }

    Node* temp = head;
    Node* prev = nullptr;

    while (temp != nullptr && temp->data != target) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        std::cout << "Target node not found in the list." << std::endl;
    } else {
        Node* newNode = new Node(newValue);
        prev->next    = newNode;
        newNode->next = temp;
    }
}

void LinkedList::insertAfter(int target, int newValue) {
    Node* temp = head;

    while (temp != nullptr && temp->data != target) {
        temp = temp->next;
    }

    if (temp == nullptr) {
        std::cout << "Target node not found in the list." << std::endl;
    } else {
        Node* newNode = new Node(newValue);
        newNode->next = temp->next;
        temp->next    = newNode;
    }
}

void LinkedList::deleteBefore(int target) {
    if (head == nullptr || head->next == nullptr) {
        std::cout << "List is too short to perform this operation."
                  << std::endl;
        return;
    }

    if (head->next->data == target) {
        Node* nodeToDelete = head;
        head               = head->next;
        delete nodeToDelete;
        return;
    }

    Node* current = head;

    while (current->next != nullptr && current->next->next != nullptr) {
        if (current->next->next->data == target) {
            Node* nodeToDelete = current->next;

            current->next = current->next->next;

            delete nodeToDelete;
            return;
        }
        current = current->next;
    }

    std::cout << "Target node not found or no node exists before it."
              << std::endl;
}

void LinkedList::deleteAfter(int target) {
    if (head == nullptr || head->next == nullptr) {
        std::cout << "List is too short to perform this operation."
                  << std::endl;
        return;
    }

    Node* current = head;

    while (current != nullptr && current->data != target) {
        current = current->next;
    }

    if (current == nullptr) {
        std::cout << "Target not found";
        return;
    }

    if (current->next == nullptr) {
        std::cout << "Target is last Node and there is no next node";
        return;
    }

    Node* nodeToDelete = current->next;

    current->next = nodeToDelete->next;

    delete nodeToDelete;
}

// Main function for testing
int main() {
    LinkedList list;
    int        n, value;

    cout << "Enter number of elements to insert: ";
    cin >> n;

    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) {
        cin >> value;
        list.insertAtEnd(value);
    }

    cout << "Initial List: ";
    list.print();

    cout << "Length of list: " << list.length() << endl;

    // Demonstration of insertBefore, insertAfter, deleteBefore, deleteAfter
    cout << "\nInsert a value before a given element:\n";
    list.insertBefore(20, 15);  // Example
    list.print();

    cout << "\nInsert a value after a given element:\n";
    list.insertAfter(30, 35);  // Example
    list.print();

    cout << "\nDelete node before a given element:\n";
    list.deleteBefore(20);
    list.print();

    cout << "\nDelete node after a given element:\n";
    list.deleteAfter(30);
    list.print();

    return 0;
}
