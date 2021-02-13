/**
 * LinkedListUnsortedType implementation
 *
 * Please see added Print and SplitLists functionality.
 * There is also an added Copy Constructor: LinkedList(const LinkedList&)
 *
 * Written by Benjamin Liden
 * 		for Prof. I. Temesvari's CS240 course.
 * 		Exercise 2.
 */
#include "linked_unsorted.h"

using namespace Item;

struct NodeType {
	ItemType info;
	NodeType *next;
};

LinkedListUnsortedType::LinkedListUnsortedType()  // Class constructor
{
	length = 0;
	listData = nullptr;
	currentPos = nullptr; // if I don't initialize it here, get a garbage ptr
}

LinkedListUnsortedType::LinkedListUnsortedType(const LinkedListUnsortedType& list) {
	length = list.length;
	currentPos = nullptr; // initialize with no current position

	if (list.listData == nullptr) { // if list is null, return immediately
		listData = nullptr;
		return;
	}

	// -------------- copying the list -------------- //

	// head of incoming list
	NodeType* trackingPtr = list.listData; // we will track the whole structure using this pointer

	// clone first element
	NodeType* newList = new NodeType;
	newList->info = trackingPtr->info;
	newList->next = nullptr;

	// if this el matches the currentPos, set it on this instance too
	if (trackingPtr == list.currentPos) {
		currentPos = newList;
	}

	// advance incoming list after above read
	trackingPtr = trackingPtr->next;
	// keep head element ref to be later listData
	NodeType* head = newList;

	// walk list, adding as we can
	while (trackingPtr != nullptr) {
		// make new Node on next ptr
		newList->next = new NodeType;
		// then move ptr to it
		newList = newList->next;

		// clone item and set next to nullptr (always)
		newList->info = trackingPtr->info;
		newList->next = nullptr;

		// if this el matches the currentPos, set it on new instance too
		if (trackingPtr == list.currentPos) {
			currentPos = newList;
		}

		// then advance incoming list
		trackingPtr = trackingPtr->next;
	}

	// finally, return head of newList
	listData = head;

}

bool LinkedListUnsortedType::IsFull() const
// Returns true if there is no room for another ItemType
//  on the free store; false otherwise.
{
	NodeType *location;
	try {
		location = new NodeType;
		delete location;
		return false;
	} catch (const std::bad_alloc &exception) {
		return true;
	}
}

int LinkedListUnsortedType::GetLength() const
// Post: Number of items in the list is returned.
{
	return length;
}

void LinkedListUnsortedType::MakeEmpty()
// Post: List is empty; all items have been deallocated.
{
	NodeType *tempPtr;

	while (listData != nullptr) {
		tempPtr = listData;
		listData = listData->next;
		delete tempPtr;
	}
	length = 0;
}
void LinkedListUnsortedType::PutItem(ItemType item)
// item is in the list; length has been incremented.
		{
	NodeType *location;			// Declare a pointer to a node

	location = new NodeType;		// Get a new node
	location->info = item;		// Store the item in the node
	location->next = listData;	// Store address of first node
	//   in next field of new node
	listData = location;		// Store address of new node into
	//   external pointer
	length++;				// Increment length of the list
}

ItemType LinkedListUnsortedType::GetItem(ItemType &item,
		bool &found)
// Pre:  Key member(s) of item is initialized.
// Post: If found, item's key matches an element's key in the 
//       list and a copy of that element has been stored in item;
//       otherwise, item is unchanged. 
		{
	bool moreToSearch;
	NodeType *location;

	location = listData;
	found = false;
	moreToSearch = (location != nullptr);

	while (moreToSearch && !found) {
		switch (item.ComparedTo(location->info)) {
		case LESS:
		case GREATER:
			location = location->next;
			moreToSearch = (location != nullptr);
			break;
		case EQUAL:
			found = true;
			item = location->info;
			break;
		}
	}
	return item;
}

void LinkedListUnsortedType::DeleteItem(ItemType item)
// Pre:  item's key has been initialized.
//       An element in the list has a key that matches item's.
// Post: No element in the list has a key that matches item's.
		{
	NodeType *location = listData;
	NodeType *tempLocation;

	// Locate node to be deleted.
	if (item.ComparedTo(listData->info) == EQUAL) {
		tempLocation = location;
		listData = listData->next;		// Delete first node.
	} else {
		while (item.ComparedTo((location->next)->info) != EQUAL)
			location = location->next;

		// Delete node at location->next
		tempLocation = location->next;
		location->next = (location->next)->next;
	}
	delete tempLocation;
	length--;
}

void LinkedListUnsortedType::ResetList()
// Post: Current position has been initialized.
{
	currentPos = nullptr;
}

const ItemType LinkedListUnsortedType::GetNextItem()
// Post:  A copy of the next item in the list is returned.
//        When the end of the list is reached, currentPos
//        is reset to begin again.
{
	ItemType item;
	if (currentPos == nullptr)
		currentPos = listData;
	else
		currentPos = currentPos->next;
	item = currentPos->info;
	return item;
}

LinkedListUnsortedType::~LinkedListUnsortedType()
// Post: List is empty; all items have been deallocated.
{
	NodeType *tempPtr;

	while (listData != nullptr) {
		tempPtr = listData;
		listData = listData->next;
		delete tempPtr;
	}
}

void LinkedListUnsortedType::Print(std::ostream &out) {
	this->ResetList();

	int length = this->GetLength();
	for (int i = 0; i < length; i++) {
		this->GetNextItem().Print(out);

		// if not last item, print a comma
		if (i + 1 != length) {
			out << ", ";
		}
	}
}

void LinkedListUnsortedType::SplitLists(LinkedListUnsortedType list,
		const ItemType item, LinkedListUnsortedType &lesserList,
		LinkedListUnsortedType &greaterList) {

	// must reset so we know the pointer is null
	list.ResetList();

	// for every element in list
	for (int i = 0; i < list.GetLength(); i++) {
		ItemType currentItem = list.GetNextItem();

		// check comparison against item
		RelationType relation = currentItem.ComparedTo(item);

		// then push to lesser or greater lists
		switch (relation) {
		case RelationType::LESS:
		case RelationType::EQUAL:
			lesserList.PutItem(currentItem);
			break;
		case RelationType::GREATER:
			greaterList.PutItem(currentItem);
			break;
		}
	}
}

