// Binary Search Tree ADT
// Modified by: Team #9
 

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include <string>
#include "BinaryTree.h"
using namespace std;


template<class ItemType>
class BinarySearchTree : public BinaryTree <ItemType>
{
private:
	using BinaryTree<ItemType>::rootPtr;
	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);

	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, std::string key, bool & success, ItemType * comparePtr);

	// delete target node from tree, called by internal remove node
	BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);

	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType * successor);

	// search for target node
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, std::string target) const;

	bool findSecKey(BinaryNode<ItemType>* nodePtr, std::string target, void visit(ItemType*)) const;

public:
	// insert a node at the correct location
	bool insert(std::string key, ItemType * newData);
	// remove a node if found
	bool remove(std::string key, ItemType * comparePtr);
	// find a target node
	bool search_Item(std::string key, ItemType* & returnedItem) const;

	bool search_Item(std::string key, void visit(ItemType*)) const;

};


///////////////////////// public function definitions ///////////////////////////

template<class ItemType>
bool BinarySearchTree<ItemType>::insert(std::string key, ItemType * newData)
{
	//create a new BinaryNode and initialize the node with new data
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newData, key);
	//call the _insert private function to act upon the current BinaryTree object
	rootPtr = _insert(rootPtr, newNodePtr);
	return true;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(std::string key, ItemType * comparePtr)
{
	bool isSuccessful = false;
	rootPtr = _remove(rootPtr, key, isSuccessful, comparePtr);
	return isSuccessful;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::search_Item(std::string key, ItemType* & returnedItem) const
{
	BinaryNode<ItemType>* found = findNode(this->rootPtr, key);
	if (found)
	{
		returnedItem = found->getItem();
		return true;
	}
	return false;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::search_Item(std::string key, void visit(ItemType*)) const
{
	BinaryNode<ItemType>* nodePtr = rootPtr;

	bool found = findSecKey(nodePtr, key, visit);

	return found;
}


//////////////////////////// private functions ////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
	BinaryNode<ItemType>* newNodePtr)
{
	//First nodePtr to be tested is always the rootPtr of the current BinaryTree Object

	if (nodePtr == 0)
		return newNodePtr;
	else
	{
		if (nodePtr->getKey() > newNodePtr->getKey())
			nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr));
		else
			nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr));
		return nodePtr;
	}
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr, std::string key, bool & success, ItemType * comparePtr)

{
	if (nodePtr == 0)
	{
		success = false;
		return 0;
	}
	if (nodePtr->getKey() > key)
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), key, success, comparePtr));
	else if (nodePtr->getKey() < key)
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), key, success, comparePtr));
	else
	{
		if (nodePtr->getItem() != comparePtr)
			nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), key, success, comparePtr));
		else
		{
			nodePtr = deleteNode(nodePtr);
			success = true;
		}
	}
	return nodePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr->isLeaf())
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0)
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else
	{
		ItemType* newNodeValue = NULL;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
	ItemType * successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		successor = nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}
}


template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr, std::string target) const
{
	if (nodePtr == 0)
		return 0;
	if (nodePtr->getKey() == target)
		return nodePtr;
	else if (nodePtr->getKey() > target)
		return findNode(nodePtr->getLeftPtr(), target);
	else
		return findNode(nodePtr->getRightPtr(), target);
}

template<class ItemType>
bool BinarySearchTree<ItemType>::findSecKey(BinaryNode<ItemType>* nodePtr, std::string target, void visit(ItemType*)) const
{
	bool found = false;

	if (nodePtr == 0)
		return found;  //empty tree
	if (nodePtr->getKey() == target)
	{
		visit(nodePtr->getItem());   //Like the diagram I drew, getItemPtr() should return a ptr of the data instead of the data
		found = true;
		// we still need to further traverse for duplicate.
		findSecKey(nodePtr->getRightPtr(), target, visit);  //Recursion. only right subtree can possibly contain duplicate key
		return found;
	}
	if (nodePtr->getKey() > target)
	{
		found = findSecKey(nodePtr->getLeftPtr(), target, visit);
		return found;
	}
	if (nodePtr->getKey() < target)
	{
		found = findSecKey(nodePtr->getRightPtr(), target, visit);
		return found;
	}
	return found;
}

#endif

