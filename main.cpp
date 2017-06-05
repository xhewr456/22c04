// 22C - Manish Goel
// Lab 04: Binary Search Tree
// Names: Alexander McNulty, Clifford Smith

/*
This program is a demonstration of binary search tree.
When run the program dataFile.txt in the CWD (current working directory)
reads in the data then sorts and print them to two seperate files.
Check the CWD for two files:
sortedBirthdates.txt - contains dates in breadth-first traversal
sortedNames.txt		 - contains dates in post-order traversal
This task is accomplished by the exposed behaviors in BinarySearchTree.h.
BinarySearchTree.h requires LinkedList.h and QueueADT.h to be in CWD
In this program we used:
addValue(string)
printPostOrderTraverse(ofstream)
printBreadthFirstTraverse(ofstream)
See top of BinarySearchTree.h for additional methods
*/

#include<iostream>
#include<string>
#include<fstream>
#include"BinarySearchTree.h"

using namespace std;

int main()
{
	// create and open the INPUT FILE - containing names, and birthdays
	ifstream inputFile;
	string fileName;
	cout << "enter the file path and name of the input file, the default is \"dataFile.txt\"" << endl;
	cout << "file path/name: ";
	getline(cin, fileName);
	inputFile.open(fileName);

	//create TWO SEPERATE TREES for holding birthdays or names
	BinarySearchTree<string> firstAndLastNames;
	BinarySearchTree<string> birthDates;

	//READ, SORT, then ADD data to correct tree
	string tempStorage;
	cout << "creating the two binary trees...\n";
	while (!inputFile.eof())
	{

		//READ the next line from the input file
		getline(inputFile, tempStorage);
		//SORT ascii values for 0-9 to find DATES
		if (tempStorage[0] == 48 ||
			tempStorage[0] == 49 ||
			tempStorage[0] == 50 ||
			tempStorage[0] == 51 ||
			tempStorage[0] == 52 ||
			tempStorage[0] == 53 ||
			tempStorage[0] == 54 ||
			tempStorage[0] == 55 ||
			tempStorage[0] == 56 ||
			tempStorage[0] == 57)
		{
			//if the line begins with a number ADD to BIRTHDAY TREE
			birthDates.addValue(tempStorage);
		}
		else
		{
			//if not ADD to NAMES TREE
			firstAndLastNames.addValue(tempStorage);
		}
	}
	inputFile.close();
	cout << "completed\n";
	cout << endl;

	
	// ask the user for a name to search for
	cout << "enter a name to search for: ";
	getline(cin, tempStorage);
	bool status = firstAndLastNames.searchForValue(tempStorage);
	if (status == true)
	{
		cout << tempStorage << " was found\n";
	}
	else
	{
		cout << tempStorage << " was not found\n";
	}
	cout << endl;

	// ask the user for a name to add
	cout << "enter a name to add: ";
	getline(cin, tempStorage);
	firstAndLastNames.addValue(tempStorage);
	cout << tempStorage << " was added\n";
	cout << endl;

	// ask the user for a name to remove
	cout << "enter a name to remove: ";
	getline(cin, tempStorage);
	status = firstAndLastNames.deleteValue(tempStorage);
	if (status == true)
	{
		cout << tempStorage << " was removed\n";
	}
	else
	{
		cout << tempStorage << " was not removed\n";
	}
	cout << endl;

	// ask the user for a name to modify, which is a search, delete, and add function
	cout << "enter a name to modify: ";
	getline(cin, tempStorage);
	firstAndLastNames.searchAndModify(tempStorage);
	cout << endl;


	// create and open output file for names
	// print the BST of names in POSTORDER to output file
	cout << "creating the sortedNames.txt using post order traversal...\n";
	ofstream namesOutputFile;
	namesOutputFile.open("./sortedNames.txt");
	firstAndLastNames.printPostOrderTraverse(namesOutputFile);
	namesOutputFile.close();
	cout << "completed\n";

	// create and open output file for names
	// print the BST of names in BREADTH to output file
	cout << "creating the sortedBirthdates.txt file using breadth first traversal...\n";
	ofstream birthdateOutputFile;
	birthdateOutputFile.open("./sortedBirthdates.txt");
	birthDates.printBreadthFirstTraverse(birthdateOutputFile);
	birthdateOutputFile.close();
	cout << "completed\n";
	cout << endl;

	//cin.ignore();
	cout << "\npress <Enter> to exit...";
	cin.get();
	return 0;
}