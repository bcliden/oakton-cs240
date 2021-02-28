/**
 * ItemType implementations
 *
 * Written by Benjamin Liden
 * 		for Prof. I. Temesvari's CS240 course.
 * 		Exercise 2.
 */
/*
 * Lab 3.
 * ItemType header.
 *
 * There are a few alterations to the original class file, namely:
 * 		- namespacing
 * 		- optional print stream for ItemType::Print
 * 		- add'l constructor that takes an int value (no more Initialize needed!)
 *
 * 	Written for Prof. I. Temesvari's CS240 at Oakton CC.
 *	Author: Benjamin Liden
 */
#include <iostream>
#include "ItemType.h"

using Item::ItemType;
using Item::RelationType;

ItemType::ItemType() {
	value = 0;
}

ItemType::ItemType(int num) :
		value { num } {
}

RelationType ItemType::ComparedTo(ItemType otherItem) const {
	if (value < otherItem.value)
		return RelationType::LESS;
	else if (value > otherItem.value)
		return RelationType::GREATER;
	else
		return RelationType::EQUAL;
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
