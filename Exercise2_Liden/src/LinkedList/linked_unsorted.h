/**
 * LinkedListUnsortedType header.
 *
 * Please see added Print and SplitLists functionality.
 *
 * Written by Benjamin Liden
 * 		for Prof. I. Temesvari's CS240 course.
 * 		Exercise 2.
 */
#pragma once

#include <iostream>
#include "../ItemType.h"
// File Item::ItemType.h must be provided by the user of this class.
//  Item::ItemType.h must contain the following definitions:
//  MAX_ITEMS:     the maximum number of items on the list 
//  Item::ItemType:      the definition of the objects on the list
//  RelationType:  {LESS, GREATER, EQUAL}
//  Member function ComparedTo(Item::ItemType item) which returns
//       LESS, if self "comes before" item 
//       GREATER, if self "comes after" item 
//       EQUAL, if self and item are the same 
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

	Item::ItemType GetItem(Item::ItemType &item, bool &found);
	// Function: Retrieves list element whose key matches item's key (if
	//           present).
	// Pre:  List has been initialized.
	//       Key member of item is initialized.
	// Post: If there is an element someItem whose key matches
	//       item's key, then found = true and someItem is returned;
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

	const Item::ItemType GetNextItem();
	// Function: Gets the next element in list.
	// Pre:  List has been initialized and has not been changed since last call.
	//       Current position is defined.
	//       Element at current position is not last in list.
	//
	// Post: Current position is updated to next position.
	//       item is a copy of element at current position.

	void Print(std::ostream& out = std::cout);
	// Print all members, separated by commas, onto given stream.

	static void SplitLists(LinkedListUnsortedType list, const Item::ItemType item,
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

