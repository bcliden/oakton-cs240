#ifndef LINKEDQUEUETYPEITERATOR_H
#define LINKEDQUEUETYPEITERATOR_H
#include <stddef.h>
#include "NodeType.h"
// A template for an iterator that implements the contract required by the
// range-based for-loop.
//2/25/2019
//Ivan Temesvari
class LinkedQueueTypeIterator
{
	public:
		// Customize the constructor to work with the ADT.
		LinkedQueueTypeIterator(NodeType* start, int loc);

		ItemType& operator*();

		// Customize to return the proper iterator class.
		LinkedQueueTypeIterator& operator++();

		// Customize to receive the correct Iterator class.
		bool operator!=(const LinkedQueueTypeIterator& it) const;

	private:
		// The start of the linked list.
		NodeType* item;
		int location;
};
#endif
