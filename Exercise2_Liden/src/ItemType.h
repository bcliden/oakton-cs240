/**
 * ItemType namespace
 *
 * Written by Benjamin Liden
 * 		for Prof. I. Temesvari's CS240 course.
 * 		Exercise 2.
 */
#pragma once

#include <iostream>

namespace Item {

const int MAX_ITEMS = 14;

enum RelationType {
	LESS, GREATER, EQUAL
};

class ItemType {
public:
	ItemType();
	RelationType ComparedTo(ItemType) const;
	void Print(std::ostream&) const;
	void Initialize(int number);
private:
	int value;
};
}

