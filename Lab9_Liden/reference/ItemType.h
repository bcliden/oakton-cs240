#ifndef ITEM_H
#define ITEM_H
#include <fstream>
#include <iostream>
using namespace std;
const int MAX_ITEMS = 5;
const int emptyItem = -1;
enum RelationType  {LESS, GREATER, EQUAL};
class ItemType {
public:
  ItemType();
  RelationType ComparedTo(ItemType) const;
  void Print(ostream&) const;
  void Initialize(int number);
  int Hash() const;
private:
  int idNum;
};

ItemType::ItemType(){
  idNum = 0;
}

RelationType ItemType::ComparedTo(ItemType otherItem) const
{
  if (idNum < otherItem.idNum)
    return LESS;
  else if (idNum > otherItem.idNum)
    return GREATER;
  else return EQUAL;
}

void ItemType::Initialize(int number)
{
	idNum = number;
}

void ItemType::Print(ostream& out) const
// pre:  out has been opened.
// post: value has been sent to the stream out.
{
  out << idNum;
}


// This file contains the individual functions from the text.
// Note that there are two InsertItems
int ItemType::Hash() const
// Post: Returns an integer between 0 and MAX_ITEMS -1.
{
  return (idNum % MAX_ITEMS);
}
#endif
