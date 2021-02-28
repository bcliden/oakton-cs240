//============================================================================
// Name        : CSC240SortedArray.cpp
// Author      : Ivan Temesvari
// Date        : 2/24/2020
//============================================================================

#include <iostream>
#include "sorted.h"
using namespace std;

int main() {
	SortedType myList;
	cout << myList.GetMaxLength() << endl;
	++myList;    //unary operator, we overload operator++. The size of the list is increased by 1.
	cout << myList.GetMaxLength() << endl;

	ItemType item1;
	item1.Initialize(4);
	ItemType item2;
	item2.Initialize(5);
	ItemType item3;
	item3.Initialize(6);
	ItemType item4;
	item4.Initialize(7);
	ItemType item5;
	item5.Initialize(8);
	ItemType item6;
	item6.Initialize(9);

	myList.PutItem(item1);
	myList.PutItem(item2);
	myList.PutItem(item3);
	myList.PutItem(item4);
	myList.PutItem(item5);
	myList.PutItem(item6);
	cout << myList;
	cout << myList.GetMaxLength() << endl;

	ItemType item7;
	item7.Initialize(2);
	myList.PutItem(item7);
	cout << myList;
	cout << myList.GetMaxLength() << endl;

	SortedType list;
	list = myList;
	int dotProduct = myList*list;
	cout << "Dot product = " << dotProduct << endl;

	SortedType list2;
	list2.PutItem(item1);
	list2.PutItem(item2);
	list2.PutItem(item3);
	list2.PutItem(item4);

	int dotProduct2 = myList*list2;
	cout << "Dot product = " << dotProduct2 << endl;

	return 0;
}
