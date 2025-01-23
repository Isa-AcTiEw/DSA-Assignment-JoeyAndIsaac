
#include "AVLTree.h"
#include <iostream>
#define max(x,y) ((x > y)? x : y)
template <class T>
// constructor 

AVLTree<T>::AVLTree() {
	root = nullptr;
}

template <class T>

void AVLTree<T>::insert(T item) {
	// create the node here 
	AVLNode* avlNode;
	avlNode->key = item->getKey();
	avlNode->item = item;
	if (root == nullptr) {
		root = avlNode
	}
	else {
		// call the recursive function 
		insertRecursive(root, key, item);
	}
}

// *& is a reference to a pointer variable 
template <class T>
void AVLTree<T>::insertRecursive(AVLNode<T>*& root, string key, T item) {
	// recursive base case if the root == nullptr 
	AVLNode* newNode;
	// base case the tree is automatically balanced at that node (left and right height is 0, height of node is 1)
	if (root == nullptr) {

		newNode->key = key;
		newNode->item = item;
		return;
	}
	else {
		if (key < root->key) {
			// update the left subtree pointer to the newNode that is inserted on the leftSubtree
			root->left = insertRecursive(root->left, string key, T item);
		}
		else {
			root->right = insertRecursive(root->right, string key, T item);
		}
	}

	// Account for any imbalancing during insertion (after the node is inserted, i can access its predecessor node (parent) to check if its balanced 
	int bf = getBalanceFactor(root);
	// Perform right rotation  (Tree's right subtree is heavier means the height is > 0, but since we take height(left) - height(right) i will get a negative number 
	// balance factor is < 0
	if (bf > 1 && newNode->key < root->left->key) {
		return rotateRight(root);
	}
	// Perform left rotation (Tree's left subtree is heavier means the height > 0) 
	// balance factor > 0
	if (bf < -1 && newNode->key < root->right->key) {
		return rotateLeft(root);
	}
	// Perform Left-Right rotation
	if (bf > 1 && newNode->key > root->right->key) {
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	}
	// Perform Right-Left rotation 
	if (bf < -1 && newNode->key < root->right->key) {
		root->right = rotateRight(root->right);
		return rotateLeft(root);
	}

	
	
}


template <class T>
AVLNode<T>* AVLTree<T>::rotateRight(AVLNode<T>*& node) {
	// rotate the tree to the right 
	AVLNode* c = node->left;
	node->left = c->right;
	c->right = node;
	return c;
}

template <class T>
AVLNode<T>* AVLTree<T>::rotateLeft(AVLNode<T>*& node) {
	// rotate tree to the left 
	AVLNode* c = node->right;
	node->right = c->left;
	c->left = node;
	return c;
}

template <class T>

// This function given the root of the avl tree returns the height of the whole tree 
// since an avl tree is balanced the time complexity of getHeight is O(n) where log n reperesents the number of nodes within the tree 
// Recursively go through the right and left subtrees of each node, height is 1 + max(rightHeight,leftHeight)

int AVLTree<T>::height(AVLNode<T>* root) {
	if (root == nullptr) {
		return 0;
	}
	int leftHeigt = height(root->left);
	int rightHeight = height(root->right);
	return 1 + max(leftHeight, rightHeight);
}

template <class T>
int AVLTree<T>::getBalanceFactor(AVLNode<T>* root) {
	if (root == nullptr) {
		return 0;
	}
	else {
		return height(root->left) - height(root->right)
	}
}

template <class T>

// use inOrder traversal to display names in alphabetical order (automatically lexographically sorted when storing strings in a tree)
void AVLTree<T>::print(AVLNode<T>* root) {
	if (root == nullptr) {
		return;
	}
	else {
		print(root->left); // traverse the left subtree 
		T data = root->item;
		// print the data 
		data->displayInfo();
		print(root->right); // traverse the right subtree
	}
}