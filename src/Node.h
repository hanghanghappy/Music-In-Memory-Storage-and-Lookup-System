// Music In-Memory Storage and Lookup System
// Node class

#ifndef NODE_H
#define NODE_H

template<typename T>
class Node {
private:
    Node* next; // a pointer to the next node in the list
    T item; // store data
public:
    //Constructor
    Node() { next = nullptr; }
    Node(T a) { next = nullptr; item = a; }
    Node(Node* a, T b) { next = a; item = b; }
    
    //getters
    T getItem() { return item; }
    Node* getNext() { return next; }

    //setters
    void setItem(T a) { item = a; }
    void setNext(Node* a) { next = a; }
};
#endif