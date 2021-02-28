#ifndef ITEMTYPE_H
#define ITEMTYPE_H
// The following declarations and definitions go into file 
// ItemType.h. 
#include <fstream>
#include <iostream>
using namespace std;

enum RelationType  {LESS, GREATER, EQUAL};

class ItemType 
{ 
public:
  ItemType();
  RelationType ComparedTo(ItemType) const;
  void Print(ostream&) const;
  void Initialize(int number);
  int GetValue();
private:
  int value;
};
 
int ItemType::GetValue(){
	return value;
}

ItemType::ItemType()
{
  value = 0;
}

RelationType ItemType::ComparedTo(ItemType otherItem) const
{
  if (value < otherItem.value)
    return LESS;
  else if (value > otherItem.value)
    return GREATER;
  else return EQUAL;
}

void ItemType::Initialize(int number)
{
  value = number;
}

void ItemType::Print(ostream& out) const
// pre:  out has been opened.
// post: value has been sent to the stream out.
{
  out << value;
}
#endif
