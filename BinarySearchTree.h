/*
THIS PROGRAM IS A SIMPLE BINARY SEARCH TREE
EXPOSED BINARY SEARCH TREE CLASS FUNCTIONS
void printPostOrderTraverse(std::ofstream &writeFile)		- print post order traversal to file
void printBreadthFirstTraverse(std::ofstream &writeFile)	- print breadth first traversal to file
void breadth_firstTraversal()								- print breadth first traversal to screen
bool searchForValue(T value)								- find node in tree
void searchAndModify(T findThis)							- find and replace node value in tree *will change tree structure*
bool deleteValue(T value)									- delete node from tree *will change tree structure*
void addValue(T value)										- add node to tree *if data values are the same, the root will be saved to the left*
*/

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include<fstream>
#include<iostream>
#include"QueueADT.h"

template <class T>
class DualLinkDataNode
{
public:
	T data;
	DualLinkDataNode<T> *leftBranch;
	DualLinkDataNode<T> *rightBranch;

	// defualt constructor
	DualLinkDataNode()
	{
		leftBranch = nullptr;
		rightBranch = nullptr;
	}

	// constructor
	DualLinkDataNode(T value)
	{
		data = value;
		leftBranch = nullptr;
		rightBranch = nullptr;
	}
};

template <class T>
class BinarySearchTree
{
private:
	DualLinkDataNode<T> *rootNode;

protected:
	//  add nodes to the tree using a binary search traversal, and is called by addNode() function
	//  this function is access protected from anything outside the class for safety
	DualLinkDataNode<T> *addInOrder(DualLinkDataNode<T> *subTreePtr, DualLinkDataNode<T> *newNode)
	{
		// if the current sub-tree is empty, return the address of the new node
		if (subTreePtr == nullptr)
		{
			return newNode;
		}

		else
		{
			// if the sub-tree's data is greater than or equal to new node's data, send new node down the left branch
			if (newNode->data <= subTreePtr->data)
			{
				subTreePtr->leftBranch = addInOrder(subTreePtr->leftBranch, newNode);
			}

			else
			{
				subTreePtr->rightBranch = addInOrder(subTreePtr->rightBranch, newNode);
			}

			return subTreePtr;
		}
	}

	//  This is protected function that will remove the value from the tree.
	//  First it will search the tree for the value, then if the value is found, it will call removeNode() function
	//  Remove node function will delete the node and balance the tree as required
	DualLinkDataNode<T> *removeValue(DualLinkDataNode<T> *subTreePtr, const T findThis, bool &successBoolean)
	{
		DualLinkDataNode<T> *tempPtr = nullptr;
		// if the value was not found, terminate the removeValue() recursion, and return a false for success
		if (subTreePtr == nullptr)
		{
			successBoolean = false;
			return nullptr;
		}

		// if the value was found, send this node's address to removeNode() function and set success to true
		else if (subTreePtr->data == findThis)
		{
			subTreePtr = removeNode(subTreePtr);
			successBoolean = true;
			return subTreePtr;
		}
		// check the left branch for the value
		else if (subTreePtr->data > findThis)
		{
			tempPtr = removeValue(subTreePtr->leftBranch, findThis, successBoolean);
			subTreePtr->leftBranch = tempPtr;
			return subTreePtr;
		}
		// check the right branch for the value
		else
		{
			tempPtr = removeValue(subTreePtr->rightBranch, findThis, successBoolean);
			subTreePtr->rightBranch = tempPtr;
			return subTreePtr;
		}
	}

