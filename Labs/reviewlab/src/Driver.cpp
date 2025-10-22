#include <cassert>  // For asserting test conditions
#include <iostream>

#include "Node.hpp"
#include "Stack.hpp"

/**
 * @brief Runs a comprehensive test suite on the Stack class.
 */

void printwholestack(const Stack& stack) {
    if (stack.isEmpty()) {
        std::cout << "Stack is empty." << std::endl;
    } else {
        std::cout << "Top element is: " << stack.top() << std::endl;
    }
}

int main() {
    std::cout << "--- Stack Test Suite Initialized ---" << std::endl;

    // Test 1: Operations on a new, empty stack
    std::cout << "\n--- Test 1: Empty Stack Operations ---" << std::endl;
    Stack s1;
    assert(s1.isEmpty() == true);
    std::cout << "isEmpty() passed." << std::endl;

    std::cout << "Attempting top() on empty stack (should print error):"
              << std::endl;
    int topVal = s1.top();
    assert(topVal == -1);  // Check for your error code
    std::cout << "top() check passed." << std::endl;

    std::cout << "Attempting pop() on empty stack (should print error):"
              << std::endl;
    int popVal = s1.pop();
    assert(popVal == -1);          // Check for your error code
    assert(s1.isEmpty() == true);  // Should still be empty
    std::cout << "pop() check passed." << std::endl;

    // Test 2: Basic LIFO (Last-In, First-Out) logic
    std::cout << "\n--- Test 2: LIFO Correctness ---" << std::endl;
    Stack s2;
    s2.push(10);
    printwholestack(s2);
    s2.push(20);
    printwholestack(s2);
    s2.push(30);
    printwholestack(s2);

    assert(s2.isEmpty() == false);
    assert(s2.top() == 30);
    std::cout << "Pushed 10, 20, 30. top() is 30. Passed." << std::endl;

    assert(s2.pop() == 30);
    std::cout << "Popped 30. Passed." << std::endl;
    printwholestack(s2);

    assert(s2.top() == 20);
    std::cout << "New top() is 20. Passed." << std::endl;
    printwholestack(s2);

    assert(s2.pop() == 20);
    std::cout << "Popped 20. Passed." << std::endl;
    printwholestack(s2);

    assert(s2.top() == 10);
    std::cout << "New top() is 10. Passed." << std::endl;
    printwholestack(s2);

    assert(s2.pop() == 10);
    std::cout << "Popped 10. Passed." << std::endl;
    printwholestack(s2);

    assert(s2.isEmpty() == true);
    std::cout << "Stack is now empty. Passed." << std::endl;

    // Test 3: Pop-to-empty and try to pop again
    std::cout << "\n--- Test 3: Pop-to-Empty Edge Case ---" << std::endl;
    std::cout << "Attempting top() on just-emptied stack (should print error):"
              << std::endl;
    topVal = s2.top();
    assert(topVal == -1);
    std::cout << "top() check passed." << std::endl;

    std::cout << "Attempting pop() on just-emptied stack (should print error):"
              << std::endl;
    popVal = s2.pop();
    assert(popVal == -1);
    std::cout << "pop() check passed." << std::endl;

    // Test 4: Stress Test (Large number of items)
    std::cout << "\n--- Test 4: Stress Test (1,000,000 items) ---" << std::endl;
    Stack     s3;
    int const STRESS_SIZE = 1000000;
    std::cout << "Pushing " << STRESS_SIZE << " items..." << std::endl;
    for (int i = 0; i < STRESS_SIZE; ++i) {
        s3.push(i);
    }
    std::cout << "Push complete." << std::endl;
    assert(s3.isEmpty() == false);
    assert(s3.top() == STRESS_SIZE - 1);
    std::cout << "Top value is correct (" << s3.top() << "). Passed."
              << std::endl;

    bool stressTestPassed = true;
    std::cout << "Popping " << STRESS_SIZE << " items and verifying order..."
              << std::endl;
    for (int i = STRESS_SIZE - 1; i >= 0; --i) {
        int val = s3.pop();
        if (val != i) {
            std::cout << "!!! FAILED: Popped " << val << " but expected " << i
                      << std::endl;
            stressTestPassed = false;
            break;
        }
    }

    if (stressTestPassed) {
        std::cout << "All items popped in correct LIFO order. Passed."
                  << std::endl;
    }
    assert(s3.isEmpty() == true);
    std::cout << "Stack is empty after stress test. Passed." << std::endl;

    // Test 5: Destructor Test (Implicit)
    std::cout << "\n--- Test 5: Destructor Test ---" << std::endl;
    std::cout << "Creating stack in new scope..." << std::endl;
    {
        Stack s4;
        for (int i = 0; i < 500; ++i) {
            s4.push(i);
        }
        std::cout << "Stack s4 created and filled with 500 items." << std::endl;
    }  // s4 goes out of scope HERE. Its ~Stack() destructor is called.
    std::cout << "Stack s4 destroyed." << std::endl;
    std::cout << "(To verify no memory leaks, run this program with Valgrind)"
              << std::endl;

    std::cout << "\n--- All Tests Completed Successfully ---" << std::endl;
    return 0;
}