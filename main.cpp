/*************************************************************
                                                             *
	CIS 22C Team #09 project                                 *
	By: Hedi Moalla	- Derek Delacruz - Un Hou Chan           *
	                                                         *
	STOLEN GUNS DATABASE                                     *
	using Hash Table, Binary Search Trees, and linked lists  *
	                                                         *
	Description: This program is a database of stolen guns   *
															 *
	Date: 06/18/2015										 *
															 *
**************************************************************/


#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "BinarySearchTree.h"
#include "BinaryTree.h"
#include "BinaryNode.h"
#include "HashTable.h"
#include "StolenGun.h"

using namespace std;

// display header
void displayHeader(){
	cout << "  /\\______\n"
		<< "  \\  ==== --------/|\n"
		<< "   | ==== |________|========================================O\n"
		<< "  /    ___|-------|     |                                |\n"
		<< "  |   /\\ |              |         WELCOME TO THE         |\n"
		<< "  |   |_/               |          STOLEN GUNS           |\n"
		<< "  |   |         ________|            DATABASE            |________\n"
		<< "  |   |        |        |                                |        |\n"
		<< "  |___|        |        |________________________________|        |\n"
		<< "               |        \\###|                       |###/         |\n"
		<< "               |         \\##|                       |##/          |\n"
		<< "               |          \\#|                       |#/           |\n"
		<< "               |___________\\|                       |/____________|\n";
}
// display menu
void displayMenu()
{

	cout << endl;
	cout <<"\t\t     *****************************************\n"
		<< "\t\t     *                                       *\n"
		<< "\t\t     *         A - Add Data                  *\n"
		<< "\t\t     *                                       *\n"
		<< "\t\t     *         D - Delete Data               *\n"
		<< "\t\t     *                                       *\n"
		<< "\t\t     *         F - Search                    *\n"
		<< "\t\t     *                                       *\n"
		<< "\t\t     *         L - List data                 *\n"
		<< "\t\t     *                                       *\n"
		<< "\t\t     *         W - Write data to file        *\n"
		<< "\t\t     *                                       *\n"
		<< "\t\t     *         S - Statistics                *\n"
		<< "\t\t     *                                       *\n"
		<< "\t\t     *         Q - Quit                      *\n"
		<< "\t\t     *                                       *\n"
		<< "\t\t     *****************************************\n\n";

}

// display submenu in option L
void listMenu(){
	
	cout << "List Menu:\n\n";
	cout << "U: List unsorted data\n";
	cout << "S: Tree by Serial Number\n";
	cout << "P: Tree by Phone Number\n";
	cout << "I: Indented List\n";
	cout << "F: Sort by Serial number\n";
	cout << "J: Sort by Phone number\n";
	cout << "G: Preorder traversal by Serial number\n";
	cout << "H: Postorder traversal by Serial number\n";
	cout << "K: Preorder traversal by Phone number\n";
	cout << "L: Postorder traversal by Phone number\n";
	cout << "Q: Quit menu\n";
	cout << "Your choice: ";
}

// function to display gun
void displayGun(StolenGun* gun)
{
	cout << "Serial Number: " << gun->getSerial() << " Make: " << gun->getMake()
		<< " Model: " << gun->getModel() << " Caliber: " << gun->getCaliber()
		<< " Phone Number: " << gun->getPhoneNum() << endl;
}

// function to display gun
void displayGunIndented(StolenGun* gun)
{
	cout << "Serial Number: " << gun->getSerial() 
		<< " Phone Number: " << gun->getPhoneNum() << endl;
}

// function to display just the serial of the gun (for formatting purposes)
void displayGunSerial(StolenGun* gun)
{
	cout << gun->getSerial()<< endl;
}

// function to display the phone number corresponding to the gun
void displayGunPhone(StolenGun* gun)
{
	cout << gun->getPhoneNum() << endl;
}

// function to write data to file
void writeData(StolenGun * gun, ofstream & outFile)
{
	outFile << gun->getSerial() << ";" << gun->getMake()
		<< ";" << gun->getModel() << ";" << gun->getCaliber()
		<< ";" << gun->getPhoneNum() << ";" << endl;
}

