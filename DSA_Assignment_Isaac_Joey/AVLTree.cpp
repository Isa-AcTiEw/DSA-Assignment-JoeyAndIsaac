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
void AVLTree<T>::insert(T *item) {
    int key = item->getKey();
    AVLNode<T>* avlNode = new AVLNode<T>();  // Correctly allocate memory for avlNode
    avlNode->key = key;
    avlNode->item = item;
    if (root == nullptr) {
        root = avlNode;
    }
    else {
        root = insertRecursive(root, key, item, avlNode);
    }
}

//template <class T>
//void AVLTree<T>::updateInsert(T* item, Vector<T*>& related) {
//    int key = item->getKey();
//    AVLNode<T>* avlNode = new AVLNode<T>();  // Correctly allocate memory for avlNode
//    avlNode->key = key;
//    avlNode->item = item;
//    for (int i = 0; i < related.getLength(); i++) {
//        avlNode->relatedPointers.pushBack(related[i]);
//    }
//    if (root == nullptr) {
//        root = avlNode;
//    }
//    else {
//        root = insertRecursive(root, key, item, avlNode);
//    }
//}
template <class T>
// insertion for AVL Tree 
AVLNode<T>* AVLTree<T>::insertRecursive(AVLNode<T>* node, int key, T* item, AVLNode<T>* newNode) {
    // insert recursively using bst property 
    if (node == nullptr) {
        return newNode;
    }
    if (key < node->key) {
        // insert the node to the left subtree of the avltree
        node->left = insertRecursive(node->left, key, item, newNode);
    }
    else {
        node->right = insertRecursive(node->right, key, item, newNode);
    }

    // balance factor 
    int bf = getBalanceFactor(node);

    // Rebalancing based on these four conditions 

    // left left case (tree is not right heavy and the node is inserted to the left subtree left subtree)
    if (bf > 1 && key < node->left->key) {
        return rotateRight(node);
    }
    
    // right right case (tree is not left heavy and the node is inserted to the right subtree right subtree)
    if (bf < -1 && key > node->right->key) {
        return rotateLeft(node);
    }
    // Condition for checking a left-right imbalance (tree is left heavy (bf > 1) and tree left subtree is right heavy bf < -1) 
    if (bf > 1 && key > node->left->key) {
        node-> left = rotateLeft(node->left);
        return rotateRight(node);
    }
    // Condition for checking a right-left imbalance (tree is right heavy (bf < -1) and tree right subtree is left heavy bf > 1)
    if (bf < -1 && key < node->right->key) {
        node-> right = rotateRight(node->right);
        return rotateLeft(node);
    }

    // Return the (unchanged) node pointer 
    return node;
}

template <class T>
AVLNode<T>* AVLTree<T>::rotateRight(AVLNode<T>* nodeN) {
    AVLNode<T>* c = nodeN->left;
    nodeN->left = c->right;
    c->right = nodeN;
    return c;
}

template <class T>
AVLNode<T>* AVLTree<T>::rotateLeft(AVLNode<T>* nodeN) {
    AVLNode<T>* c = nodeN->right;
    nodeN->right = c->left;
    c->left = nodeN;
    return c;
}

template <class T>
int AVLTree<T>::height(AVLNode<T>* root) {
    if (root == nullptr) {
        return -1;
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
    T* data = root->item;
    data->displayInfo();  // Print actor or movie info
    cout << endl;
    print(root->right);  // Traverse right subtree
}


template <class T>
AVLNode<T>* AVLTree<T>::searchAVLById(AVLNode<T>* t, int id) {
    if (t == nullptr) {
        return nullptr;
    }
    else {
        if (t->key == id) {
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
        if (root->item->getName() == name) {
            return root;
        }
        else {
            return searchAVLByName(root, name);
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
    if (t->item->getName() == name) {
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
        nodeList.pushBack(temp); // store the current node (after temp == nullptr, exits recursion)
        retrieveAll(temp->right, nodeList);
    }
}

template <class T>
AVLNode<T>* AVLTree<T>::removeNode(AVLNode<T>* t, int key) {
    if (t == nullptr) return t;

    if (key < t->key) {
        t->left = removeNode(t->left, key);
    }
    else if (key > t->key) {
        t->right = removeNode(t->right, key);
    }
    else {
        // Case 1: Node has no children (leaf node)
        if (t->left == nullptr && t->right == nullptr) {
            delete t;
            return nullptr;
        }
        // Case 2: Node has one child (only left or only right child)
        else if (t->left == nullptr) {
            AVLNode<T>* temp = t->right;
            delete t;
            return temp;
        }
        else if (t->right == nullptr) {
            AVLNode<T>* temp = t->left;
            delete t;
            return temp;
        }
        // Case 3: Node has two children
        else {
            AVLNode<T>* successor = t->right;
            AVLNode<T>* parent = t; // Keep track of successor's parent

            while (successor->left != nullptr) {
                parent = successor;
                successor = successor->left;
            }

            // Replace current node's key and item with successor's data
            t->key = successor->key;
            t->item = successor->item;

            // Remove the successor (it will either be a leaf or have one child)
            if (parent->left == successor) {
                parent->left = removeNode(successor, successor->key);
            }
            else {
                parent->right = removeNode(successor, successor->key);
            }
        }
    }

    // Ensure `t` is not nullptr before updating height or performing balancing
    if (t != nullptr) {
        // Update height of the current node
        t->height = 1 + max(height(t->left), height(t->right));

        int bf = getBalanceFactor(t); // Get the balance factor

        // Left-left case
        if (bf > 1 && t->left != nullptr && key < t->left->key) {
            return rotateRight(t);
        }

        // Right-right case
        if (bf < -1 && t->right != nullptr && key > t->right->key) {
            return rotateLeft(t);
        }

        // Left-right case
        if (bf > 1 && t->left != nullptr && t->left->right != nullptr && t->left->right->key == key) {
            t->left = rotateLeft(t->left);
            return rotateRight(t);
        }

        // Right-left case
        if (bf < -1 && t->right != nullptr && t->right->left != nullptr && t->right->left->key == key) {
            t->right = rotateRight(t->right);
            return rotateLeft(t);
        }
    }

    return t; // Return the updated node
}




template <class T>
void AVLTree<T>::remove(int key) {
    root = removeNode(root, key);
}

template <class T> 
// Function to check if the tree is balanced
bool AVLTree<T>::isBalanced(AVLNode<T>* root) {
    if (root == nullptr) return true;  // An empty tree is balanced

    // Calculate the balance factor of the current node
    int bf = getBalanceFactor(root);

    // Check if the balance factor is in the range of -1 to 1
    if (bf < -1 || bf > 1) return false;

    // Recursively check the left and right subtrees
    return isBalanced(root->left) && isBalanced(root->right);
}
