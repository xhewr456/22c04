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

	// testing stuff
	BinarySearchTree<int> testRoot2;
	testRoot2.addNode(121);
	testRoot2.addNode(12);
	testRoot2.addNode(23);
	testRoot2.addNode(154);
	testRoot2.addNode(25);
	testRoot2.addNode(46);
	testRoot2.addNode(107);

	testRoot2.breadth_firstTraversal();
	cout << endl;


	BinarySearchTree<string> testRootString;
	testRootString.addNode("one");
	testRootString.addNode("three");
	testRootString.addNode("five");
	testRootString.addNode("seven");
	testRootString.addNode("eleven");
	testRootString.addNode("thirteen");
	testRootString.addNode("seventeen");

	testRootString.breadth_firstTraversal();
	cout << endl;

	cout << endl;

	int number = 0;
	while (number != -1)
	{
		cout << "Enter a positive number to be searched, enter -1 to exit: \n";
		cin >> number;
		if (root.search(number) == true)
		{
			cout << "Found\n\n";
		}
		else if (number == -1)
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
