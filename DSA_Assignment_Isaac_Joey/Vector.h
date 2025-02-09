// Team Member 1: Isaac Tiew Xun Yong (S10257760G)
#pragma once
template <class T>
class Vector
{
	private:
		T* dynamicArray;
		int size;
		int capacity;
	public:
		Vector();
		/*
		* Constructor for the vector class takes it an input size used to determine 
		* the number of elements in the vector at the start, the type item to be assigned
		  to each index in the vector 
		*/
		Vector(int s, T item);
		/*
		* The pushBack opertion increments the size index as long as size <= capacity this allows for new items 
		* to be inserted at the rear of the vector O(1) operation, If the size exceeds the given capacity the resize operation
		* is being called on the vector thus making it an O(n) opertion
		*/
		bool pushBack(T item);
		/*
		* Overloading operators for retrieval of items in the vector
		*/
		T& const operator[](int index) const; // allows retrieval by list indices (read-only access)
		T& operator[](int index);
		bool pushBack(T* item);
		/*
		* The resize operation takes the given argument newCapacity which is the new maximum amount of items that can be stored in the vector, it allocates
		* new memory for the dynamicArray in the vector class based on its given capacity, it copies all the original items of the old vector to the new vector 
		* deletes (free) the memory allocated to the dynamicArray. This operation is O(n) where n is the size of the elements in the original vector 
		*/
		void resize(int newCapacity);
		int getLength();
};

