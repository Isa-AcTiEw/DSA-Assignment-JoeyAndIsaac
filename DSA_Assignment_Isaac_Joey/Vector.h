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
		Vector(int s, int c);
		bool pushBack(const T& item);
		bool deleteItem(T& item);
		T& const operator[](int index) const; // allows retrieval by list indices (read-only access)
		T& operator[](int index);
		void resize(int newCapacity);
		void print();
};

