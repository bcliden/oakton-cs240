#pragma once

//============================================================================
// Name        : Exercise 4
// Author      : Benjamin Liden
// Date		   : April 5, 2021
// Professor   : Ivan Temesvari
// Class       : CS240
//============================================================================

// this class is mostly untouched

#include <new>
#include <cstddef>

class FullQueue {
};

class EmptyQueue {
};

template<class T>
struct NodeType;

template<class T>
class QueType {
public:
	QueType();
	// Class constructor.
	// Because there is a default constructor, the precondition
	// that the queue has been initialized is omitted.
	QueType(int max);
	// Parameterized class constructor.
	~QueType();
	// Class destructor.
	QueType(const QueType<T> &anotherQue);
	// Copy constructor
	void MakeEmpty();
	// Function: Initializes the queue to an empty state.
	// Post: Queue is empty.
	bool IsEmpty() const;
	// Function: Determines whether the queue is empty.
	// Post: Function value = (queue is empty)
	bool IsFull() const;
	// Function: Determines whether the queue is full.
	// Post: Function value = (queue is full)
	void Enqueue(T newItem);
	// Function: Adds newItem to the rear of the queue.
	// Post: If (queue is full) FullQueue exception is thrown
	//       else newItem is at rear of queue.
	void Dequeue(T &item);
	// Function: Removes front item from the queue and returns it in item.
	// Post: If (queue is empty) EmptyQueue exception is thrown
	//       and item is undefined
	//       else front element has been removed from queue and
	//       item is a copy of removed element.
private:
	NodeType<T> *front;
	NodeType<T> *rear;
};

template<class T>
struct NodeType {
	T info;
	NodeType *next;
};

template<class T>
QueType<T>::QueType()          // Class constructor.
// Post:  front and rear are set to nullptr.
{
	front = nullptr;
	rear = nullptr;
}

template<class T>
void QueType<T>::MakeEmpty()
// Post: Queue is empty; all elements have been deallocated.
{
	NodeType<T> *tempPtr;

	while (front != nullptr) {
		tempPtr = front;
		front = front->next;
		delete tempPtr;
	}
	rear = nullptr;
}

// Class destructor.
template<class T>
QueType<T>::~QueType() {
	MakeEmpty();
}

template<class T>
bool QueType<T>::IsFull() const
// Returns true if there is no room for another T
//  on the free store; false otherwise.
{
	NodeType<T> *location;
	try {
		location = new NodeType<T>;
		delete location;
		return false;
	} catch (std::bad_alloc&) {
		return true;
	}
}

template<class T>
bool QueType<T>::IsEmpty() const
// Returns true if there are no elements on the queue; false otherwise.
{
	return (front == nullptr);
}

template<class T>
void QueType<T>::Enqueue(T newItem)
// Adds newItem to the rear of the queue.
// Pre:  Queue has been initialized.
// Post: If (queue is not full) newItem is at the rear of the queue;
//       otherwise a FullQueue exception is thrown.

		{
	if (IsFull())
		throw FullQueue();
	else {
		NodeType<T> *newNode;

		newNode = new NodeType<T>;
		newNode->info = newItem;
		newNode->next = nullptr;
		if (rear == nullptr)
			front = newNode;
		else
			rear->next = newNode;
		rear = newNode;
	}
}

template<class T>
void QueType<T>::Dequeue(T &item)
// Removes front item from the queue and returns it in item.
// Pre:  Queue has been initialized and is not empty.
// Post: If (queue is not empty) the front of the queue has been
//       removed and a copy returned in item;
//       othersiwe a EmptyQueue exception has been thrown.
		{
	if (IsEmpty())
		throw EmptyQueue();
	else {
		NodeType<T> *tempPtr;

		tempPtr = front;
		item = front->info;
		front = front->next;
		if (front == nullptr)
			rear = nullptr;
		delete tempPtr;
	}
}

template<class T>
QueType<T>::QueType(const QueType<T> &anotherQue) {
	NodeType<T> *ptr1;
	NodeType<T> *ptr2;

	if (anotherQue.front == nullptr)
		front = nullptr;
	else {
		front = new NodeType<T>;
		front->info = anotherQue.front->info;
		ptr1 = anotherQue.front->next;
		ptr2 = front;
		while (ptr1 != nullptr) {
			ptr2->next = new NodeType<T>;
			ptr2 = ptr2->next;
			ptr2->info = ptr1->info;
			ptr1 = ptr1->next;
		}
		ptr2->next = nullptr;
		rear = ptr2;
	}
}
