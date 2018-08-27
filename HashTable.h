/*
	HASH TABLE IMPLEMENTATION
*/

#ifndef HashTable_H_INCLUDED
#define HashTable_H_INCLUDED

#include "OverFlowList.h"
#include "StolenGun.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
//#include <cstring>
#define PRIME1 541
#define PRIME2 659
#define BUCKET_SIZE 3
#define TABLE_SIZE 31
using namespace std;

template<typename T>
void doNothing(T* nothing) {}

template<class T>
struct Table_Nodes
{
	string key;
	T* Data;
	Table_Nodes() { key = ""; Data = NULL; }
	~Table_Nodes() { if (Data != NULL) delete Data; }
};

template<class T>
class Hash_Buckets
{
private:
	int count;
	Table_Nodes<T>* bucket = NULL;
public:
	//Constructor
	Hash_Buckets() { count = 0; }
	//Destructor
	~Hash_Buckets()
	{
		if (bucket != NULL)
			delete[] bucket;
	}

	//insert Bucket Function
	bool insertBucket(T* item, string key);

	//delete Node Function
	bool deleteBucket(string key);

	//getter//
	int getCount() { return count; }
	Table_Nodes<T>* getBucket() { return bucket; }
};

template<class T>
class HashTable
{
private:
	int rejected = 0;
	int table_size;
	Hash_Buckets<T>* hash_table;
	OverFlowList<T>* overFlown;
	int _hashing(string key); //ditto. overloading with string key as argument.
	void _insert_OverFlowList(T* item, string key);


public:

	//Constructor//
	HashTable(int n) { table_size = n; hash_table = new Hash_Buckets<T>[table_size]; overFlown = NULL; }

	HashTable()      { table_size = TABLE_SIZE; hash_table = new Hash_Buckets<T>[table_size]; overFlown = NULL; }
	///////////////

	//Destructor//
	~HashTable() { delete[] hash_table; if (overFlown != NULL) delete overFlown; }
	//////////////

	//Get the overFlown list//
	OverFlowList<T>* getOverFlowList() { return overFlown; }
	/////////////////////////

	int getTableSize() { return table_size; }

	void insert(T* item, string key);

	void displayTable(void visit(T* item));   //This function display the hash table

	void displayList(void visit(T* item));

	Hash_Buckets<T>* getHashTable() { return hash_table; } //This function return the hash_table pointer;

	bool search_Item(string key, void visit(T*)); //This Function search an Item with key, and visits it. Return boolean of whether it is found or not

	bool search_Item(string key, T*& foundItem);  //Instead of visit item, return item to second argument.

	void display_Statistics();

	bool deleteNode(string key);

};

//====================Hash_Buckets Functions=======================//

template<class T>
bool Hash_Buckets<T>::insertBucket(T* item, string key)
{
	bool success = false;
	if (count == 0)
		bucket = new Table_Nodes<T>[BUCKET_SIZE];

	if (count<BUCKET_SIZE)
	{
		bucket[count].Data = item;
		bucket[count].key = key;
		count++;
		success = true;
	}
	return success;
}

template<class T>
bool Hash_Buckets<T>::deleteBucket(string key)
{
	bool success = false;

	int i = 0;
	while (i<count && key != bucket[i].key)
		i++;
	if (i<count && key == bucket[i].key)  //if matched
	{
		delete bucket[i].Data;    //delete Data
		int j;

		for (j = i; j < count - 1; j++) //
		{
			bucket[j] = bucket[j + 1];
		}
		bucket[j].Data = NULL;
		bucket[j].key = "";
		count--;

		success = true;
	}


	return success;
}


//=======================Hash Function================================//
template<class T>
int HashTable<T>::_hashing(string key)
{
	int intKey = 0;

	for (unsigned int i = 0; i<key.length(); i++)
		intKey += (i + 1)*(i + 1)*(int)key[i];

	return (PRIME1 * intKey + PRIME2) % table_size;
}



template<class T>
void HashTable<T>::insert(T* item, string key)
{
	int index;
	index = _hashing(key);


	if (!search_Item(key, doNothing))       //if there is no duplication
	{
		if (!hash_table[index].insertBucket(item, key))  //if cannot insert into bucket (full)
			_insert_OverFlowList(item, key);              //Insert to the overFlown list
	}

	else
		cout << "Error: a duplicated key is encountered when inserting an item\n"
		<< "Termination of Program and further investigation is advised!\n";
}

template<class T>
void HashTable<T>::displayTable(void visit(T* item))
{
	for (int i = 0; i< table_size; i++)
	{
		cout << "Index " << i << ": ";
		for (int j = 0; j<hash_table[i].getCount(); j++)
		{	
			if (j == 0)
				visit(hash_table[i].getBucket()[j].Data);
			if (j > 0){				// means not first one in bucket
				cout << "\t\t";  
				visit(hash_table[i].getBucket()[j].Data);
			}
			cout << endl;
		}
		if (hash_table[i].getCount() == 0)
			cout << "//Empty bucket\n\n";
	}
}


template <class T>
void HashTable<T>::displayList(void visit(T* item)){
	for (int i = 0; i< table_size; i++)
	{
		for (int j = 0; j<hash_table[i].getCount(); j++)
		{
			visit(hash_table[i].getBucket()[j].Data);
			cout << endl;
		}
		
	}
}

