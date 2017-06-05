#include<iostream>
#include<string>
//#include"LinkedList.h"
#include"QueueADT.h"
#include"BinarySearchTree.h"
#include<fstream>

using namespace std;


int main()
{
	// open the data input file
	ifstream inputFile;
	inputFile.open("dataFile.txt");
	ofstream namesOutputFile;
	namesOutputFile.open("sortedNames.txt");
	ofstream birthdateOutputFile;
	birthdateOutputFile.open("sortedBirthdates.txt");


	BinarySearchTree<string> firstAndLastNames;
	BinarySearchTree<string> birthDates;
	string tempStorage;

	while (!inputFile.eof())
	{
		getline(inputFile, tempStorage);
		firstAndLastNames.addValue(tempStorage);

		getline(inputFile, tempStorage);
		birthDates.addValue(tempStorage);
	}
	inputFile.close();

	// this will create the sorted names file
	firstAndLastNames.printPostOrderTraverse(namesOutputFile);
	cout << endl;
	cout << endl;

	// this will create the sorted birthday file
	birthDates.printBreadthFirstTraverse(birthdateOutputFile);
	cout << endl;
	cout << endl;

	namesOutputFile.close();
	birthdateOutputFile.close();

	BinarySearchTree<int> root; //pointer stores the address of root node
	root.addValue(12);
	root.addValue(1);
	root.addValue(2);
	root.addValue(15);
	root.addValue(13);
	root.addValue(2);
	root.addValue(4);
	root.addValue(100);

	root.breadth_firstTraversal();
	cout << endl;

	//root.printPostOrderTraverse();
	cout << endl;

	root.searchAndModify(15);
	root.breadth_firstTraversal();
	cout << endl;
	cout << endl;

	root.deleteValue(1);
	root.breadth_firstTraversal();
	cout << endl;

	root.addValue(105);
	root.breadth_firstTraversal();
	cout << endl;

	root.deleteValue(105);
	root.breadth_firstTraversal();
	cout << endl;

	root.addValue(107);
	root.breadth_firstTraversal();
	cout << endl;

	cout << root.deleteValue(10);
	cout << endl;

	// testing stuff
	BinarySearchTree<int> testRoot2;
	testRoot2.addValue(121);
	testRoot2.addValue(12);
	testRoot2.addValue(23);
	testRoot2.addValue(154);
	testRoot2.addValue(25);
	testRoot2.addValue(46);
	testRoot2.addValue(107);

	testRoot2.breadth_firstTraversal();
	cout << endl;


	BinarySearchTree<string> testRootString;
	testRootString.addValue("one");
	testRootString.addValue("three");
	testRootString.addValue("five");
	testRootString.addValue("seven");
	testRootString.addValue("eleven");
	testRootString.addValue("thirteen");
	testRootString.addValue("seventeen");
	testRootString.deleteValue("seventeen");

	testRootString.breadth_firstTraversal();
	cout << endl;

	root.searchAndModify(15);
	cout << endl;
	root.breadth_firstTraversal();
	cout << endl;

	cout << endl;

	int number = -1;
	while (number != 0)
	{
		cout << "Enter a positive number to be searched, enter <0> to exit: ";
		cin >> number;
		if (root.searchForValue(number) == true)
		{
			cout << "Found\n\n";
		}
		else if (number == 0)
		{
			break;
		}
		else
		{
			cout << "Not Found\n\n";
		}
	}


	cin.ignore();
	cout << "press <Enter> to exit...";
	cin.get();
	return 0;
}
