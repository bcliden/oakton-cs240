/**
 * ArrayBackedUnsortedType header.
 *
 * 	(note: some work carried over from Ex2, Lab2, and Lab3)
 *
 * 	Written for Prof. I. Temesvari's CS240 at Oakton CC.
 *	Author: Benjamin Liden
 */
#pragma once

#include <iostream>
#include "../ItemType.h"

class ArrayBackedUnsortedType {
public:
	ArrayBackedUnsortedType();
	// Constructor

	void MakeEmpty();
	// Function: Returns the list to the empty state.
	// Post:  List is empty.

	bool IsFull() const;
	// Function:  Determines whether list is full.
	// Pre:  List has been initialized.
	// Post: Function value = (list is full)

	int GetLength() const;
	// Function: Determines the number of elements in list.
	// Pre:  List has been initialized.
	// Post: Function value = number of elements in list

	Item::ItemType GetItem(Item::ItemType, bool&);
	// Function: Retrieves list element whose key matches item's key (if
	//           present).
	// Pre:  List has been initialized.
	//       Key member of item is initialized.
	// Post: If there is an element someItem whose key matches
	//       item's key, then found = true and someItem is returned.
	// 	 otherwise found = false and item is returned.
	//       List is unchanged.

	void PutItem(Item::ItemType item);
	// Function: Adds item to list.
	// Pre:  List has been initialized.
	//       List is not full.
	//       item is not in list.
	// Post: item is in list.

	void DeleteItem(Item::ItemType item);
	// Function: Deletes the element whose key matches item's key.
	// Pre:  List has been initialized.
	//       Key member of item is initialized.
	//       One and only one element in list has a key matching item's key.
	// Post: No element in list has a key matching item's key.

	void ResetList();
	// Function: Initializes current position for an iteration through the list.
	// Pre:  List has been initialized.
	// Post: Current position is prior to list.

	Item::ItemType GetNextItem();
	// Function: Gets the next element in list.
	// Pre:  List has been initialized and has not been changed since last call.
	//       Current position is defined.
	//       Element at current position is not last in list.
	//
	// Post: Current position is updated to next position.
	//       item is a copy of element at current position.

	void Print(std::ostream& = std::cout);
	// Function: Print entire list out to stream param

	void ShiftRight();
	// Function: move last item to head. shift all other cells right.

private:
	int length;
	Item::ItemType info[Item::MAX_ITEMS];
	int currentPos;
};

