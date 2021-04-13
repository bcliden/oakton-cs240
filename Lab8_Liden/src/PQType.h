#pragma once

// Definition of class PQType, which represents the Priority Queue ADT

#include <iostream>
#include "Heap.h"

class FullPQ {
};
class EmptyPQ {
};

constexpr int MAX_ITEMS = 10;

template<class T>
class PQType {
public:
	PQType();			//default constructor
	PQType(int);        // parameterized class constructor
	~PQType();          // class destructor

	PQType operator=(const PQType &rhs);

	// Function: Initializes the queue to an empty state.
	// Post: Queue is empty.
	void MakeEmpty();

	// Function: Determines whether the queue is empty.
	// Post: Function value = (queue is empty)
	bool IsEmpty() const;

	// Function: Determines whether the queue is full.
	// Post: Function value = (queue is full)
	bool IsFull() const;

	// Function: Adds newItem to the rear of the queue.
	// Post: if (the priority queue is full) exception FullPQ is thrown;
	//       else newItem is in the queue.
	void Enqueue(T newItem);

	// Function: Removes element with highest priority from the queue
	// and returns it in item.
	// Post: If (the priority queue is empty) exception EmptyPQ is thrown;
	//       else highest priority element has been removed from queue.
	//       item is a copy of removed element.
	void Dequeue(T &item);

	template<class ItemPQ>
	friend std::ostream& operator<<(std::ostream &out,
			const PQType<ItemPQ> &pq);
private:
	int length;
	HeapType<T> items;
	int maxItems;
};

template<class T>
PQType<T>::PQType() {
	maxItems = MAX_ITEMS;
	items.elements = new T[maxItems];
	length = 0;
}

template<class T>
PQType<T>::PQType(int max) {
	maxItems = max;
	items.elements = new T[maxItems];
	length = 0;
}

template<class T>
PQType<T> PQType<T>::operator=(const PQType<T> &rhs) {
	//assignment operator=
	if (this == &rhs) {
		return *this;
	} else {
		//delete old contents of this
		delete[] items.elements;
		length = 0;
		maxItems = rhs.maxItems;
		items.elements = new T[rhs.maxItems];

		//copy new contents over to this from rhs
		int count = 0;
		while (count < rhs.length) {
			items.elements[count] = rhs.items.elements[count];
			count++;
		}
	}
	return *this;
}

template<class T>
void PQType<T>::MakeEmpty() {
	length = 0;
}

template<class T>
PQType<T>::~PQType() {
	delete[] items.elements;
}
template<class T>
void PQType<T>::Dequeue(T &item)
// Post: element with highest priority has been removed 
//       from the queue; a copy is returned in item.
		{
	if (length == 0)
		throw EmptyPQ();
	else {
		item = items.elements[0];
		items.elements[0] = items.elements[length - 1];
		length--;
		items.ReheapDown(0, length - 1);
	}
}

template<class T>
void PQType<T>::Enqueue(T newItem)
// Post: newItem is in the queue.
		{
	if (length == maxItems)
		throw FullPQ();
	else {
		length++;
		items.elements[length - 1] = newItem;
		items.ReheapUp(0, length - 1);
	}
}
template<class T>
bool PQType<T>::IsFull() const
// Post: Returns true if the queue is full; false, otherwise.
{
	return length == maxItems;
}

template<class T>
bool PQType<T>::IsEmpty() const
// Post: Returns true if the queue is empty; false, otherwise.
{
	return length == 0;
}

template<class T>
std::ostream& operator<<(std::ostream &out, const PQType<T> &pq) {
	for (int i = 0; i < pq.length; i++) {
		out << pq.items.elements[i] << std::endl;
	}
	return out;
}
