/*
 * Lab 3.
 * ItemType header.
 *
 * There are a few alterations to the original class file, namely:
 * 		- namespacing
 * 		- add'l constructor that takes an int value (no more Initialize needed!)
 *
 *
 * 	Written for Prof. I. Temesvari's CS240 at Oakton CC.
 * 	Author: Benjamin Liden
 */

#pragma once

#include <iostream>

namespace Item {
	constexpr int MAX_ITEMS = 15;

	enum class RelationType {
		LESS, EQUAL, GREATER
	};

	class ItemType {
	public:
		ItemType();
		ItemType(int);
		RelationType ComparedTo(ItemType) const;
		void Print(std::ostream&) const;
		void Initialize(int number);
	private:
		int value;
	};
}
