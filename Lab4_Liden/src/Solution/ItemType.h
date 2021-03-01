#pragma once

/**
 * 	Original file from: CS240SortedArray.zip
 *
 * 	Not modified in any meaningful way.
 */

#include <fstream>
#include <iostream>

enum RelationType {
	LESS, GREATER, EQUAL
};

class ItemType {
	public:
		ItemType();
		RelationType ComparedTo(ItemType) const;
		void Print(std::ostream&) const;
		void Initialize(int number);
		int GetValue();

	private:
		int value;
};
