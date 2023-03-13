// Music In-Memory Storage and Lookup System
// Binary tree abstract base class

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"

template<class ItemType>
class BinaryTree
{
protected:
    BinaryNode<ItemType>* rootPtr;		// ptr to root node
    int count;							// number of nodes in tree

public:
    // constructors
    BinaryTree() { rootPtr = 0; count = 0; }
    BinaryTree(const BinaryTree<ItemType>& tree) { rootPtr = clone(tree.rootPtr); count = tree.count; }
    virtual ~BinaryTree() { destroyTree(rootPtr); }

    // common functions for all binary trees
    bool isEmpty() const { return count == 0; }
    int getCount() const { return count; }
    void clear() { destroyTree(rootPtr); rootPtr = 0; count = 0; }
    void preOrder(void visit(ItemType&)) const { _preorder(visit, rootPtr); }
    void inOrder(void visit(ItemType&)) const { _inorder(visit, rootPtr); }
    void postOrder(void visit(ItemType&)) const { _postorder(visit, rootPtr); }
    void printTree(void visit(ItemType&, int)) const { _printTree(visit, rootPtr, 1); }

    // abstract functions to be implemented by derived class
    virtual bool insert(const ItemType& newData) = 0;
    //virtual bool remove(const ItemType &data) = 0;
    //virtual bool search(const ItemType &target, ItemType & returnedItem) const = 0;

private:
    // delete all nodes from the tree
    void destroyTree(BinaryNode<ItemType>* nodePtr);

    // internal traverse
    void _preorder(void visit(ItemType&), BinaryNode<ItemType>* nodePtr) const;
    void _inorder(void visit(ItemType&), BinaryNode<ItemType>* nodePtr) const;
    void _postorder(void visit(ItemType&), BinaryNode<ItemType>* nodePtr) const;
    void _printTree(void visit(ItemType&, int), BinaryNode<ItemType>* nodePtr, int level) const;

    //clone a tree
    BinaryNode<ItemType>* clone(BinaryNode<ItemType>* nodePtr) const;
};

//Destroy the entire tree
template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
    if (nodePtr) // != NULL
    {
        destroyTree(nodePtr->getLeftPtr());
        destroyTree(nodePtr->getRightPtr());
        //cout << "DEBUG - Destructor: Now deleting " << nodePtr->getItem().getName() << endl;
        delete nodePtr;
    }
}

//Preorder Traversal
template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType&), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr) // != NULL
    {
        ItemType item = nodePtr->getItem();
        visit(item);
        _preorder(visit, nodePtr->getLeftPtr());
        _preorder(visit, nodePtr->getRightPtr());
    }
}

//Inorder Traversal
template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType&), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr) // != NULL
    {
        ItemType item = nodePtr->getItem();
        _inorder(visit, nodePtr->getLeftPtr());
        visit(item);
        _inorder(visit, nodePtr->getRightPtr());
    }
}

//Postorder Traversal
template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType&), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr) // != NULL
    {
        ItemType item = nodePtr->getItem();
        _postorder(visit, nodePtr->getLeftPtr());
        _postorder(visit, nodePtr->getRightPtr());
        visit(item);
    }
}

//Prints tree as an indented list
template<class ItemType>
void BinaryTree<ItemType>::_printTree(void visit(ItemType&, int), BinaryNode<ItemType>* nodePtr, int level) const
{
    if (nodePtr)
    {
        ItemType item = nodePtr->getItem();
        visit(item, level);
        _printTree(visit, nodePtr->getRightPtr(), level + 1);
        _printTree(visit, nodePtr->getLeftPtr(), level + 1);
    }
}

//Clone a tree
template<class ItemType>
BinaryNode<ItemType> *BinaryTree<ItemType>::clone(BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr == NULL)
        return NULL;
    BinaryNode<ItemType>* newNode = new BinaryNode<ItemType>(nodePtr->getItem());
    newNode->setLeftPtr(clone(nodePtr->getLeftPtr()));
    newNode->setRightPtr(clone(nodePtr->getRightPtr()));
    return newNode;
}
#endif

