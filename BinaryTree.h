// Binary tree abstract base class
// Modified by: Team #9

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include <string>
#include <fstream>
#include "BinaryNode.h"

using namespace std;

template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree
	int level = 0;
public:
	// "admin" functions
	BinaryTree() { rootPtr = 0; count = 0; }
	BinaryTree(const BinaryTree<ItemType> & tree){ rootPtr = copyTree(tree.rootPtr); count = tree.getCount(); }
	virtual ~BinaryTree() { destroyTree(this->rootPtr); }
	BinaryTree & operator = (const BinaryTree & sourceTree);
	int getCount() const { return count; }
	BinaryNode<ItemType>* getRootPtr() const { return rootPtr; }
	// common functions for all binary trees
	bool isEmpty() const	{ return count == 0; }
	int size() const	    { return count; }
	void clear()			{ destroyTree(rootPtr); rootPtr = 0; count = 0; }
	void preOrder(void visit(ItemType *)) const { _preorder(visit, rootPtr); }
	void inOrder(void visit(ItemType *)) const  { _inorder(visit, rootPtr); }
	void postOrder(void visit(ItemType *)) const{ _postorder(visit, rootPtr); }
	void displayTree(void visit(ItemType *)) const{ _displayTree(visit, rootPtr, level); }
	void outputFile(ofstream & outFile, void writeItem(ItemType*, ofstream&)) { _outputFile(writeItem, outFile, rootPtr); };


private:
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);

	// internal traverse
	void _preorder(void visit(ItemType *), BinaryNode<ItemType>* nodePtr) const;
	void _inorder(void visit(ItemType *), BinaryNode<ItemType>* nodePtr) const;
	void _postorder(void visit(ItemType *), BinaryNode<ItemType>* nodePtr) const;
	void _displayTree(void visit(ItemType *), BinaryNode<ItemType>* nodePtr, int level) const;
	void _outputFile(void writeItem(ItemType*, ofstream&), ofstream & outFile, BinaryNode<ItemType>* nodePtr) const;
};

//////////////////////////////////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr)
{
	BinaryNode<ItemType>* newNodePtr = 0;
	if (nodePtr != 0)
	{
		/* ************************************************************************
		It is not necessary to add the 0, 0 for the default constructor for the
		BinaryNode will take care of it.
		*************************************************************************/
		newNodePtr = new BinaryNode<ItemType>(nodePtr->getItem(), 0, 0);
		newNodePtr->setLeftPtr(copyTree(nodePtr->getLeftPtr()));
		newNodePtr->setRightPtr(copyTree(nodePtr->getRightPtr()));
	}

	return newNodePtr;
}

template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr != 0)
	{
		//postOrder traversal to delete children before parents in a recursion
		destroyTree(nodePtr->getLeftPtr());
		destroyTree(nodePtr->getRightPtr());
		delete nodePtr;
	}
}

//////////////////////////////////////////////////////////////////////////////

template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType *), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType* item = nodePtr->getItem();
		visit(item);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	}
}

template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType *), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType* item = nodePtr->getItem();
		_inorder(visit, nodePtr->getLeftPtr());
		visit(item); //inOrder
		_inorder(visit, nodePtr->getRightPtr());
	}
}

template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType *), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType* item = nodePtr->getItem();
		_postorder(visit, nodePtr->getLeftPtr());
		_postorder(visit, nodePtr->getRightPtr());
		visit(item); //postOrder
	}
}

template<class ItemType>
BinaryTree<ItemType> & BinaryTree<ItemType>::operator=(const BinaryTree<ItemType> & sourceTree)
{
	this->clear();
	this.rootPtr = copyTree(sourceTree.rootPtr);
	this.count = sourceTree.count;
	return *this;
}

// function to display the tree as indented
// this function uses recursion
template<class ItemType>
void BinaryTree<ItemType>::_displayTree(void visit(ItemType *), BinaryNode<ItemType>* nodePtr, int level = 0) const
{
	if (nodePtr != 0) {
		_displayTree(visit, nodePtr->getRightPtr(), level + 1);
		ItemType* item = nodePtr->getItem();
		cout << "\t";
		for (int i = 0; i < level; i++){
			cout << "\t";
		}
		cout << level + 1 << ". ";
		visit(item);
		cout << endl;
		_displayTree(visit, nodePtr->getLeftPtr(), level + 1);
	
	}
}

///////////////////////////output File option///////////////////////////////////////
template<class ItemType>
void BinaryTree<ItemType>::_outputFile(void writeItem(ItemType*, ofstream&), ofstream & outFile, BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		_outputFile(writeItem, outFile, nodePtr->getLeftPtr());
		ItemType* item = nodePtr->getItem();
		writeItem(item, outFile);
		_outputFile(writeItem, outFile, nodePtr->getRightPtr());
	}
}


#endif
