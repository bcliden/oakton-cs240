/**
 * ItemType implementations
 *
 * Written by Benjamin Liden
 * 		for Prof. I. Temesvari's CS240 course.
 * 		Exercise 2.
 */
#include <iostream>
#include "ItemType.h"

Item::ItemType::ItemType()
{ 
  value = 0;
}

Item::RelationType Item::ItemType::ComparedTo(ItemType otherItem) const
{
  if (value < otherItem.value)
    return LESS;
  else if (value > otherItem.value)
    return GREATER;
  else return EQUAL;
}

void Item::ItemType::Initialize(int number)
{
  value = number;
}

void Item::ItemType::Print(std::ostream& out) const
// pre:  out has been opened.
// post: value has been sent to the stream out.
{
  out << value;
}
