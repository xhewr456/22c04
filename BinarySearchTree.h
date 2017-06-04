/*
THIS PROGRAM IS A SIMPLE BINARY SEARCH TREE
//if data values are the same, the root will be saved to the left
*/

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

template <class T>
class DualLinkDataNode
{
public:
	T data;
	//T firstAndLastName;
	//T birthDate;
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

	// Removes the given target value from the tree while maintaining a binary search tree.
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
			// Item is in the root of some subtree
			subTreePtr = removeNode(subTreePtr);
			successBoolean = true;
			return subTreePtr;
		}

		else if (subTreePtr->data > findThis)
		{
			// Search the left subtree
			tempPtr = removeValue(subTreePtr->leftBranch, findThis, successBoolean);
			subTreePtr->leftBranch = tempPtr;
			return subTreePtr;
		}

		else
		{
			// Search the right subtree
			tempPtr = removeValue(subTreePtr->rightBranch, findThis, successBoolean);
			subTreePtr->rightBranch = tempPtr;
			return subTreePtr;
		}
	}

	// Removes the item in the node, N, to which nodePtr points.
	// Returns a pointer to the node at this tree location after node N is deleted.
	DualLinkDataNode<T> *removeNode(DualLinkDataNode<T> *currentNode)
	{
		DualLinkDataNode<T> * tempPtr = nullptr;

		// if the sub-tree has no left or right branches, delete the node and return a nullptr
		if (currentNode->leftBranch == nullptr && currentNode->rightBranch == nullptr)
		{
			delete currentNode;
			currentNode = nullptr;
			//return currentNode;
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
				//currentNode = nullptr;
				return currentNode;
			}

			//  else, the path is only the right branch
			else
			{
				currentNode = currentNode->rightBranch;
				delete tempPtr;
				//currentNode = nullptr;
				return currentNode;
			}
		}

		// else, the sub-tree has two branches
		else
		{
			// Find the inorder successor of the entry in N: it is in the left subtree rooted at N’s right child
			tempPtr = removeLeftMostNode(currentNode->rightBranch, currentNode->data);  // data is referenced in removeleftnode function
			currentNode->rightBranch = tempPtr;
			currentNode->data = currentNode->data;  // because the data was referenced, it has now been changed
			return currentNode;
		}
	}




	// Removes the leftmost node in the left subtree of the node pointed to by nodePtr.
	// Sets inorderSuccessor to the value in this node.
	// Returns a pointer to the revised subtree.
	DualLinkDataNode<T> *removeLeftMostNode(DualLinkDataNode<T> *nodePtr, T &inorderSuccesssor)
	{
		// 
		if (nodePtr->leftBranch == nullptr)
		{
			// This is the node you want; it has no left child, but it might have a right subtree
			inorderSuccesssor = nodePtr->data;
			return removeNode(nodePtr);
		}
		// 
		else
		{
			return removeLeftMostNode(nodePtr->leftBranch, inorderSuccesssor);
		}
		
	}

	//  Recursive function to search the tree for a specific value
	DualLinkDataNode<T> *searchTree(const T findThis, DualLinkDataNode<T> *root, bool &successBoolean)
	//bool searchTree(T value, DualLinkDataNode<T> *root)
	{
		// if the value was not found, return false
		if (root == nullptr)
		{
			//return false;
			successBoolean = false;
			return nullptr;
		}
		// if the value is found, return true and unwind the recursion
		else if (root->data == findThis)
		{
			//return true;
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
		// destructor
		// remove all the dynamically created nodes
	}

	//------------------------------------------------------------
	// Public Methods:
	//------------------------------------------------------------

	// another way to add nodes to the binary tree, based on the book's design
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


	void searchAndModify(T findThis)
	{
		T newValue;
		bool status;
		DualLinkDataNode<T> *nodeWithSeachValue = nullptr;
		// search for a value, and if found, modify the node's data member
		if (!rootNode)
		{
			std::cout << "error: tree is empty";
		}
		else if (rootNode->data == findThis)
		{
			std::cout << "current value: " << rootNode->data << std::endl;
			std::cout << "enter a new value: ";
			getline(std::cin, newValue);
			rootNode->data = newValue;
		}
		else if (findThis <= rootNode->data)
		{
			// search for the value, and if the value is found, prompt for a new value
			nodeWithSeachValue = searchTree(findThis, rootNode->leftBranch, status);
		}
		else
		{
			nodeWithSeachValue = searchTree(findThis, rootNode->rightBranch, status);
		}
		if (nodeWithSeachValue != nullptr && status == true)
		{
			std::cout << "current value: " << nodeWithSeachValue->data << std::endl;
			std::cout << "enter a new value: ";
			getline(std::cin, newValue);
			nodeWithSeachValue->data = newValue;
		}
		else
		{
			std::cout << "value: " << findThis << " was not found";
		}
	}

	void insert(T data)
	{
		DualLinkDataNode<T> *newBstNode = nullptr;
		newBstNode = new DualLinkDataNode<T>(data);

		// if the tree is empty, set the root as the new node 
		//if (root == nullptr)
		if (!rootNode)
		{
			//root = getNewNode(data);
			rootNode = newBstNode;
			newBstNode->leftBranch = nullptr;
			newBstNode->rightBranch = nullptr;
		}

		// else, if data value is less than or equal, the root will be saved to the left branch
		else if (data <= rootNode->data)
		{
			//root->leftBranch = insert(data, root->leftBranch);
			rootNode->leftBranch = insertNode(newBstNode, rootNode->leftBranch);
		}

		else
		{
			rootNode->rightBranch = insertNode(newBstNode, rootNode->rightBranch);
		}
	}

	DualLinkDataNode<T> *insertNode(DualLinkDataNode<T> *newBinaryNode, DualLinkDataNode<T> *passedRoot)
	{
		// if the current branch leads to empty leaf, make the node that was passed (newBstNode) the new leaf
		if (passedRoot == nullptr)
		{
			passedRoot = newBinaryNode;
		}

		// else, if data value is less than or equal, the root will be saved to the left branch
		else if (newBinaryNode->data <= passedRoot->data)
		{
			passedRoot->leftBranch = insertNode(newBinaryNode, passedRoot->leftBranch);
		}

		// else, the new data is greater than the current root's data, try to insert the node in the right branch
		else
		{
			passedRoot->rightBranch = insertNode(newBinaryNode, passedRoot->rightBranch);
		}
		return passedRoot;
	}



	//  breadth - first traversal mechanism
	//  this is the renmaed void levelOrder() function
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
				if (current->leftBranch != nullptr) Q.enQueue(current->leftBranch);
				if (current->rightBranch != nullptr) Q.enQueue(current->rightBranch);
				Q.deQueue(); // remove the element at the front
			}
		}
	}

	void post_orderTraversal()
	{
		// post-order traversal mechanism
	}




	//BstNode<T> *insert(T data, BstNode<T> *root)
	//{
	//	if (root == nullptr)
	//	{
	//		root = getNewNode(data);
	//	}
	//	//if data values are the same, the root will be saved to the left
	//	else if (data <= root->data)
	//	{
	//		root->leftBranch = insert(data, root->leftBranch);
	//	}
	//	else
	//	{
	//		root->rightBranch = insert(data, root->rightBranch);
	//	}
	//	return root;
	//}

	//DualLinkDataNode<T> *getNewNode(T data)
	//{
	//	DualLinkDataNode<T> *newNode = new DualLinkDataNode<T>();
	//	newNode->data = data;
	//	newNode->leftBranch = nullptr;
	//	newNode->rightBranch = nullptr;
	//	return newNode;
	//}


	//bool search(int data)
	//{
	//	if (rootNode == nullptr)
	//	{
	//		return false;
	//	}
	//	else if (rootNode->data == data)
	//	{
	//		return true;
	//	}
	//	else if (data <= rootNode->data)
	//	{
	//		return search(data, rootNode->leftBranch);
	//	}
	//	else
	//	{
	//		return search(data, rootNode->rightBranch);
	//	}
	//}

};





#endif