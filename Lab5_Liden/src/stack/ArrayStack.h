#pragma once

/**
 * ArrayStack Header
 *
 * Mostly unaltered from the D2L materials.
 *
 * See new additions: ReplaceItem, Identical
 *
 * Benjamin Liden 3/13
 */

#include <iostream>
#include "./ItemType.h"

//   The user of this file must provided a file "ItemType.h" that defines:
//       ItemType : the class definition of the objects on the stack.
//       MAX_ITEMS: the maximum number of items on the stack.

//   Class specification for Stack ADT in file Stack1.h
//Edit: Ivan Temesvari 2/11/2019

class FullStack {};
// Exception class thrown by Push when stack is full.

class EmptyStack {};
// Exception class thrown by Pop and Top when stack is emtpy.

class ArrayStack {
	public:
		ArrayStack(int max); // max is stack size
		ArrayStack();  // Default size is 500.

		// Function: Determines whether the stack is full.
		// Pre:  Stack has been initialized.
		// Post: Function value = (stack is full)
		bool IsFull() const;

		// Function: Determines whether the stack is empty.
		// Pre:  Stack has been initialized.
		// Post: Function value = (stack is empty)
		bool IsEmpty() const;

		// Function: Adds newItem to the top of the stack.
		// Pre:  Stack has been initialized.
		// Post: If (stack is full), FullStack exception is thrown;
		//     otherwise, newItem is at the top of the stack.
		void Push(ItemType item);

		// Function: Removes top item from the stack.
		// Pre:  Stack has been initialized.
		// Post: If (stack is empty), EmptyStack exception is thrown;
		void Pop();

		// Function: Returns a copy of top item on the stack.
		// Pre:  Stack has been initialized.
		//     otherwise, top element has been removed from stack.
		// Post: If (stack is empty), EmptyStack exception is thrown;
		//     otherwise, top element has been removed from stack.
		ItemType Top();

		//Destructor. Reallocate the memory reserved for ItemType* items.
		~ArrayStack();

		//Print the stack
		void Print(std::ostream& = std::cout);

		//Function: Determines if two stacks are identical.
		//Preconditions: stack1 and stack2 have been initialized.
		//Postconditions: stack1 and stack2 are unchanged.
		//				  Function return value = stack1 and stack2 are identical
		friend bool Identical(const ArrayStack& stack1, const ArrayStack& stack2);

	private:
		int maxStack; // Maximum number of stack items.
		int top;
		ItemType* items;  // Pointer to dynamically allocated memory.
};

//Function: Replaces all occurrences of oldItem with newItem.
//Precondition: stack has been initialized.
//Postcondition:Each occurrence of oldItem in stack has been replaced by newItem.
void ReplaceItem(ArrayStack& stack, ItemType oldItem, ItemType newItem);