template<class T>
bool HashTable<T>::search_Item(string key, void visit(T*))
{
	bool found = false;

	int index = _hashing(key);
	int i = 0;
	while (i<hash_table[index].getCount() && key != hash_table[index].getBucket()[i].key)
		i++;

	if (i<hash_table[index].getCount() && key == hash_table[index].getBucket()[i].key)
	{
		visit(hash_table[index].getBucket()[i].Data);
		found = true;
	}
	else    //If not found in the bucket, find in the overflow list
	{
		OverFlowList<T>* overFlownPtr = overFlown;

		while (overFlownPtr != NULL && found == false)
			if (overFlownPtr->getKey() == key)
			{
				visit(overFlownPtr->getItem());
				
				found = true;
			}
			else
				overFlownPtr = overFlownPtr->getNext();
	}

	return found;
}

template<class T>
bool HashTable<T>::search_Item(string key, T*& foundItem)
{
	bool found = false;

	int index = _hashing(key);
	int i = 0;
	while (i<hash_table[index].getCount() && key != hash_table[index].getBucket()[i].key)
		i++;

	if (i<hash_table[index].getCount() && key == hash_table[index].getBucket()[i].key)
	{
		foundItem = hash_table[index].getBucket()[i].Data;
		found = true;
	}
	else    //If not found in the bucket, find in the overflow list
	{
		OverFlowList<T>* overFlownPtr = overFlown;
		while (overFlownPtr != NULL && found == false)
			if (overFlownPtr->getKey() == key)
			{
				foundItem = hash_table[index].getBucket()[i].Data;
				
				found = true;
			}
			else
				overFlownPtr = overFlownPtr->getNext();
	}

	return found;
}


template<class T>
void HashTable<T>::display_Statistics()
{
	int occupied = 0;
	int collision = 0;
	int emptyBucket = 0;
	int fullBucket = 0;
	int itemCount = 0;

	for (int i = 0; i<table_size; i++)
		switch (hash_table[i].getCount())
	{
		case 0:
			emptyBucket++;
			break;
		case 1:
		{
			itemCount += 1;
			occupied++;
			break;
		}
		case 2:
		{
			itemCount += 2;
			occupied++;
			collision += 1;
			break;
		}
		case 3:
		{
			itemCount += 3;
			occupied++;
			collision += 2;
			fullBucket++;
			break;
		}
		default:
			break;
	}

	cout << "Statistics:\n"
		<< "\nOccupied Buckets: "  << setw(9) << occupied
		<< "\nCollisions: "  << setw(15) << collision
		<< "\nEmpty Buckets: "  << setw(12) << emptyBucket
		<< "\nFull Buckets: "  << setw(13) << fullBucket
		<< "\nRejected Items: " << setw(11) << rejected
		<< "\nLoad Factor: "  << setw(14) << setprecision(3) << 100 * (double)occupied / (double)table_size << "%"
		<< "\nAverage Items: "  << setw(12) << (double)itemCount / (double)occupied << "\n\n";
		

	// display table
	for (int i = 0; i< table_size; i++)
	{
		cout << "Bucket" << right << setw(3) << i << ":\t";
		if (hash_table[i].getCount() != 0){
			for (int j = 0; j < hash_table[i].getCount(); j++)
				cout << "|X| ";
		}
		cout << endl;
		
	}
}

template<class T>
void HashTable<T>::_insert_OverFlowList(T* item, string key)
{
	OverFlowList<T>* newPtr = new OverFlowList<T>(item, key);
	rejected++;
	if (overFlown == NULL)
		overFlown = newPtr;
	else
	{
		OverFlowList<T>* nodePtr = overFlown;
		OverFlowList<T>* prePtr = nodePtr;
		nodePtr = overFlown->getNext();

		while (nodePtr != NULL)
		{
			prePtr = nodePtr;
			nodePtr = nodePtr->getNext();
		}
		prePtr->setNext(newPtr);
	}
}

template<class T>
bool HashTable<T>::deleteNode(string key)
{
	int index = _hashing(key);

	bool success = hash_table[index].deleteBucket(key);

	if (!success && overFlown != NULL)                   //search the overflowlist if not successful
	{
		OverFlowList<T>* overFlownPtr = overFlown;
		if (overFlownPtr->getKey() == key)
		{
			overFlown = overFlownPtr->getNext();
			delete overFlownPtr->getItem();
			overFlownPtr->setNext(NULL);
			delete overFlownPtr;
			success = true;
		}
		else
		{
			OverFlowList<T>* prePtr = overFlownPtr;
			overFlownPtr = overFlownPtr->getNext();
			while (overFlownPtr != NULL && overFlownPtr->getKey() != key)
			{
				prePtr = overFlownPtr;
				overFlownPtr = overFlownPtr->getNext();
			}
			if (overFlownPtr->getKey() == key)
			{
				prePtr->setNext(overFlownPtr->getNext());
				delete overFlownPtr->getItem();
				overFlownPtr->setNext(NULL);
				delete overFlownPtr;
				success = true;
			}
		}
		rejected--;
	}

	return success;
	
}

#endif // HashTable_H_INCLUDED
