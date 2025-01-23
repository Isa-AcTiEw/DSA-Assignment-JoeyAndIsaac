#pragma once
// Hash table class definition with separate chaining
#include <iostream>
#include "AVLTree.h"
#include <string>
using namespace std;
typedef int hashKey;

template <class T>
class HashTable
{
private:
    static const int MAX_SIZE = 101;  // Maximum size of the hash table
    AVLTree<T>* items[MAX_SIZE];      // Array of pointers to AVLTree objects
    int size;                         // Number of elements in the table

public:
    // Constructor for the HashTable
    HashTable();

    // Hash function to map key to an index
    int hash(hashKey newKey);

    // Add a new item to the hash table
    bool add(hashKey newKey, T newItem);

    // Check if the hash table is empty
    bool isEmpty();

    // Get the number of elements in the hash table
    int getLength();

    // Print the contents of the hash table
    void print();
};

