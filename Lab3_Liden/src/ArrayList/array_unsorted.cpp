/**
 * 	ArrayBackedUnsortedType implementation.
 *
 * 	(note: some work carried over from Ex2, Lab2, and Lab3)
 *
 * 	Please see ShiftRight and improved delete functionalities.
 *
 * 	Written for Prof. I. Temesvari's CS240 at Oakton CC.
 *	Author: Benjamin Liden
 */

#include "../ItemType.h"
#include "array_unsorted.h"

using Item::ItemType;
using Item::RelationType;

ArrayBackedUnsortedType::ArrayBackedUnsortedType() {
	length = 0;
	currentPos = -1;
}

bool ArrayBackedUnsortedType::IsFull() const {
	return (length == Item::MAX_ITEMS);
}

int ArrayBackedUnsortedType::GetLength() const {
	return length;
}

ItemType ArrayBackedUnsortedType::GetItem(ItemType item,
		bool &found)
// Pre:  Key member(s) of item is initialized. 
// Post: If found, item's key matches an element's key in the 
//       list and a copy of that element has been returned;
//       otherwise, item is returned. 
		{

	bool moreToSearch;
	int location = 0;
	found = false;

	moreToSearch = (location < length);

	while (moreToSearch && !found) {
		switch (item.ComparedTo(info[location])) {
		case RelationType::LESS:
		case RelationType::GREATER:
			location++;
			moreToSearch = (location < length);
			break;
		case RelationType::EQUAL:
			found = true;
			item = info[location];
			break;
		}
	}
	return item;
}

void ArrayBackedUnsortedType::MakeEmpty()
// Post: list is empty.
{
	length = 0;
}

void ArrayBackedUnsortedType::PutItem(ItemType item)
// Post: item is in the list.
		{
	info[length] = item;
	length++;
}

// This is the original textbook implementation of DeleteItem
//void ArrayBackedUnsortedType::DeleteItem(Item::ItemType item)
//// Pre:  item's key has been initialized.
////       An element in the list has a key that matches item's.
//// Post: No element in the list has a key that matches item's.
//		{
//
//	int location = 0;
//
//	while (item.ComparedTo(info[location]) != RelationType::EQUAL)
//		location++;
//
//	info[location] = info[length - 1];
//	length--;
//}

void ArrayBackedUnsortedType::DeleteItem(ItemType itemToDelete) {
	int position = 0;

	while (position < this->length) { // while we aren't at the end of the array...
		ItemType* currentItem = &info[position]; // get cheap pointer to current item
 		if(itemToDelete.ComparedTo(*currentItem) == RelationType::EQUAL){ // if elements are equal...
 			// "delete" the item
			*currentItem = info[this->length - 1]; // last element into this slot
	 		this->length -= 1;
	 		// do NOT decrement position. We need to check the element we just swapped in!
		} else { // otherwise, increment position and keep going
			position += 1;
		}
	}
}

void ArrayBackedUnsortedType::ResetList()
// Post: currentPos has been initialized.
{
	currentPos = -1;
}

Item::ItemType ArrayBackedUnsortedType::GetNextItem()
// Pre:  ResetList was called to initialized iteration.
//       No transformer has been executed since last call.
//       currentPos is defined.
// Post: item is current item.
//       Current position has been updated.
{
	currentPos++;
	return info[currentPos];
}

void ArrayBackedUnsortedType::Print(std::ostream &out) {
	this->ResetList();

	int length = this->GetLength();
	for (int i = 0; i < length; i++) {
		this->GetNextItem().Print(out);

		// if not last item, print a comma
		if (i + 1 != length) {
			out << ", ";
		}
	}
	out << std::endl;
}

void ArrayBackedUnsortedType::ShiftRight(){
	int length = this->GetLength();

	// start at array end.
	int position = length;
	// save last element to be HEAD element later
	Item::ItemType newHead = info[length - 1];

	// while we aren't back at the beginning, swap elements and decrement position
	while (position > 0) {
		// move nextPositon onto current position
		info[position] = info[position - 1];
		// decrement current position
		position -= 1;
	}

	// finally, put the saved element into the head slot
	info[0] = newHead;
}
