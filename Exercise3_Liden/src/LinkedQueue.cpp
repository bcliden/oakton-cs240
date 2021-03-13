/**
 * Linked Queue Implementation
 *
 * Written by Benjamin Liden for Prof. Temesvari's CS240 on 3/13
 *
 * no add'l help used (some textbook reference)
 */

#include <new>
#include "LinkedQueue.h"

struct NodeType {
	ItemType info;
	NodeType *next;
};

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
	NodeType* frontNode = qt.rear->next;
	NodeType* location = frontNode;

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
	NodeType* frontNode = rhs.rear->next;
	NodeType* location = frontNode;

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
	NodeType* frontNode = rear->next;
	NodeType* location = rear->next;
	do {
		NodeType* temp = location->next; // store next node
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
	NodeType *location;
	try {
		location = new NodeType;
		delete location;
		return false;
	} catch (const std::bad_alloc &exception) {
		return true;
	}
}

/**
 * Add item onto the rear of the queue
 */
void LinkedQueue::Enqueue(ItemType newItem) {
	if (IsFull()) {
		throw FullQueue();
	}

	NodeType *newNode = new NodeType;
	newNode->info = newItem;
	newNode->next = nullptr;

	if (IsEmpty()) {
		rear = newNode;
		newNode->next = newNode;
	} else {
		NodeType *oldHead = rear->next; // save oldHead pointer
		rear->next = newNode; // point last element to newNode
		newNode->next = oldHead; // point newNode to oldHead
		rear = newNode; // change REAR pointer to newNode
	}
	++length;
}

// remove item from the front of the queue
void LinkedQueue::Dequeue(ItemType &item) {
	// remove front element
	if (IsEmpty()) {
		throw EmptyQueue();
	}

	NodeType *oldHead = rear->next; // get current head
	item = oldHead->info; // apply info into argument

	NodeType *newHead = oldHead->next; // get #2 element
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

	NodeType *frontNode = rear->next;
	NodeType *location = frontNode; // start at front
	do {
		out << location->info << " "; // print info in node
		location = location->next; // advance to next node
	} while (location != nullptr && location != frontNode); // loop while location isn't front or null
	out << std::endl;
}
