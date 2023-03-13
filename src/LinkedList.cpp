// Music In-Memory Storage and Lookup System
// LinkedList class

#include "LinkedList.h"
#include <iostream>
#include <fstream>

using namespace std;

//The insertNode function inserts a new node into the list
template<class T>
bool LinkedList<T>::insertNode(Node<T>* a) {
    if (length == 0) {
        head = a;
        tail = a;
        length++;
    }
    else {
        tail->setNext(a);
        tail = a;
        length++;
        collisions++;
    }
    return true;
}

//The removeNode function removes a node from the list
template<class T>
bool LinkedList<T>::removeNode(Node<T>* a) {
    Node<T>* pWalk = head;
    if (pWalk == NULL)
    {
        return false;
    }
    if (pWalk->getItem() == a->getItem())
    {
        head = pWalk->getNext();
        delete pWalk;
        length--;
        return true;
    }
    else
    {
        while (pWalk->getNext() != NULL)
        {
            if (pWalk->getNext()->getItem() == a->getItem())
            {
                Node<T>* deleted = pWalk->getNext();
                pWalk->setNext(pWalk->getNext()->getNext());
                delete deleted;
                collisions--;
                length--;
                return true;
            }
            pWalk = pWalk->getNext();
        }
        return false;
    }
}

//The searchNode function searches for a node in a list and return the item
template<class T>
bool LinkedList<T>::searchNode(Node<T>* a, T& returnedItem) {
    Node<T>* pWalk = head;
    while (pWalk)
    {
        if (pWalk->getItem() == a->getItem())
        {
            returnedItem = pWalk->getItem();
            return true;
        }
        pWalk = pWalk->getNext();
    }
    return false;
}

//The showContents function shows the items in the list
template<class T>
void LinkedList<T>::showContents() {
    Node<T>* pWalk = head;
    while (pWalk) {
        std::cout << pWalk->getItem() << " - ";

        pWalk = pWalk->getNext();
    }
}

//The showContents function inputs the items into the file
template<class T>
void LinkedList<T>::showContentsinFile(ofstream& filename){
    Node<T>* pWalk = head;
    while (pWalk) {
        filename << pWalk->getItem() << " - ";
        pWalk = pWalk->getNext();
    }
}