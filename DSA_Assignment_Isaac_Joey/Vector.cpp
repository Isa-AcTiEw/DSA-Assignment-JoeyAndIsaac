// Team Member 1: Isaac Tiew Xun Yong (S10257760G)
#include "Vector.h"
#include "Actor.h"
#include "Movie.h"
#include <iostream>
#include "AVLTree.h"
using namespace std;

// explicit template class definitions 
template class Vector<int>;
template class Vector<bool>;
template class Vector<Vector<int>>;
template class Vector<Movie*>;
template class Vector<Actor*>;
template class Vector<string>;
template class Vector<AVLNode<Movie>*>;
template class Vector<AVLNode<Actor>*>;

template <class T>
Vector<T>::Vector() : size(0), capacity(40) {
	dynamicArray = new T[capacity];  // Initialize the dynamic array with the specified capacity
}
template <class T>
Vector<T>::Vector(int cap, T item) {
	capacity = cap;
	size = cap;  // Fill the array with 'cap' copies of 'item'
	dynamicArray = new T[capacity];
	for (int i = 0; i < size; i++) {
		dynamicArray[i] = item;  // Fill array with 'item'
	}
}
template <class T>

// Precondition: The index must be withing the size of the array 
// Postcondition: Returns an immutable reference of the item stored in the array 
// Time Complexity: O(1) since vector data structures allow for indexed retrieval it does not traverse the entire array
T& Vector<T>::operator[](int index) const{
	if (index >= 0 && index < size) {
		return dynamicArray[index];
	}
	else {
		cout << "Index is out of range" << endl;
	}
}

template <class T>
T& Vector<T>::operator[](int index) {
	if (index <= capacity) {
		return dynamicArray[index];
	}
	else {
		cout << "Index is out of range" << endl;
	}
}


// Precondition: none 
// Postcondition: The size of the array increases and if the element inserted to the array exceeds the maximum capacity, the capacity
// increases exponentially due to the parameters passed in 
// Time Complexity: Worst-Case O(n+1) : copy the array into the new array and allocate new memory, insert the element at size + 1 pos O(1)
// Average Case: O(1) time - complexity: i increase the index of size (insertion at rear) no shifting of elements necessary
template<class T>
bool Vector<T>::pushBack(T item) {
	if (size >= capacity) {
		// call resize function (to allocate new memory for new aray items)
		resize(capacity * 2); // increase the capacity exponentially each time i exceed or run out of memory 
	}
	dynamicArray[size] = item;
	size++; // increase the size of the array after adding a new element 
	return true;
}

template <class T>
bool Vector<T>::pushBack(T* item) {
	// Check if the current size exceeds the capacity
	if (size >= capacity) {
		// Call resize function to allocate new memory with double the current capacity
		resize(capacity * 2); // Increase capacity exponentially
	}

	// Insert the item at the current size (end of the array)
	dynamicArray[size] = *item;

	// Increment the size after adding the new element
	size++;

	return true;
}


// Precondition: size must be equivalent to capacity (no more memory to allocate new elements in the array)
// Postcondition: capacity increases exponentially, the pointer to the original array is deleted, memory allocated to temp is freed 
// Time complexity: O(n) , dependant on the size of the current array 
template <class T>
void Vector<T>::resize(int newCapacity) {
	// Allocate new memory first
	T* newArray = new T[newCapacity];
	// Copy existing elements to the new array
	for (size_t i = 0; i < size; i++) {
		newArray[i] = dynamicArray[i];
	}

	// Delete old memory
	delete[] dynamicArray;

	// Reassign dynamicArray to the new array
	dynamicArray = newArray;

	// Update the capacity
	capacity = newCapacity;
}


// Function to print all elements in the array

template <class T>

int Vector<T>::getLength() {
	return size;
}

