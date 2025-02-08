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
		Vector(int s, T item);
		bool pushBack(T item);
		T& const operator[](int index) const; // allows retrieval by list indices (read-only access)
		T& operator[](int index);
		bool pushBack(T* item);
		void resize(int newCapacity);
		int getLength();
};

