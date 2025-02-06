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
AVLNode<T>* AVLTree<T>::removeNode(AVLNode<T>* root, int key) {
    if (root == nullptr) return root;

    if (key < root->key) {
        root->left = removeNode(root->left, key);
    }
    else if (key > root->key) {
        root->right = removeNode(root->right, key);
    }
    else {
        // Found node to be deleted
        if (root->left == nullptr) {
            AVLNode<T>* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            AVLNode<T>* temp = root->left;
            delete root;
            return temp;
        }

        // Node with two children: find in-order successor
        AVLNode<T>* temp = root->right;
        while (temp->left != nullptr) temp = temp->left;

        root->key = temp->key;
        root->item = temp->item;
        root->right = removeNode(root->right, temp->key);
    }

    return root;  // Return the new root
}

template <class T>
void AVLTree<T>::remove(int key) {
    root = removeNode(root, key);
}
