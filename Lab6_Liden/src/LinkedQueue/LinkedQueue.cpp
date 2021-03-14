/**
 * Linked Queue Implementation
 *
 * Written by Benjamin Liden for Prof. Temesvari's CS240 on 3/13
 *
 * Initially written for Exercise 3,
 * 		updated for an iterator as part of Lab 6 (on 3/14/2020)
 *
 */

#include <new>
#include "LinkedQueue.h"
#include "LinkedQueueIterator.h"
#include "Node.h"

using LinkedQueueUtil::Node;
using LinkedQueueUtil::Item;

//struct Node {
//	ItemType info;
//	Node *next;
//};

// Constructors
LinkedQueue::LinkedQueue() :
		length { 0 }, rear { nullptr } {
}

LinkedQueue::LinkedQueue(const LinkedQueue &qt) :
		length { qt.length }, rear { nullptr } {
	if (qt.IsEmpty()) {
		return;
	}

	// Begin copy of incoming data
	Node* frontNode = qt.rear->next;
	Node* location = frontNode;

	// copy cells while location is NOT front
	do {
		this->Enqueue(location->info);
		location = location->next;
	} while (location != frontNode && location != nullptr);
}

LinkedQueue& LinkedQueue::operator=(const LinkedQueue &rhs) {
	if (this == &rhs) { // if same object, do nothing
		return *this;
	}
	if (!IsEmpty()) { // if this object isn't empty, make room
		this->MakeEmpty();
	}
	if (rhs.IsEmpty()) { // if incoming is empty, return now
		return *this;
	}

	// Begin copy of incoming data
	Node* frontNode = rhs.rear->next;
	Node* location = frontNode;

	// copy cells while location is NOT front
	do {
		this->Enqueue(location->info);
		location = location->next;
	} while (location != frontNode && location != nullptr);

	return *this;
}

// Destructor
LinkedQueue::~LinkedQueue() {
	MakeEmpty();
}

// Member Functions
void LinkedQueue::MakeEmpty() {
	if (IsEmpty()) {
		return;
	}
	Node* frontNode = rear->next;
	Node* location = rear->next;
	do {
		Node* temp = location->next; // store next node
		delete location; // delete current node
		location = temp; // point to next node
	} while (location != frontNode && location != nullptr); // stop if pointer is null or addr of first node
	length = 0;
}

bool LinkedQueue::IsEmpty() const {
	return rear == nullptr;
}

bool LinkedQueue::IsFull() const {
	// see if we can allocate a new node or not
	Node *location;
	try {
		location = new Node;
		delete location;
		return false;
	} catch (const std::bad_alloc &exception) {
		return true;
	}
}

/**
 * Add item onto the rear of the queue
 */
void LinkedQueue::Enqueue(Item newItem) {
	if (IsFull()) {
		throw FullQueue();
	}

	Node *newNode = new Node;
	newNode->info = newItem;
	newNode->next = nullptr;

	if (IsEmpty()) {
		rear = newNode;
		newNode->next = newNode;
	} else {
		Node *oldHead = rear->next; // save oldHead pointer
		rear->next = newNode; // point last element to newNode
		newNode->next = oldHead; // point newNode to oldHead
		rear = newNode; // change REAR pointer to newNode
	}
	++length;
}

// remove item from the front of the queue
void LinkedQueue::Dequeue(Item &item) {
	// remove front element
	if (IsEmpty()) {
		throw EmptyQueue();
	}

	Node *oldHead = rear->next; // get current head
	item = oldHead->info; // apply info into argument

	Node *newHead = oldHead->next; // get #2 element
	rear->next = newHead; // point rear to second element
	delete oldHead; // delete old front node
	--length;
}

// print all steps, beginning at front
void LinkedQueue::Print(std::ostream &out) {
	if (IsEmpty()) {
		out << "Queue is empty." << std::endl;
		return;
	}

	Node *frontNode = rear->next;
	Node *location = frontNode; // start at front
	do {
		out << location->info << " "; // print info in node
		location = location->next; // advance to next node
	} while (location != nullptr && location != frontNode); // loop while location isn't front or null
	out << std::endl;
}

//
// The methods below provide the range-based for loop support. These would
// be customized with the companion LinkedQueueTypeIterator class that is returned.
//
LinkedQueueIterator LinkedQueue::begin()
{
	//Complete this.
}

LinkedQueueIterator LinkedQueue::end()
{
	//Complete this.
}
