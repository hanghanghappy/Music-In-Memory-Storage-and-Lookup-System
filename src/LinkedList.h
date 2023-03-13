// Music In-Memory Storage and Lookup System
// LinkedList class

#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include <fstream>
#include "Node.h"

template<class T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int length;
    int collisions;
public:
    LinkedList() { head = nullptr; tail = nullptr; length = 0; collisions = 0; } //constructor

    // Linked list operations
    int getLength() { return length; }
    int getCollisions() { return collisions; }
    Node<T>* getHead() { return head; }
    bool insertNode(Node<T>* a);
    bool removeNode(Node<T>* a);
    bool searchNode(Node<T>* a, T& returnedItem);
    void showContents();
    void showContentsinFile(std::ofstream& filename);
};

#endif
