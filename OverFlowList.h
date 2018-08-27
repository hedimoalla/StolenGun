/********************************************
	Implementation of a LinkedList that
	will hold the overflown items
*/

#ifndef OVERFLOWLIST_H_INCLUDED
#define OVERFLOWLIST_H_INCLUDED

#include <string>

using namespace std;

template<class T>
class OverFlowList
{
private:
	string key;
	T* item;
	OverFlowList* next;

public:
	//Constructor//
	OverFlowList(){ next = NULL; }
	OverFlowList(T* newItem, string k) { item = newItem; key = k; next = NULL; }
	///////////////

	//Destructor//
	~OverFlowList()
	{
		if (next != NULL)
			delete next;
	}
	///////////////

	//Getter & Setter//
	void setNext(OverFlowList* nextPtr)  { next = nextPtr; }
	void setItem(T* newItem) { item = newItem; }
	void setKey(string k) { key = k; }

	T* getItem() { return item; }
	OverFlowList* getNext() { return next; }
	string getKey() { return key; }
	///////////////////

};

#endif // OVERFLOWLIST_H_INCLUDED
