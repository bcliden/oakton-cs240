#pragma once

/**
 * LinkedQueueIterator Templated Header and Implementation
 * 		for Lab 6 of Prof. Temesvari's CS240.
 *
 * Written by Benjamin Liden
 * 		on 3/14/2020.
 */

#include "Node.h"

template<class Item>
class LinkedQueueIterator
{
	public:
		LinkedQueueIterator(Node<Item>* start);
		Item& operator*();
		LinkedQueueIterator<Item>& operator++();
		bool operator!=(const LinkedQueueIterator<Item>& it) const;

	private:
		Node<Item>* item;
};

/**
 *	Base Constructor, taking beginning node
 */
template<class Item>
LinkedQueueIterator<Item>::LinkedQueueIterator(Node<Item>* start) {
	this->item = start;
}

/**
 * Dereference iterator to underlying item
 */
template<class Item>
Item& LinkedQueueIterator<Item>::operator*() {
	return item->info;
}

/**
 * Move iterator down to next item
 */
template<class Item>
LinkedQueueIterator<Item>& LinkedQueueIterator<Item>::operator++() {
	if (item == nullptr || item->next == nullptr) {
		item = nullptr;
	} else {
		item = item->next;
	}
	return *this;
}

/**
 * Do these two iterator items match?
 */
template<class Item>
bool LinkedQueueIterator<Item>::operator!=(const LinkedQueueIterator<Item> &it) const {
	return item != it.item;
}
