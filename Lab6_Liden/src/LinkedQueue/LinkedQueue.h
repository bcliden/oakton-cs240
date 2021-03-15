#pragma once

/**
 * Linked Queue Header Templated Header and Implementation
 *
 * Written by Benjamin Liden for Prof. Temesvari's CS240 on 3/14.
 * Much borrowed from Dale Ch 5.
 *
 * 	New items: LinkedQueue.{begin, end}, templating
 */

#include <iostream>

#include "./LinkedQueueIterator.h"
#include "Node.h"

// "error" classes
class FullQueue {};
class EmptyQueue {};

template <class Item>
class LinkedQueue {
	public:
		// Class constructor.
		// Because there is a default constructor, the precondition
		// that the queue has been initialized is omitted.
		LinkedQueue();

		// Class destructor.
		~LinkedQueue();

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
		// Post: newItem is at rear of queue.
		void Enqueue(Item newItem);

		// Function: Removes front item from the queue and returns it in
		// item.
		// Post: If (queue is empty) EmptyQueue exception is thrown
		// and item is undefined
		// else front element has been removed from queue and
		// item is a copy of removed element.
		void Dequeue(Item &item);

		//Print function
		void Print(std::ostream& = std::cout);

		int GetLength();

	    LinkedQueueIterator<Item> begin();
	    LinkedQueueIterator<Item> end();

	private:
		Node<Item> *front;
		Node<Item> *rear;
};

// Constructor
template<class Item>
LinkedQueue<Item>::LinkedQueue() :
		front { nullptr }, rear { nullptr } {
}

// Destructor
template<class Item>
LinkedQueue<Item>::~LinkedQueue() {
	MakeEmpty();
}

// Member Functions
template<class Item>
void LinkedQueue<Item>::MakeEmpty() {
	Node<Item>* tempPtr;

	while (front != nullptr) {
		tempPtr = front;
		front = front->next;
		delete tempPtr;
	}

	rear = nullptr;
}

template<class Item>
bool LinkedQueue<Item>::IsEmpty() const {
	return front == nullptr;
}

template<class Item>
bool LinkedQueue<Item>::IsFull() const {
	// see if we can allocate a new node or not
	Node<Item> *location;
	try {
		location = new Node<Item>;
		delete location;
		return false;
	} catch (const std::bad_alloc &exception) {
		return true;
	}
}

template<class Item>
void LinkedQueue<Item>::Enqueue(Item newItem) {
	if (IsFull()) {
		throw FullQueue();
	}

	Node<Item> *newNode = new Node<Item>;
	newNode->info = newItem;
	newNode->next = nullptr;

	if (rear == nullptr) {
		front = newNode;
	} else {
		rear->next = newNode;
	}
	rear = newNode;
}

// remove item from the front of the queue
template<class Item>
void LinkedQueue<Item>::Dequeue(Item &item) {
	// remove front element
	if (IsEmpty()) {
		throw EmptyQueue();
	}
	Node<Item>* tempPtr;

	tempPtr = front;
	item = front->info;
	front = front->next;
	if (front == nullptr) {
		rear = nullptr;
	}
	delete tempPtr;
}

// print all steps, beginning at front
template<class Item>
void LinkedQueue<Item>::Print(std::ostream &out) {
	if (IsEmpty()) {
		out << "Queue is empty." << std::endl;
		return;
	}

	Node<Item> *location = front; // start at front
	while (location != nullptr) {
		out << location->info;
		location = location->next;
	}
	out << std::endl;
}

//
// The methods below provide the range-based for loop support. These would
// be customized with the companion LinkedQueueTypeIterator class that is returned.
//
template<class Item>
LinkedQueueIterator<Item> LinkedQueue<Item>::begin()
{
	return LinkedQueueIterator<Item>{ this->front };
}

template<class Item>
LinkedQueueIterator<Item> LinkedQueue<Item>::end()
{
	return LinkedQueueIterator<Item> { nullptr };
}
