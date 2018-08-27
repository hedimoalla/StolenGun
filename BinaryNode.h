// Node for a binary tree
// Modified by: Team #9

#ifndef _BINARY_NODE
#define _BINARY_NODE

#include <string>

using namespace std;


template<class ItemType>
class BinaryNode
{
private:
	ItemType*              item;         // Data portion
	BinaryNode<ItemType>* leftPtr;		// Pointer to left child
	BinaryNode<ItemType>* rightPtr;		// Pointer to right child
	std::string key;
public:
	// constructors
	BinaryNode() { item = 0; leftPtr = 0; rightPtr = 0; key = ""; }
	BinaryNode(ItemType* anItem, std::string k)	{ item = anItem; key = k; leftPtr = 0; rightPtr = 0; }
	BinaryNode(ItemType* anItem,
		std::string k,
		BinaryNode<ItemType>* left,
		BinaryNode<ItemType>* right) {
		item = anItem; key = k; leftPtr = left; rightPtr = right;
	}
	// mutators
	void setItem(ItemType* anItem) { item = anItem; }
	void setLeftPtr(BinaryNode<ItemType>* left) { leftPtr = left; }
	void setRightPtr(BinaryNode<ItemType>* right) { rightPtr = right; }
	void setKey(std::string k){ key = k; }
	// accessors
	ItemType* getItem() const	 { return item; }
	BinaryNode<ItemType>* getLeftPtr() const  { return leftPtr; }
	BinaryNode<ItemType>* getRightPtr() const { return rightPtr; }
	std::string getKey() const { return key; }
	bool isLeaf() const { return (leftPtr == 0 && rightPtr == 0); }
};

#endif
