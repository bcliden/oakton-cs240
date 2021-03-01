/**
 * Modified by Benjamin Liden
 * 	on 2/27/21
 * 	for Prof. Temesvari's CS240
 *
 * 	Original file from: CS240SortedArray.zip
 *
 * 	See added private member function: doubleArray
 * 	See added destructor
 */

#include "sorted_array.h"

std::ostream& operator<<(std::ostream &out, const SortedType &list) {
	if (list.length == 0) {
		out << "Empty list.";
	}
	for (int i = 0; i < list.length; i++) {
		list.info[i].Print(out);
		out << " ";
	}
	out << std::endl;
	return out;
}

SortedType::SortedType() {
	MAX_ITEMS = 5;
	info = new ItemType[MAX_ITEMS];
	currentPos = -1;
	length = 0;
}

// added necessary destructor dynamic memory is in use
SortedType::~SortedType() {
	delete[] info;
}

void SortedType::MakeEmpty() {
	length = 0;
}

bool SortedType::IsFull() const {
	return (length == MAX_ITEMS);
}

int SortedType::GetLength() const {
	return length;
}

int SortedType::GetMaxLength() const {
	return MAX_ITEMS;
}

ItemType SortedType::GetItem(ItemType item, bool &found) {
	int midPoint;
	int first = 0;
	int last = length - 1;

	bool moreToSearch = first <= last;
	found = false;
	while (moreToSearch && !found) {
		midPoint = (first + last) / 2;
		switch (item.ComparedTo(info[midPoint])) {
		case LESS:
			last = midPoint - 1;
			moreToSearch = first <= last;
			break;
		case GREATER:
			first = midPoint + 1;
			moreToSearch = first <= last;
			break;
		case EQUAL:
			found = true;
			item = info[midPoint];
			break;
		}
	}
	return item;
}

void SortedType::DeleteItem(ItemType item) {
	int location = 0;

	while (item.ComparedTo(info[location]) != EQUAL)
		location++;
	for (int index = location + 1; index < length; index++)
		info[index - 1] = info[index];
	length--;
}

void SortedType::PutItem(ItemType item) {
	bool moreToSearch;
	int location = 0;

	// If full, expand array size
	if (IsFull()) {
		expandArray();
	}
	moreToSearch = (location < length);
	while (moreToSearch) {
		RelationType r = item.ComparedTo(info[location]);
		switch (r) {
		case LESS:
		case EQUAL:
			moreToSearch = false;
			break;
		case GREATER:
			location++;
			moreToSearch = (location < length);
			break;
		}
	}
	// then, move items AFTER location down one slot
	for (int index = length; index > location; index--)
		info[index] = info[index - 1];
	info[location] = item;
	length++;
}

void SortedType::ResetList()
// Post: currentPos has been initialized.
{
	currentPos = -1;
}

ItemType SortedType::GetNextItem()
// Post: item is current item.
//       Current position has been updated.
{
	currentPos++;
	return info[currentPos];
}

/**
 * Extend the memory capacity of the current array by 2 * MAX_LENGTH
 *
 * Function added as part of Lab4!
 */
void SortedType::expandArray() {
	/**
	 * NOTE to self:
	 * No need to update the currentPos as it's index-based, not memory pointer based.
	 */
	int expandedMaxItems = MAX_ITEMS * 2;
	ItemType *copy = new ItemType[expandedMaxItems];

	// copy over ONLY logically important values (length), not MAX_LENGTH
	for (int i = 0; i < length; i++) {
		copy[i] = info[i];
	}

	delete[] info; // delete original info
	MAX_ITEMS = expandedMaxItems; // set new MAX_ITEMS size
	info = copy; // set item pointer to new array
}
