// hashTable data 
// Team Member 1: Isaac Tiew Xun Yong (S10257760G) SearchAVLBYId, removeNode, insertRecursive
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
    T* item;
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
    Actor* item;
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
    Movie* item;
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
    AVLNode<T>* rotateRight(AVLNode<T>* nodeN);
    AVLNode<T>* rotateLeft(AVLNode<T>* nodeN);

    // Other necessary methods (e.g., insert, balance, etc.) could be added here
    /*
    * Helper function for inserting all the nodes in the avl tree, passes the argument T* item which is the pointer to the item inserted
    */
    void insert(T* item);
    /*
    * Precondition: Root must not be a nullptr 
      Post-condition: Returns the difference in height between the left and right subtrees of the node
    * Time complexity: O(log n) as it calls the height recursively on the left and right subtrees of the current node being traversed 
    */
    int getBalanceFactor(AVLNode<T>* root);
    /*
    * Precondition: root must not be a nullptr
    * Postcondition: Displays all the details an information of either the movie or actor avlNode
    * Time Complexity: Is O(n) as each node is being traversed in inOrder traversal and the function displayInfo on each node 
    */
    void print(AVLNode<T>* root);

    /*
    * helper function for removeNode
    */
    void remove(int key);
    /*  removeNode
        * Precondition: The key given which is either the movieId or ActorId must be a valid id (this id exists in the hash table)
        * Postcondition: The node with the given key is being removed from the avl tree, rebalancing operations are performed where necessary
        * Time complexity: O(log n) recursively searches for the node on the left subtree if key of curretn node < target key else it recursively searches the right subtree
        * for the key. For performing rebalancing operations once the algorithm has stepped out of the recursion it calculates the balanceFactor of the current node
        * and checks for the conditions for performing a left - left rotation, right - left rotation, left - right rotation, right - right rotation
    */
    AVLNode<T>* removeNode(AVLNode<T>* root, int key);

    /*
    * Helper function for searchAVLById
    */
    AVLNode<T>* searchAVLById(int id);

    /*
    * Precondition: the id given must be a valid movie or actorId that exists in the avltree 
    * Postcondition: The avlNode that has a key same as the target id is returned 
    * Time complexity: 
       Average Case O(log n): Traverse the avl tree recusively if the current node key < id recursively traverse the right subtree if the key < id recusively traverse the left subtree
       in each recursive step the auxiliary space needed for searching in the avl tree is being halfed, the time taken to search the entire tree grows logarithmically  
       Best Case O(1): If the target id is found in the root of the avltree no need to traverse the tree
    */
    AVLNode<T>* searchAVLById(AVLNode<T>* t, int id);
    AVLNode<T>* searchAVLByName(string name);
    /*
    * SearchAVLByName() is a recursive algorithm that traverses the entire avl tree in inOrder traversal this is because since name is not the key of the avl node 
    * it is not possible for each recursive step to half the space needed for searching hence i would have to recurse on both the left and right subtrees hence the time 
    * complexity is O(n).
    */
    AVLNode<T>* searchAVLByName(AVLNode<T>* t, string name);
    AVLNode<T>* getRoot();
    void retrieveAll(Vector<AVLNode<T>*>& nodeList);
    void retrieveAll(AVLNode<T>* temp, Vector<AVLNode<T>*>& nodeList);
    bool isBalanced(AVLNode<T>* root);
    AVLNode<T>* insertRecursive(AVLNode<T>* node, int key, T* item, AVLNode<T>* newNode);
    void print();
};
