#include "Queue.h"
#include <iostream>
using namespace std;
Queue::Node::Node(ItemType item) : item(item), next(nullptr) {

};

// Default constructor and destructor 
Queue::Queue() {};

Queue::~Queue() {
	while (isEmpty() == false) {
		// Dequeue all the elements 
		dequeue();
	}
	cout << "All memory have been freed from the nodes in the queue" << endl;
};


// Methods for the queue 

// Enqueue Method 
// If the queue is empty then it assigns the frontNode and backNode to the first node added 
// Since the queue contains a reference to the front and rear node it is not necessary to traverse the linked list. Basically update the backNode to the newNode in this function
// This is because items are dequeued from the front and enqueued from the rear a queue is a FIFO Data Structure 

bool Queue::enqueue(ItemType item) {
	if (isEmpty() == true) {
		// Create a new Node and then assign the front and rear node to the first node created 
		Node* newNode = new Node(item);
		// Always remember that frontNode is a pointer to the first node in the queue (memory address of the first node)
		frontNode = newNode;
		// Next we link the next prop of backNode next pointer to point to frontNode (my front and back is connected at first -> points to same node)
		backNode = newNode;
		return true;
	}
	else {
		// The queue is not empty then we create a newNode and then point the current backNode to the newNode, update the backNode value
		Node* newNode = new Node(item);
		// Set to nullptr since the currentBackNode is the last node in the list 
		backNode->next = newNode;
		backNode = newNode;
		return true;
	}
}

bool Queue::dequeue() {
	if (isEmpty() == true) {
		cout << "Unable to dequeue the items as the queue is empty" << endl;
		return false;
	}
	else {
		// Create a temp node to store the current Frontnode 
		Node* temp = frontNode;
		frontNode = temp->next;
		delete temp; // free the memory used by the pointer 
		return true;
	}
}

bool Queue::dequeue(ItemType& item) {
	if (isEmpty() == true) {
		cout << "Unable to dequeue the items as the queue is empty" << endl;
		return false;
	}
	else {
		// Create a temp node to store the current Frontnode 
		Node* temp = frontNode;
		frontNode = temp->next;
		item = temp->item;
		delete temp; // free the memory used by the pointer 
		return true;
	}
}
bool Queue::isEmpty() {
	if (frontNode == nullptr) {
		return true;
	}
	else {
		return false;
	}
}

void Queue::getFront(ItemType& item) {
	if (!isEmpty()) {
		item = frontNode->item;
	}
	else {
		cout << "There is no front node as the queue is empty" << endl;
	}
}

void Queue::displayItems() {
	if (isEmpty() == true) {
		// Then log a message saying that the queue is empty 
		cout << "There is no items in the queue unable to display items in the queue please add an item before displaying " << endl;
	}
	else {
		// Start to display them 
		Node* temp = frontNode;
		while (temp->next != nullptr) {
			// Then we print the current value stored in temp 
			cout << temp->item << endl;
			temp = temp->next;
		}
		// Print the last element in the queue
		cout << "Rear element: " << temp->item << endl;
	}
}
