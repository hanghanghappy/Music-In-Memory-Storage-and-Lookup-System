// Music In-Memory Storage and Lookup System
/*
HashTable class - class that implements LinkedList
creates a HashTable of linkedlists
*/
using namespace std;
#include "HashTable.h"
#include <string>
#include <fstream>
#include <iostream>

//The insert function inserts an item into the list with the hash insert chaining method
template <class ItemType>
bool HashTable<ItemType>::insert(ItemType& a, string key) {
    int ind = hash(key);
    LinkedList<ItemType>* curList = &hashAry[ind];
    Node<ItemType>* the = new Node<ItemType>(a);
    count++;
    return curList->insertNode(the);
}

//The remove function remove an item from the list with the hash delete chaining method
template <class ItemType>
bool HashTable<ItemType>::remove(ItemType& a, string key) {
    int ind = hash(key);
    LinkedList<ItemType>* curList = &hashAry[ind];
    Node<ItemType>* the = new Node<ItemType>(a);
    if (curList->removeNode(the))
    {
        count--;
        return true;
    }
    else
        return false;
}

//A simple hash function
template <class ItemType>
int HashTable<ItemType>::hash(string key) {
    int ind = 0;
    for (int i = 0; i < key[i]; i++) {
        ind += (key[i] * (i + 1));
    }
    return ind % hashSize;
}

//The search function searches for an item in the list and return it
template <class ItemType>
bool HashTable<ItemType>::search(ItemType& a, string key) {
    int ind = hash(key);
    LinkedList<ItemType>* curList = &hashAry[ind];
    Node<ItemType>* the = new Node<ItemType>(a);
    ItemType returnedItem;
    if (curList->searchNode(the, returnedItem))
    {
        a = returnedItem;
        return true;
    }
    else
        return false;
}

//The traverseAll function traverses all the items in the list and output them
template <class ItemType>
void HashTable<ItemType>::traverseAll() {
    for (int i = 0; i < hashSize; i++) {
        cout << i << ": ";
        LinkedList<ItemType>* curList = &hashAry[i];

        if (curList->getLength()) {
            cout << "Found " << curList->getLength() << " items: ";
            curList->showContents();
        }
        else {
            cout << curList->getLength() << " ";
        }
        cout << endl;
    }
}

//The traverseFile function traverses all the items in the list and output them into the file
template <class ItemType>
void HashTable<ItemType>::traverseFile(ofstream& filename) {
    for (int i = 0; i < hashSize; i++) {
        filename << i << ": ";
        LinkedList<ItemType>* curList = &hashAry[i];

        if (curList->getLength()) {
            filename << "Found " << curList->getLength() << " items: ";
            curList->showContentsinFile(filename);
        }
        else {
            filename << curList->getLength() << " ";
        }
        filename << endl;
    }
}

//The statistic function outputs the statistics of the hash list
template <class ItemType>
void HashTable<ItemType>::statistic() {
    LinkedList<ItemType>* curList = &hashAry[0];
    int longest;
    int longestlists = 0;
    int totalcollisions = 0;
    for (int i = 0; i < hashSize; i++)
    {
        totalcollisions = totalcollisions + curList->getCollisions();
        curList = &hashAry[i + 1];
    }
    curList = &hashAry[0];
    for (int i = 0; i < hashSize; i++) {
        LinkedList<ItemType>* nextList = &hashAry[i + 1];
        if (curList->getLength() <= nextList->getLength())
        {
            curList = nextList;
        }
    }
    longest = curList->getLength();
    curList = &hashAry[0];
    for (int i = 0; i < hashSize; i++) {
        if (curList->getLength() == longest)
        {
            longestlists++;
        }
        curList = &hashAry[i + 1];
    }
    cout << "===================Hash Table Statistics===================\n";
    cout << "Load Factor:                    " << getLoadFactor() << endl;
    cout << "Number of Collisions:           " << totalcollisions << endl;
    cout << "Length of Longest Linked List:  " << longest << endl;
    cout << "Number of Longest Linked Lists: " << longestlists << endl;
    cout << "===========================================================\n";
}
