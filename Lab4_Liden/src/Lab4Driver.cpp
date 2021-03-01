//============================================================================
// Name        : Lab4 Driver
// Author      : Benjamin Liden
// Date        : 2/27/2021
//============================================================================

#include <iostream>
#include <sstream>
#include <assert.h>

#include "Solution/sorted_array.h"

const std::string expectedOutput = R"(Initial max length is: 5
4 5 6 7 8 
list has max size of: 5
2 4 5 6 7 8 9 
list has max size of: 10
)";

int main() {
	std::stringstream testLog;

	// variables to be used below
	SortedType myList;
	ItemType currentItem;
	int currentLength = myList.GetMaxLength();

	// initial length
	testLog << "Initial max length is: " << currentLength << std::endl;
	assert(currentLength == 5);

	// intialize items
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

	// fill list to the brim
	myList.PutItem(item1);
	myList.PutItem(item2);
	myList.PutItem(item3);
	myList.PutItem(item4);
	myList.PutItem(item5);

	// test currentPosition
	myList.GetNextItem();
	currentItem = myList.GetNextItem();
	assert(currentItem.GetValue() == 5);

	// test max size
	testLog << myList;
	currentLength = myList.GetMaxLength();
	testLog << "list has max size of: " << currentLength << std::endl;
	assert(currentLength == 5);

	// initialize items and fill list BEYOND previous max size
	ItemType item6;
	item6.Initialize(9);
	ItemType item7;
	item7.Initialize(2);
	myList.PutItem(item6);
	myList.PutItem(item7);

	// test currentPosition again
	currentItem = myList.GetNextItem();
	/**
	 * Check "next" item. This is actually the same as above
	 * 		because item7 (value: 2) gets slotted into index[0]
	 */
	assert(currentItem.GetValue() == 5);

	// test max size again
	testLog << myList;
	currentLength = myList.GetMaxLength();
	testLog << "list has max size of: " << currentLength << std::endl;
	assert(currentLength == 10);

	// finally, assert that the testLog matches expected output
	assert(expectedOutput == testLog.str());

	std::cout << "Tests ran successfully." << std::endl;
	std::cout << "Goodbye!" << std::endl;
	return 0;
}
