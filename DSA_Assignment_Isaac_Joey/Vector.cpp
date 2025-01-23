#include "Vector.h"
#include <iostream>
using namespace std;

// explicit template class definitions 
template class Vector<int>;

template <class T>
Vector<T>::Vector() : size(0), capacity(40) {
	dynamicArray = new T[capacity];  // Initialize the dynamic array with the specified capacity
}
template <class T>

// Precondition: The index must be withing the size of the array 
// Postcondition: Returns an immutable reference of the item stored in the array 
// Time Complexity: O(1) since vector data structures allow for indexed retrieval it does not traverse the entire array
T& Vector<T>::operator[](int index) const{
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
bool Vector<T>::pushBack(const T& item) {
	if (size == capacity) {
		// call resize function (to allocate new memory for new aray items)
		resize(capacity * 2); // increase the capacity exponentially each time i exceed or run out of memory 
	}
	dynamicArray[size] = item;
	size++; // increase the size of the array after adding a new element 
	return true;
}

// Precondition: size must be equivalent to capacity (no more memory to allocate new elements in the array)
// Postcondition: capacity increases exponentially, the pointer to the original array is deleted, memory allocated to temp is freed 
// Time complexity: O(n) , dependant on the size of the current array 
template <class T>
void Vector<T>::resize(int newCapacity) {
	// copy the elements from the old array 
	// assign new allocated memory to the new array 
	// delete the temp array 
	// dynamicArray = newArray
	T* temp = dynamicArray;
	
	// allocate new memory 
	dynamicArray = new T[newCapacity];

	// copy 
	for (int i = 0; i < size; i++) {
		dynamicArray[i] = temp[i];
	}
	// free the memory at temp (pointing to old memory referenced by dynamicArray)
	delete[] temp;
}

// Function to print all elements in the array
template <class T>
void Vector<T>::print() {
	for (int i = 0; i < size; i++) {
		cout << dynamicArray[i] << endl;
	}
}