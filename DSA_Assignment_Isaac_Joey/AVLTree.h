// hashTable data 
#pragma once
#include <iostream>
using namespace std;

typedef string KeyType;
template <typename T>
struct AVLNode
{
    KeyType key;
    T item;
    AVLNode* left;
    AVLNode* right;
    int height; // height of the current node 
    // maintain a list of pointers to the actual actor or movie object 
};

template <typename T>

class AVLTree
{
private:

    AVLNode* root;

public:

    AVLTree(); // Constructor to initialize the tree

    // Function to get the height of a node
    int height(AVLNode* node);

    // Methods for performing right-rotate and left-rotate
    AVLNode* rotateRight(AVLNode*& node);
    AVLNode* rotateLeft(AVLNode*& node);

    // Other necessary methods (e.g., insert, balance, etc.) could be added here
    void insert(T item);
    void insertRecursive(AVLNode*& root,string key,T item);
    void delete(KeyType key);
    int getBalanceFactor(AVLNode* root); 
    void print();
    void print(AVLNode<T>* root);
};

