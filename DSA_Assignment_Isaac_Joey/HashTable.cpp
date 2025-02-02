#include "HashTable.h"
#include "AVLTree.h"
#include <string>
#include <cmath>
#include "Actor.h";
#include "Movie.h";
template class HashTable<Actor>;
template class HashTable<Movie>;
template <class T>
//HashTable constructor, intializes an array of MAX_SIZE with each AVLNode pointer in each index pointing to a nullptr 
// Also sets the size of the HashTable to 0 since there are no new elements 
// O(n) as it is dependant on the size of the hash table 

HashTable<T>::HashTable() {
	for (int i = 0; i < MAX_SIZE; i++) {
		items[i] = new AVLTree<T>();
	}
	size = 0;
};

// calcualte the hash given a year
// precondition: the year must be of type string 
// postcondition: the integer generated by the hashYear function is within the MAX_SIZE of the hash table since i used the modulo operator 
// convert to ascii value each of the numbers then do a polynomial rolling hash 

template <class T>
int HashTable<T>::hash(hashKey key) {
	int sum = 0;
	int base = 31;
	string strKey = to_string(key);
	int len = strKey.length();
	for (int i = 0; i < len; i++) {
		int digit = strKey[i] - '0';
		if (digit != NULL) {
			sum += digit * pow(base, len - i);
		}
	}
	if (sum != 0) {
		int hash = sum % 101;
		return hash;
	}
}

template <class T>
bool HashTable<T>::add(hashKey newKey, T item) {
	// hash the key first 
	int index = hash(newKey); // year of released or date of year for the actor 
	// call the insert method pass in the item;
	AVLTree<T>* avlTree = items[index];
	avlTree->insert(item);
	size++;
	return true;
}

template <class T>
bool HashTable<T>::isEmpty() {
	return size == 0;
}

template <class T>
int HashTable<T>::getLength() {
	return size;
}

template <class T>

void HashTable<T>::print() {
	for (int i = 0; i < getLength(); i++) {
		if (items[i] != nullptr) {
			AVLTree<T>* avlTree = items[i];
			avlTree->print();
		}
	}
}

template <class T>

#include <iostream>
#include <stdexcept>  // For std::invalid_argument or std::runtime_error

AVLNode<T>* HashTable<T>::search(int id) {
	try {
		std::cout << "Searching for ID: " << id << std::endl;

		// Check if ID is valid (optional check, depending on your use case)
		if (id < 0) {
			throw std::invalid_argument("ID cannot be negative.");
		}

		// Loop through all hash table buckets
		for (int i = 0; i < MAX_SIZE; i++) {
			// Access the AVL tree at the current index
			AVLTree<T>* avlTree = items[i];

			// Check if the AVL tree is not null and its root is not null
			if (avlTree != nullptr && avlTree->getRoot() != nullptr) {
				// Perform the search in the AVL tree using the provided ID
				AVLNode<T>* item = avlTree->searchAVLById(id);

				// If the item is found, return it
				if (item != nullptr) {
					return item;
				}
			}
		}

		// If the ID is not found in any of the AVL trees, throw an exception
		throw std::runtime_error("Item with ID " + std::to_string(id) + " not found in the hash table.");

	}
	catch (const std::invalid_argument& e) {
		// Catch invalid argument exception (e.g., if the ID is negative)
		std::cerr << "Invalid argument: " << e.what() << std::endl;
	}
	catch (const std::runtime_error& e) {
		// Catch runtime error exception (e.g., ID not found)
		std::cerr << "Runtime error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		// Catch any other standard exception
		std::cerr << "Error: " << e.what() << std::endl;
	}

	// Return nullptr if an error occurred
	return nullptr;
}


template <class T>
AVLTree<T>* HashTable<T>::getKey(int key) {
	// hash the key
	int index = hash(key);
	if (index != NULL) {
		// locate the index at which the avl tree pointer is stored 
		AVLTree<T>* root = items[index];
		if (root != nullptr) {
			return root;
		}
		else {
			return nullptr;
		}
	}
}