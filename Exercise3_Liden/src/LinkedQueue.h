#pragma once

/**
 * Linked Queue Header
 *
 * Written by Benjamin Liden for Prof. Temesvari's CS240 on 3/13
 */

#include <iostream>

// "error" classes
class FullQueue {};
class EmptyQueue {};

typedef int ItemType;
struct NodeType;

class LinkedQueue {
	public:
		// Class constructor.
		// Because there is a default constructor, the precondition
		// that the queue has been initialized is omitted.
		LinkedQueue();

		// Copy Constructor
		LinkedQueue(const LinkedQueue &qt);

		//Overloaded assignment operator=
		LinkedQueue& operator=(const LinkedQueue &rhs);

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
		void Enqueue(ItemType newItem);

		// Function: Removes front item from the queue and returns it in
		// item.
		// Post: If (queue is empty) EmptyQueue exception is thrown
		// and item is undefined
		// else front element has been removed from queue and
		// item is a copy of removed element.
		void Dequeue(ItemType &item);

		//Print function
		void Print(std::ostream& = std::cout);

		int GetLength();

	private:
		int length;
		NodeType *rear;
};
