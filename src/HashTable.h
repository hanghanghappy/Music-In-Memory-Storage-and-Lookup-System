// Music In-Memory Storage and Lookup System
/*
HashTable class - class that implements LinkedList
creates a HashTable of linkedlists
*/
#ifndef _HASH_TABLE
#define _HASH_TABLE

#include <string>
#include "LinkedList.cpp"
#include <fstream>

template <class ItemType>
class HashTable {
private:
    LinkedList<ItemType>* hashAry;
    int hashSize;
    int count;
public:
    //Constructor
    HashTable() { count = 0; hashSize = 128; hashAry = new LinkedList<ItemType>[hashSize]; }
    HashTable(int a) { count = 0; hashSize = a; hashAry = new LinkedList<ItemType>[hashSize]; }
    //Destructor
    ~HashTable() { delete[] hashAry; }

    //Getters
    int getCount() { return count; }
    int getHashSize() { return hashSize; }
    double getLoadFactor() { return 100.0 * count / hashSize; }

    //Setter
    void setHashSize(int a) { hashSize = a; }
    
    //Hash Table operations
    bool insert(ItemType& a, string key);
    bool remove(ItemType& a, string key);
    int hash(string key);
    bool search(ItemType& a, string key);
    void traverseAll();
    void traverseFile(ofstream& filename);
    void statistic();

};

#endif