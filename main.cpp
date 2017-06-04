#include<iostream>
#include<string>
//#include"LinkedList.h"
#include"QueueADT.h"
//#include"Currency.h"
#include"BinarySearchTree.h"

using namespace std;


int main()
{
	BinarySearchTree<int> root; //pointer stores the address of root node
	root.insert(12);
	root.insert(1);
	root.insert(2);
	root.insert(15);
	root.insert(2);
	root.insert(4);
	root.insert(100);

	//root.levelOrder();
	root.breadth_firstTraversal();
	cout << endl;

	root.deleteValue(12);
	root.breadth_firstTraversal();
	cout << endl;

	root.addValue(105);
	root.breadth_firstTraversal();
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

	cout << endl;

	int number = -1;
	while (number != 0)
	{
		cout << "Enter a positive number to be searched, enter <0> to exit: ";
		cin >> number;
		if (root.search(number) == true)
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
