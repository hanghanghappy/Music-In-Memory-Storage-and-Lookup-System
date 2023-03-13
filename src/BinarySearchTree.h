// Music In-Memory Storage and Lookup System
// Binary Search Tree ADT

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
public:
    // insert a node at the correct location
    bool insert(const ItemType& item);
    // remove a node if found
    bool remove(const ItemType &item);
    // find a target node
    bool search(const ItemType& target, ItemType& returnedItem) const;
    //bool searchmultiple(const ItemType& target, ItemType& returnedItem, BinarySearchTree& returnedList) const;
    // find the smallest node
    bool findSmallest(ItemType& returnedItem) const;
    // find the largest node
    bool findLargest(ItemType& returnedItem) const;
    // find the root node
    bool findRoot(ItemType& returnedItem) const;

    //int duplicates(const ItemType& target, ItemType& returnedItem) const;
private:
    // internal insert node: insert newNode in nodePtr subtree
    BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);

    // search for target node
    BinaryNode<ItemType>* _search(BinaryNode<ItemType>* treePtr, const ItemType& target) const;

    // find the smallest node
    BinaryNode<ItemType>* _findSmallest(BinaryNode<ItemType>* nodePtr, ItemType& smallest) const;

    // find the largest node
    BinaryNode<ItemType>* _findLargest(BinaryNode<ItemType>* nodePtr, ItemType& largest) const;

    // find the root node
    BinaryNode<ItemType>* _findRoot(BinaryNode<ItemType>* nodePtr, ItemType& root) const;

    // internal remove node: locate and delete target node under nodePtr subtree
    BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool &success);

    // delete target node from tree, called by internal remove node
    BinaryNode<ItemType>* _removeNode(BinaryNode<ItemType>* targetNodePtr);

    // remove the leftmost node in the left subtree of nodePtr
    BinaryNode<ItemType>* _removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType &successor);

};


///////////////////////// public function definitions ///////////////////////////
//Wrapper for _insert - Inserting items within a tree
template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType& newEntry)
{
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
    this->rootPtr = _insert(this->rootPtr, newNodePtr);
    this->count++;
    return true;
}

//Wrapper for _remove - Removing an item within a tree
template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType& item)
{
    bool success = false;
    this->rootPtr = _remove(this->rootPtr, item, success);
    if (success == true)
        this->count--;
    return success;
}

//Finding the smallest, which is the leftmost leaf (wrapper function)
template<class ItemType>
bool BinarySearchTree<ItemType>::findSmallest(ItemType& returnedItem) const
{
    BinaryNode<ItemType>* temp = nullptr;
    temp = _findSmallest(this->rootPtr, returnedItem);
    if (temp) // != NULL
        return true;
    return false;
}

//Finding the biggest, which is the rightmost leaf (wrapper function)
template<class ItemType>
bool BinarySearchTree<ItemType>::findLargest(ItemType& returnedItem) const
{
    BinaryNode<ItemType>* temp = nullptr;
    temp = _findLargest(this->rootPtr, returnedItem);
    if (temp) // != NULL
        return true;
    return false;
}

//Finding the root of the tree (wrapper function)
template<class ItemType>
bool BinarySearchTree<ItemType>::findRoot(ItemType& returnedItem) const
{
    BinaryNode<ItemType>* temp = nullptr;
    temp = _findRoot(this->rootPtr, returnedItem);
    if (temp) // != NULL
        return true;
    return false;
}

//Wrapper for _search
// - it calls the private _search function that returns a Node pointer or NULL
// - if found, it copies data from that node and sends it back to the caller 
//   via the output parameter, and returns true, otherwise it returns false.
template<class ItemType>
bool BinarySearchTree<ItemType>::search(const ItemType& anEntry, ItemType& returnedItem) const
{
    BinaryNode<ItemType>* temp = nullptr;
    temp = _search(this->rootPtr, anEntry);
    if (temp)
    {
        returnedItem = temp->getItem();
        return true;
    }
    else
    {
        return false;
    }
}

//////////////////////////// private functions ////////////////////////////////////////////

