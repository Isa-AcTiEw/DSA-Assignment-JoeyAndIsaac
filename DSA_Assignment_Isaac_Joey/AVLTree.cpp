#include "AVLTree.h"
#include "Actor.h"
#include "Movie.h"
#include <iostream>
#include <algorithm>  // For std::max

template class AVLTree<Actor>;
template class AVLTree<Movie>;

template <class T>
// Constructor
AVLTree<T>::AVLTree() {
    root = nullptr;
}

template <class T>
void AVLTree<T>::insert(T item) {
    int key = item.getKey();
    cout << "This is the given key: " << key << endl;
    AVLNode<T>* avlNode = new AVLNode<T>();  // Correctly allocate memory for avlNode
    avlNode->key = key;
    avlNode->item = item;
    if (root == nullptr) {
        root = avlNode;
    }
    else {
        insertRecursive(root,key,item);
    }
}

template <class T>
void AVLTree<T>::insertRecursive(AVLNode<T>*& t, int key, T item) {
    // root is just a pointer to a reference used to traversed the entire avl tree 
    if (t == nullptr) {
        AVLNode<T>* newNode = new AVLNode<T>;
        newNode->key = key;
        newNode->item = item;
        newNode->left = nullptr;
        newNode->right = nullptr;
        t = newNode; // attatch the leaf node 
        return;
    }

    if (key > t->key) {
       insertRecursive(t->right, key, item);
       cout << "The key is greater: " << endl;
    }
    else if (key < t->key){
        insertRecursive(t->left, key, item);
        cout << "The key is lesser: " << endl;
    }

    // Recalculate balance factor after insertion
    int bf = getBalanceFactor(t);

    // Right rotation
    if (bf > 1 && key < t->left->key) {
       rotateRight(t);
    }
    // Left rotation
    if (bf < -1 && key > t->right->key) {
        rotateLeft(t);
    }
    // Left-Right rotation
    if (bf > 1 && key > t->left->key) {
        rotateLeft(t->left);
    }
    // Right-Left rotation
    if (bf < -1 && key < t->right->key) {
        rotateRight(t->right);
    }

}

template <class T>
void AVLTree<T>::rotateRight(AVLNode<T>*& node) {
    AVLNode<T>* c = node->left;
    node->left = c->right;
    c->right = node;

    // Update heights
    node->height = 1 + std::max(height(node->left), height(node->right));
    c->height = 1 + std::max(height(c->left), height(c->right));

    node = c;
}

template <class T>
void AVLTree<T>::rotateLeft(AVLNode<T>*& node) {
    AVLNode<T>* c = node->right;
    node->right = c->left;
    c->left = node;

    // Update heights
    node->height = 1 + std::max(height(node->left), height(node->right));
    c->height = 1 + std::max(height(c->left), height(c->right));

    node = c;
}

template <class T>
int AVLTree<T>::height(AVLNode<T>* root) {
    if (root == nullptr) {
        return 0;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return 1 + std::max(leftHeight, rightHeight);  // Using std::max here
}

template <class T>
int AVLTree<T>::getBalanceFactor(AVLNode<T>* root) {
    if (root == nullptr) {
        return 0;
    }
    return height(root->left) - height(root->right);
}

template <class T>
void AVLTree<T>::print(AVLNode<T>* root) {
    if (root == nullptr) {
        return;
    }
    print(root->left);  // Traverse left subtree
    T data = root->item;
    data.displayInfo();  // Print actor or movie info
    cout << endl;
    print(root->right);  // Traverse right subtree
}


template <class T> 
AVLNode<T>* AVLTree<T>::searchAVLById(AVLNode<T>* t,int id) {
    if (t == nullptr) {
        return nullptr;
    }
    else {
        if (t->key == id) {
            t->item.displayInfo();
            return t;
        }
        else {
            if (t->key < id) {
                return searchAVLById(t->right, id);
            }
            else {
                return searchAVLById(t->left, id);
            }
        }
    }
}


template <class T> 
AVLNode<T>* AVLTree<T>::searchAVLByName(string name) {
    // if the name is found in the root of the avltree
    if (root != nullptr) {
        if (root->item.getName() == name) {
            return root;
        }
        else {
            return searchAVLByName(root,name);
        }
    }
    else {
        return nullptr;
    }
}

template <class T>
AVLNode<T>* AVLTree<T>::searchAVLByName(AVLNode<T>* t, string name) {
    if (t == nullptr) {
        return nullptr; // Base case: If the node is null, return null
    }

    // Search in the left subtree first (In-Order Traversal)
    AVLNode<T>* leftResult = searchAVLByName(t->left, name);
    if (leftResult != nullptr) {
        return leftResult;
    }
    // Check the current node
    if (t->item.getName() == name) {
        return t; // Found the node, return it
    }

    // Search in the right subtree
    return searchAVLByName(t->right, name);
}

template <class T>
void AVLTree<T>::print() {
    print(root);
}

template <class T>
AVLNode<T>* AVLTree<T>::searchAVLById(int id) {
    return searchAVLById(root, id);
}


template <class T>
AVLNode<T>* AVLTree<T>::getRoot() {
    return root;
}

template <class T>
void AVLTree<T>::retrieveAll(Vector<AVLNode<T>*>& nodeList) {
    if (root != nullptr) {
        retrieveAll(root, nodeList);
    }
}
template <class T>

void AVLTree<T>::retrieveAll(AVLNode<T>* temp, Vector<AVLNode<T>*>& nodeList) {
    if (temp == nullptr) {
        return;
    }
    else {
        retrieveAll(temp->left, nodeList);
        cout << "This is temp: " << temp->item.getName() << endl;
        nodeList.pushBack(temp); // store the current node (after temp == nullptr, exits recursion)
        retrieveAll(temp->right, nodeList);
    }
}