bool iequals(const string& a, const string& b)
{
	unsigned int sz = a.size();
	if (b.size() != sz)
		return false;
	for (unsigned int i = 0; i < sz; ++i)
		if (tolower(a[i]) != tolower(b[i]))
			return false;
	return true;
}

// function to read content of the file
void readFile(BinarySearchTree<StolenGun>* tree1,BinarySearchTree<StolenGun>* tree2,
			HashTable<StolenGun>* gunTable, ifstream& inFile)
{
	StolenGun *gun = new StolenGun();
	string s = "";
	string b = "";
	string m = "";
	string c = "";
	string p = "";

	char tempChar;
	
	inFile.get(tempChar);
	while (tempChar != ';')
	{
		s += tempChar;
		inFile.get(tempChar);
	}

	//Brand//
	inFile.get(tempChar);
	while (tempChar != ';')
	{
		b += tempChar;
		inFile.get(tempChar);
	}

	//Model//
	inFile.get(tempChar);
	while (tempChar != ';')
	{
		m += tempChar;
		inFile.get(tempChar);
	}

	//Caliber//
	inFile.get(tempChar);
	while (tempChar != ';')
	{
		c += tempChar;
		inFile.get(tempChar);
	}

	//Phone Number//
	inFile.get(tempChar);
	while (tempChar != ';')
	{
		p += tempChar;
		inFile.get(tempChar);
	}

	gun->setSerial(s);					// set all variable in the gun object
	gun->setMake(b);
	gun->setModel(m);
	gun->setCaliber(c);
	gun->setPhoneNum(p);

	string key1 = gun->getSerial();		// assign serial to key1
	string key2 = gun->getPhoneNum();	// assign phoneNum to key2
	
	tree1->insert(key1, gun);			// insert gun in tree
	tree2->insert(key2, gun);
	gunTable->insert(gun, key1);		// insert gun in hashtable

	inFile.ignore();  //ignore '\n' character
}

