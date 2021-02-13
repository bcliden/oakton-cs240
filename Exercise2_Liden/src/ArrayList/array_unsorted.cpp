/**
 * ArrayBackedUnsortedType implementation.
 *
 * Please see added Print and SplitLists functionality.
 *
 * Written by Benjamin Liden
 * 		for Prof. I. Temesvari's CS240 course.
 * 		Exercise 2.
 */

#include "../ItemType.h"
#include "array_unsorted.h"

using namespace Item;

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

Item::ItemType ArrayBackedUnsortedType::GetItem(Item::ItemType item,
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
		case LESS:
		case GREATER:
			location++;
			moreToSearch = (location < length);
			break;
		case EQUAL:
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
void ArrayBackedUnsortedType::PutItem(Item::ItemType item)
// Post: item is in the list.
		{
	info[length] = item;
	length++;
}
void ArrayBackedUnsortedType::DeleteItem(Item::ItemType item)
// Pre:  item's key has been initialized.
//       An element in the list has a key that matches item's.
// Post: No element in the list has a key that matches item's.
		{

	int location = 0;

	while (item.ComparedTo(info[location]) != EQUAL)
		location++;

	info[location] = info[length - 1];
	length--;
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
//	out << std::endl;
}

void ArrayBackedUnsortedType::SplitLists(ArrayBackedUnsortedType list,
		const Item::ItemType item, ArrayBackedUnsortedType &lesserList,
		ArrayBackedUnsortedType &greaterList) {

	// for every element in list
	int len = list.GetLength();
	for (int i = 0; i < len; i++) {
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
