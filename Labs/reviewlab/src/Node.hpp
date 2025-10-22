#ifndef NODE_HPP
#define NODE_HPP

struct Node {
    int   data;
    Node* next;
    Node(const int& value);
};

#endif  // NODE_HPP