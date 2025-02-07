// hashTable data 
#pragma once
#include <iostream>
#include "Vector.h"
#include "Actor.h"
#include "Movie.h"
using namespace std;

typedef int KeyType;
template <typename T>
struct AVLNode
{
    KeyType key;
    T item;
    AVLNode* left;
    AVLNode* right;
    int height = 1; // height of the current node 
    // maintain a list of pointers to the actual actor or movie object 
    Vector<T*> relatedPointers;
};

template <>
struct AVLNode<Actor>
{
    KeyType key;
    Actor item;
    AVLNode* left;
    AVLNode* right;
    int height = 1; // height of the current node 
    // maintain a list of pointers to the actual actor or movie object 
    Vector<Movie*> relatedPointers;
};

template <> 
struct AVLNode<Movie>
{
    KeyType key;
    Movie item;
    AVLNode* left;
    AVLNode* right;
    int height = 1; // height of the current node 
    // maintain a list of pointers to the actual actor or movie object 
    Vector<Actor*> relatedPointers;
};

template <typename T>

// use id as the key for the avlTree as well to ensure that same actors with the same name are able to be inserted 
// As well for easier insertion for finding related casts (using cast.csv)
// Consider ways to improve the load balance of the hash table (as it looks quite sparse)
class AVLTree
{
private:

    AVLNode<T>* root;

public:

    AVLTree(); // Constructor to initialize the tree

    // Function to get the height of a node
    int height(AVLNode<T>* node);

    // Methods for performing right-rotate and left-rotate
    void rotateRight(AVLNode<T>*& node);
    void rotateLeft(AVLNode<T>*& node);

    // Other necessary methods (e.g., insert, balance, etc.) could be added here
    void insert(T item);
    void insertRecursive(AVLNode<T>*& root,int key,T item);
    int getBalanceFactor(AVLNode<T>* root); 
    void print(AVLNode<T>* root);
    AVLNode<T>* searchAVLById(int id);
    AVLNode<T>* searchAVLById(AVLNode<T>* t, int id);
    AVLNode<T>* searchAVLByName(string name);
    AVLNode<T>* searchAVLByName(AVLNode<T>* t, string name);
    AVLNode<T>* getRoot();
    void retrieveAll(Vector<AVLNode<T>*>& nodeList);
    void retrieveAll(AVLNode<T>* temp, Vector<AVLNode<T>*>& nodeList);

    void print();
};

