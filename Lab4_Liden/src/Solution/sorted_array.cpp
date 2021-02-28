/*
 * ItemType.cpp
 *
 *  Created on: Feb 27, 2021
 *      Author: Ben
 */

#include "sorted_array.h"

int SortedType::operator*(const SortedType &op) {
	int product = 0;
//try{
	if (length == op.length) {
		for (int i = 0; i < length; i++) {
			product += info[i].GetValue() * op.info[i].GetValue();
		}
	} else {
		throw ArrayLengthMismatch();
	}
//}
//catch(ArrayLengthMismatch& err){
//	cout << err.what() << endl;
//}

	return product;
}

SortedType SortedType::operator++() { //pre-increment: increases the size of the info array by 1.
	ItemType *infoCopy = new ItemType[MAX_ITEMS + 1];
	for (int i = 0; i < MAX_ITEMS; i++) {
		infoCopy[i] = info[i];
	}
	delete[] info;
	MAX_ITEMS++;
	info = infoCopy;
	return *this;
}

SortedType SortedType::operator++(int) { //post-increment: increases the size of the info array by 1.
	ItemType *infoCopy = new ItemType[MAX_ITEMS + 1];
	for (int i = 0; i < MAX_ITEMS; i++) {
		infoCopy[i] = info[i];
	}
	delete[] info;
	MAX_ITEMS++;
	info = infoCopy;
	return *this;
}

std::ostream& operator<<(std::ostream &out, const SortedType list) {
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
	//Make some room for one more.
	if (IsFull()) {
		//enlarge the list by 1
		++(*this);   //use pre-increment
		//(*this)++:   //use post-increment
	}
	moreToSearch = (location < length);
	while (moreToSearch) {
		switch (item.ComparedTo(info[location])) {
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
