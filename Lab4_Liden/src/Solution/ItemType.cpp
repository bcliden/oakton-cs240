/*
 * ItemType.cpp
 *
 *  Created on: Feb 27, 2021
 *      Author: Ben
 */

#include "ItemType.h"

int ItemType::GetValue() {
	return value;
}

ItemType::ItemType() {
	value = 0;
}

RelationType ItemType::ComparedTo(ItemType otherItem) const {
	if (value < otherItem.value)
		return LESS;
	else if (value > otherItem.value)
		return GREATER;
	else
		return EQUAL;
}

void ItemType::Initialize(int number) {
	value = number;
}

void ItemType::Print(std::ostream &out) const
// pre:  out has been opened.
// post: value has been sent to the stream out.
		{
	out << value;
}