	//  This function is valled by removeValue() function and is only called if the value was found
	//  The function will use recursion to balance the tree by calling the removeLeftNode function
	DualLinkDataNode<T> *removeNode(DualLinkDataNode<T> *currentNode)
	{
		DualLinkDataNode<T> * tempPtr = nullptr;

		// if the sub-tree has no left or right branches, delete the node and return a nullptr
		if (currentNode->leftBranch == nullptr && currentNode->rightBranch == nullptr)
		{
			delete currentNode;
			currentNode = nullptr;
			return nullptr;
		}

		// if the sub-tree has only one branch
		else if ((currentNode->leftBranch != nullptr && currentNode->rightBranch == nullptr) || (currentNode->rightBranch != nullptr && currentNode->leftBranch == nullptr))
		{
			// store currnetNode's address in tempPtr
			tempPtr = currentNode;

			//  if the sub-tree's path is only on the left branch, make subTreePtr point to the left branch
			if (currentNode->leftBranch != nullptr && currentNode->rightBranch == nullptr)
			{
				currentNode = currentNode->leftBranch;
				delete tempPtr;
				tempPtr = nullptr;
				return currentNode;
			}

			//  else, the path is only the right branch
			else
			{
				currentNode = currentNode->rightBranch;
				delete tempPtr;
				tempPtr = nullptr;
				return currentNode;
			}
		}

		// else, the sub-tree has two branches
		else
		{
			// Find the inorder successor of the entry in N: it is in the left subtree rooted at N�s right child
			tempPtr = removeLeftMostNode(currentNode->rightBranch, currentNode->data);  // data is referenced in removeleftnode function
			currentNode->rightBranch = tempPtr;
			currentNode->data = currentNode->data;  // because the data was referenced, it was changed
			return currentNode;
		}
	}

	//  Travel down the left branch looking for the end of the path and get last nodes value
	DualLinkDataNode<T> *removeLeftMostNode(DualLinkDataNode<T> *nodePtr, T &inorderSuccesssor)
	{

		if (nodePtr->leftBranch == nullptr)
		{
			// This is the node you want; it has no left child, but it might have a right subtree
			inorderSuccesssor = nodePtr->data;
			return removeNode(nodePtr);
		}

		else
		{
			return removeLeftMostNode(nodePtr->leftBranch, inorderSuccesssor);
		}

	}

	//  Search the tree for the given value using recursion.  If the value is found update the boolean to true
	//  Else set the passed boolean to false
	DualLinkDataNode<T> *searchTree(const T findThis, DualLinkDataNode<T> *root, bool &successBoolean)
	{
		// if the value was not found, return false
		if (root == nullptr)
		{
			successBoolean = false;
			return nullptr;
		}
		// if the value is found, return true and unwind the recursion
		else if (root->data == findThis)
		{
			successBoolean = true;
			return root;
		}
		// if the search value is less than or equal to the data stored in the node, use recursion to travel down the left branch
		else if (findThis <= root->data)
		{
			//return searchTree(value, root->leftBranch);
			return searchTree(findThis, root->leftBranch, successBoolean);
		}
		// else travel down the right branch
		else
		{
			//return searchTree(findThis, root->rightBranch);
			return searchTree(findThis, root->rightBranch, successBoolean);
		}
	}

	//  Use a recursion to travel down the left branches until a dead end is found
	//  Then travel down the right branch until a dead is found
	//  Once both paths are checked, print out the data in the node at the end of the branch
	//  Also this function is protected from access outside of the class
	void post_orderTraversal(DualLinkDataNode<T> *currentRoot, std::ofstream &writeFile)
	{
		// if the currentRoot is null, that means this branch's patch is at the end
		if (currentRoot == nullptr)
		{
			return;
		}
		else
		{
			post_orderTraversal(currentRoot->leftBranch, writeFile); // check the left branch for a valid path
			post_orderTraversal(currentRoot->rightBranch, writeFile); // check the right branch for a valid path
			writeFile << currentRoot->data << std::endl; // when both branches are nullptr's, print out the current node's data
		}
	}

	//  Use a post order traverse to get to the bottom of the tree,
	//  then delete the node and use recursion to work back up the tree
	//  the function is protected from anything outside of the class
	void destroyTree(DualLinkDataNode<T> *currentRoot)
	{
		// if the currentRoot is null, that means this branch's patch is at the end
		if (currentRoot == nullptr)
		{
			return;
		}
		else
		{
			destroyTree(currentRoot->leftBranch); // check the left branch for a valid path
			destroyTree(currentRoot->rightBranch); // check the right branch for a valid path
			delete currentRoot; // when both branches are nullptr's, delete the node
		}
	}

public:
	//------------------------------------------------------------
	// Constructors and Destructors:
	//------------------------------------------------------------

	BinarySearchTree()
	{
		rootNode = nullptr;
	}

	~BinarySearchTree()
	{
		// call the destroy tree function to remove all the nodes in the tree
		destroyTree(rootNode);
	}

	//------------------------------------------------------------
	// Public Methods:
	//------------------------------------------------------------