//Implementation of the insert operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
    BinaryNode<ItemType>* newNodePtr)
{
    BinaryNode<ItemType>* pWalk = nodePtr, * parent = nullptr;

    if (!nodePtr) // == NULL
    {
        nodePtr = newNodePtr;
        return nodePtr;
    }
    else
    {
        while (pWalk) // != NULL
        {
            parent = pWalk;
            if (pWalk->getItem() > newNodePtr->getItem())
                pWalk = pWalk->getLeftPtr();
            else
                pWalk = pWalk->getRightPtr();
        }
        if (parent->getItem() > newNodePtr->getItem())
            parent->setLeftPtr(newNodePtr);
        else
            parent->setRightPtr(newNodePtr);
    }

    return nodePtr;
}

//Implementation for the search operation
// - return NULL if target not found, otherwise
// - returns a pointer to the node that matched the target
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_search(BinaryNode<ItemType>* nodePtr,
    const ItemType& target) const
{
    BinaryNode<ItemType>* found = nullptr;
    if (!nodePtr)
    {
        return found;
    }
    if (nodePtr->getItem() == target)
    {
        return nodePtr;
    }
    if (nodePtr->getItem() < target)
    {
        return _search(nodePtr->getRightPtr(), target);
    }
    else
    {
        return _search(nodePtr->getLeftPtr(), target);
    }

    return found;
}

//Implementation to find the smallest: recursive
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_findSmallest(BinaryNode<ItemType>* nodePtr, ItemType& smallest) const
{
    BinaryNode<ItemType>* current = nodePtr;
    if (current->getLeftPtr())
    {
        current = current->getLeftPtr();
        _findSmallest(current, smallest);
    }
    else
    {
        smallest = current->getItem();
        return current;
    }
    return current;
}

//Implementation to find the largest: recursive
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_findLargest(BinaryNode<ItemType>* nodePtr, ItemType& biggest) const
{
    BinaryNode<ItemType>* current = nodePtr;
    if (current->getRightPtr())
    {
        current = current->getRightPtr();
        _findLargest(current, biggest);
    }
    else
    {
        biggest = current->getItem();
        return current;
    }
    return current;
}

//Implementation to find the root
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_findRoot(BinaryNode<ItemType>* nodePtr, ItemType& root) const
{
    BinaryNode<ItemType>* current = nodePtr;
    root = current->getItem();
    return current;
}

//Implementation for the remove operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool& success)
{
    if (nodePtr == 0)
    {
        success = false;
        return 0;
    }
    if (nodePtr->getItem() > target)
    {
        nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
    }
    else if (nodePtr->getItem() < target)
    {
        nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
    }
    else
    {
        nodePtr = _removeNode(nodePtr);
        success = true;
    }
    return nodePtr;
}

//Implementation for the removeNode operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_removeNode(BinaryNode<ItemType>* targetNodePtr)
{
    if (targetNodePtr->isLeaf())
    {
        delete targetNodePtr;
        targetNodePtr = 0;
        return targetNodePtr;
    }
    else if (targetNodePtr->getLeftPtr() == 0)
    {
        BinaryNode<ItemType>* temp = targetNodePtr->getRightPtr();
        delete targetNodePtr;
        targetNodePtr = 0;
        return temp;
    }
    else if (targetNodePtr->getRightPtr() == 0)
    {
        BinaryNode<ItemType>* temp = targetNodePtr->getLeftPtr();
        delete targetNodePtr;
        targetNodePtr = 0;
        return temp;
    }
    else
    {
        ItemType successor;
        targetNodePtr->setRightPtr(_removeLeftmostNode(targetNodePtr->getRightPtr(), successor));
        targetNodePtr->setItem(successor);
        return targetNodePtr;
    }
}

//Implementation for the removeLeftmostNode operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType& successor)
{
    if (nodePtr->getLeftPtr() == 0)
    {
        successor = nodePtr->getItem();
        return _removeNode(nodePtr);
    }
    else
    {
        nodePtr->setLeftPtr(_removeLeftmostNode(nodePtr->getLeftPtr(), successor));
        return nodePtr;
    }
}
#endif
