#pragma once

/**
 * Modified by Benjamin Liden
 * 	on 2/27/21
 * 	for Prof. Temesvari's CS240
 */

#include "ItemType.h" 

class ArrayLengthMismatch {  //used as an exception class for dot product error.
	public:
		ArrayLengthMismatch() {
			myError = "Array lengths are not the same.";
		}
		std::string what() {
			return myError;
		}

	private:
		std::string myError;
};

class SortedType {
	public:
		friend std::ostream& operator<<(std::ostream &out, const SortedType list);
		SortedType();
		SortedType operator++();  //pre
		SortedType operator++(int);  //post
		int operator*(const SortedType&);

		bool IsFull() const;
		// Function:  Determines whether list is full.
		// Pre:  List has been initialized.
		// Post: Function value = (list is full)

		int GetLength() const;
		// Function: Determines the number of elements in list.
		// Pre:  List has been initialized.
		// Post: Function value = number of elements in list

		int GetMaxLength() const;

		ItemType GetItem(ItemType item, bool &found);
		// Function: Retrieves list element whose key matches item's key (if
		//           present).
		// Pre:  List has been initialized.
		//       Key member of item is initialized.
		// Post: If there is an element someItem whose key matches
		//       item's key, then found = true and item is returned;
		//       someItem; otherwise found = false and item is returned.
		//       List is unchanged.

		void PutItem(ItemType item);
		// Function: Adds item to list.
		// Pre:  List has been initialized.
		//       List is not full.
		//       item is not in list.
		//       List is sorted.
		// Post: item is in list.
		//       List is sorted

		void DeleteItem(ItemType item);
		// Function: Deletes the element whose key matches item's key.
		// Pre:  List has been initialized.
		//       Key member of item is initialized.
		//       One and only one element in list has a key matching item's key.
		// Post: No element in list has a key matching item's key.
		//       List is sorted.

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
		//       Returns a copy of element at current position.

		void MakeEmpty();
		// Function: Make the list empty
		// Pre:  List has been initialized.
		// Post: The list is empty

	private:
		int length;
		ItemType *info;
		int currentPos;
		int MAX_ITEMS;
};
