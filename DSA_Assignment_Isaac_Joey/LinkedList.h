#pragma once
#include "AVLTree.h"

template <typename T>

class Vector
{
	private:
		struct Node {
			Node* next;
			AVLNode<T>* referencedNode;
		};

	public:
		insertAtHead(AVLNode<T>*);
};

