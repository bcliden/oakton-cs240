#pragma once

#include "./Node.h"

class LinkedQueueIterator
{
	public:
		// Customize the constructor to work with the ADT.
		LinkedQueueIterator(LinkedQueueUtil::Node* start, int loc);

		LinkedQueueUtil::Item& operator*();

		// Customize to return the proper iterator class.
		LinkedQueueIterator& operator++();

		// Customize to receive the correct Iterator class.
		bool operator!=(const LinkedQueueIterator& it) const;

	private:
		// The start of the linked list.
		LinkedQueueUtil::Node* item;
		int location;
};