int main()
{
	char choice;
	char selection;
	string make, model, caliber;
	string key1, key2;
	ofstream outFile;
	string outFileName;
	BinarySearchTree<StolenGun> *tree1 = new BinarySearchTree<StolenGun>();	// create a binary search tree of gun objects
	BinarySearchTree<StolenGun> *tree2 = new BinarySearchTree<StolenGun>(); // create a secondary binary search tree of gun objects
	HashTable<StolenGun> *gunTable = new HashTable<StolenGun>(); // create a hashtable of guns

	ifstream inFile;

	string fileName = "StolenGunDatabase.txt";					
	inFile.open(fileName);										// open file

	while (!inFile.eof())
		readFile(tree1, tree2, gunTable, inFile);
	displayHeader();
	displayMenu();
	do{
		cout << "\nChoose Option: ";
		cin >> choice;									// read the user's choice
		cin.sync();
		cout << endl;
		switch (tolower(choice))								// handles lower and uppercase letters
		{
		case 'a':{												// add data
			
			cout << "ADD DATA\n";
			cout << "Enter Serial number: ";
			getline(cin, key1);									// read serial number
			while (gunTable->search_Item(key1, doNothing)){
				cout << "Serial number already exists. Enter again: ";
				getline(cin, key1);
			}
			cout << "Enter make: ";				
			getline(cin, make);
			cout << "Enter model: ";
			getline(cin, model);
			cout << "Enter caliber: ";
			getline(cin, caliber);
			cout << "Enter phone number: ";
			getline(cin, key2);									// read phone number
			while (key2.size() > 10 || key2.size() < 10)			// make sure phone has correct length
			{
				cout << "Invalid phone number... Enter 10-digit phone number please: ";
				getline(cin, key2);
			}
			StolenGun *gunPtr = new StolenGun(key1, make, model, caliber, key2);	// pointer to stolengun object
									
			tree1->insert(key1, gunPtr);			// insert gun in tree1
			tree2->insert(key2, gunPtr);			// insert gun in tree2
			gunTable->insert(gunPtr, key1);			// insert the gun
			cout << "\nDATA ADDED...\n";

			
			break;
		}
		case 'd':{						// delete data
			StolenGun* gunPtr = NULL;  //gunPtr will point to the actual data location and will be used to compare and confirm in BST2 deletion
			cout << "DELETE DATA\n\n";
			cout << "Enter Serial of gun to delete: ";
			getline(cin, key1);
			
			while (!gunTable->search_Item(key1, gunPtr))
			{
				cout << "Gun not found... Please enter Serial again: ";
				getline(cin, key1);
			}
			cout << "Enter phone number: ";
			getline(cin, key2);
			while (key2.size() > 10 || key2.size() < 10)
			{
				cout << "Invalid phone number... Enter 10-digit phone number please: ";
				getline(cin, key2);
			}
			while (gunPtr->getPhoneNum() != key2){
				cout << "The Phone number doesn't  match, Enter phone number again: ";
				getline(cin, key2);
			}
			
			tree1->remove(key1, gunPtr);		//remove gun from tree1
			tree2->remove(key2, gunPtr);		//remove gun from tree2
			gunTable->deleteNode(key1);			// delete the gun

			cout << "\nDATA DELETED...\n";
			break; 
		}
		case 'f':{												// search for data
			
			cout << "S: Search by Serial\n";					// search by serial
			cout << "P: Search by Phone Number:\n\n";			// or by phone number
			cout << "Your choice: ";
			cin >> selection;
			switch (tolower(selection)){
			case 's':
				cout << "Enter serial number: ";
				cin.ignore();
				getline(cin, key1);
				if (!tree1->search_Item(key1, doNothing))
					cout << "No items were found with this serial number\n";
				tree1->search_Item(key1, displayGun);
				break;
			case 'p':
				cout << "Enter 10-digit phone number: ";
				cin.ignore();
				getline(cin, key2);
				while (key2.size() > 10 || key2.size() < 10)			// make sure phone has correct length
				{
					cout << "Invalid phone number... Enter 10-digit phone number please: ";
					getline(cin, key2);
				}
				if (!tree2->search_Item(key2, doNothing))
					cout << "No items were found with this phone number\n";
				tree2->search_Item(key2, displayGun);
				break;
			default:
				cout << "Invalid choice!\n";
				break;
			}
			break;
		}
		case 'l':													// display list menu
			listMenu();
			cin >> selection;
			switch (tolower(selection)){
			case 'u':											
				gunTable->displayList(displayGun);				// list unsorted data
				break;
			case 's':											
				tree1->displayTree(displayGunSerial);					// sort by serial
				break;											
			case 'p':
				tree2->displayTree(displayGunPhone);					// sort by phone
				break;
			case 'i':											
				gunTable->displayTable(displayGunIndented);				// indented list
				break;
			case 'f':											
				tree1->inOrder(displayGunIndented);
				break;
			case 'g':
				cout << "preOrder traversal (serial number): \n\n";
				tree1->preOrder(displayGunIndented);
				break;
			case 'h':
				cout << "postOrder traversal (serial number): \n\n";
				tree1->postOrder(displayGunIndented);
				break;
			case 'j':
				tree2->inOrder(displayGunIndented);
				break;
			case 'k':
				cout << "preOrder traversal (Phone number): \n\n";
				tree2->preOrder(displayGunIndented);
				break;
			case 'l':
				cout << "postOrder traversal (Phone number): \n\n";
				tree2->postOrder(displayGunIndented);
				break;
			case 'q':
				cout << "Quit Menu...\n";
				displayMenu();
				break;
			default:
				cout << "No such option\n";
				break;
			}
			break;
		case 'w':
			cout << "Enter file name to write data to: ";
			getline(cin, outFileName);
			outFile.open(outFileName.c_str());
			tree1->outputFile(outFile, writeData);				// write data Tofile
			cout << "\nData written to file...\n";
			outFile.close();
			break;
		case 's':
			gunTable->display_Statistics();						//display statistics
			break;
		case 'm':
			displayMenu();										// display menu
			break;
		case 'q':
			cout << "End of Program\n\n";
			outFile.open("outputFile.txt");
			tree1->outputFile(outFile, writeData);
			outFile.close();
			break;
		default:
			cout << "That command was not understood" << endl;
			break;
			}


		} while (tolower(choice) != 'q');

		inFile.close();											// close file
		delete tree1, tree2, gunTable;							// delete bst1, bst2, and hashtable
		//system("pause");
		return 0;

}