	//  Use recursion to travel down the tree until the proper loaction is found to add the new node
	void addValue(T value)
	{
		DualLinkDataNode<T> *newNode = new DualLinkDataNode<T>(value);

		//  if the tree has no items, set the new node as the root node
		if (!rootNode)
		{
			rootNode = newNode;
		}

		//  else, process the node using a binary search to find the correct location for the value
		else
		{
			rootNode = addInOrder(rootNode, newNode);
		}
	}

	//  the public remove node function
	//  removes the node holding the passed value, if the node is in the tree
	//  returns true if the node was removed, or returns false
	bool deleteValue(T value)
	{
		bool status;  // store the result of the remove node recursion

		//  if the tree has no items, print out the error message
		if (!rootNode)
		{
			std::cout << "error: the tree has no items";
			return false;
		}

		// else, call the protected removeValue() function
		else
		{
			removeValue(rootNode, value, status);
		}
		return status;
	}

	//  The public function to search for a value
	//  This function checks to see if the tree has items, then sends the search value to the function searchTree()
	bool searchForValue(T value)
	{
		bool status;

		if (!rootNode)
		{
			return false;
		}
		else if (rootNode->data == value)
		{
			return true;
		}
		// if the search value is less than or equal to the data in rootNode, travel down the left branch
		else if (value <= rootNode->data)
		{
			//return searchTree(value, rootNode->leftBranch);
			searchTree(value, rootNode->leftBranch, status);

		}
		// else, travel down the right branch
		else
		{
			//return searchTree(value, rootNode->rightBranch);
			searchTree(value, rootNode->rightBranch, status);
		}
		return status;
	}

	//  The public function to modify a value in the tree
	//  this is a two step process, first step is search for the value
	//  if the value is found, delete the node
	//  next step is insert a new node with a new value into the tree
	//  thus perserving the tree balance
	void searchAndModify(T findThis)
	{
		T newValue;
		bool status;
		DualLinkDataNode<T> *nodeWithSeachValue = nullptr;

		// search for a value, and if found, modify the node's data member
		if (!rootNode)
		{
			std::cout << "error: tree is empty";
			return;
		}
		else
		{
			status = deleteValue(findThis);
		}
		if (status == true)
		{
			std::cout << "current value: " << findThis << std::endl;
			std::cout << "enter a new value: ";
			getline(std::cin, newValue);
			addValue(newValue);
		}
		else
		{
			std::cout << "value: " << findThis << " was not found";
		}
	}

	//  breadth - first traversal mechanism - PRINTS TO TERMINAL
	void breadth_firstTraversal()
	{
		if (rootNode == nullptr)
		{
			return;
		}

		else
		{
			QueueADT<DualLinkDataNode<T>*> Q;
			Q.enQueue(rootNode);
			//while there is at least one discovered node
			while (!Q.isQueueEmpty())
			{
				DualLinkDataNode<T>* current = Q.getFront();
				std::cout << current->data << " ";
				if (current->leftBranch != nullptr)
				{
					Q.enQueue(current->leftBranch);
				}
				if (current->rightBranch != nullptr)
				{
					Q.enQueue(current->rightBranch);
				}
				Q.deQueue(); // remove the element at the front
			}
		}
	}

	//  breadth - first traversal mechanism - PRINTS TO FILE
	void printBreadthFirstTraverse(std::ofstream &writeFile)
	{
		if (rootNode == nullptr)
		{
			return;
		}

		else
		{
			QueueADT<DualLinkDataNode<T>*> Q;
			Q.enQueue(rootNode);
			//while there is at least one discovered node
			while (!Q.isQueueEmpty())
			{
				DualLinkDataNode<T>* current = Q.getFront();
				writeFile << current->data << std::endl;
				if (current->leftBranch != nullptr)
				{
					Q.enQueue(current->leftBranch);
				}
				if (current->rightBranch != nullptr)
				{
					Q.enQueue(current->rightBranch);
				}
				Q.deQueue(); // remove the element at the front
			}
		}
	}

	//  uses post order traveresal to process the items in the tree, then writes the data to the &writeFile
	void printPostOrderTraverse(std::ofstream &writeFile)
	{
		if (!rootNode)
		{
			std::cout << "error: tree is empty";
		}
		else
		{
			post_orderTraversal(rootNode, writeFile);
		}
	}
};

#endif