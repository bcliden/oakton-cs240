#pragma once

// The following declarations and definitions go into file 
// ItemType.h. 
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
