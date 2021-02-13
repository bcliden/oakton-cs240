/**
 * LinkedListUnsortedType header.
 *
 * Please see added Print.
 *
 * Written by Benjamin Liden
 * 		for Prof. I. Temesvari's CS240 course.
 * 		Lab 2. Some code borrowed from my Exercise 2 solution.
 */
#pragma once

#include <iostream>
#include "../StudentType.h"

struct NodeType;

class LinkedListUnsortedType {
public:
	LinkedListUnsortedType();
	// Constructor
	LinkedListUnsortedType(const LinkedListUnsortedType& list);
	// Copy Constructor
	~LinkedListUnsortedType();
	// Destructor
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

	ItemType GetItem(ItemType &item, bool &found);
	// Function: Retrieves list element whose key matches item's key (if
	//           present).
	// Pre:  List has been initialized.
	//       Key member of item is initialized.
	// Post: If there is an element someItem whose key matches
	//       item's key, then found = true and someItem is returned;
	// 	 otherwise found = false and item is returned.
	//       List is unchanged.

	void PutItem(ItemType item);
	// Function: Adds item to list.
	// Pre:  List has been initialized.
	//       List is not full.
	//       item is not in list.
	// Post: item is in list.

	void DeleteItem(ItemType item);
	// Function: Deletes the element whose key matches item's key.
	// Pre:  List has been initialized.
	//       Key member of item is initialized.
	//       One and only one element in list has a key matching item's key.
	// Post: No element in list has a key matching item's key.

	void ResetList();
	// Function: Initializes current position for an iteration through the list.
	// Pre:  List has been initialized.
	// Post: Current position is prior to list.

	ItemType GetNextItem();
	// Function: Gets the next element in list.
	// Pre:  List has been initialized and has not been changed since last call.
	//       Current position is defined.
	//       Element at current position is not last in list.
	//
	// Post: Current position is updated to next position.
	//       item is a copy of element at current position.

	void Print(std::ostream& out = std::cout);
	// Print all members, separated by commas, onto given stream.

	static void SplitLists(LinkedListUnsortedType list, const ItemType item,
			LinkedListUnsortedType& lesserList, LinkedListUnsortedType& greaterList);
	// Function: divides list into two lists according to the value of the item.
	// Pre: list has been initialized and is not empty. list1 and list2 are empty.
	// Post: list1 contains all the items of list whose
	//			values are less than or equal to the value of item.
	//		list 2 contains all of the items of list whose
	//			values are greater that the value of item.


private:
	NodeType *listData;
	int length;
	NodeType *currentPos;
};

