//============================================================================
// Name        : Exercise 4
// Author      : Benjamin Liden
// Date		   : April 5, 2021
// Professor   : Ivan Temesvari
// Class       : CS240
//============================================================================

#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include "TreeType.h"

int main(){
	std::stringstream testLog;

	TreeType<std::string> tree;
	OrderType order = OrderType::IN_ORDER;
	tree.PutItem("J");
	tree.PutItem("D");
	tree.PutItem("A");
	tree.PutItem("B");
	tree.PutItem("G");
	tree.PutItem("E");
	tree.PutItem("H");
	tree.PutItem("F");
	tree.PutItem("P");
	tree.PutItem("K");
	tree.PutItem("L");
	tree.PutItem("U");
	tree.PutItem("S");
	tree.PutItem("T");
	tree.PutItem("W");
	tree.PutItem("X");
	tree.PutItem("Y");
	tree.ResetTree(order);
	tree.Print(testLog);

	// verify the tree is in the correct ordering
	assert(testLog.str() == "ABDEFGHJKLPSTUWXY");
	testLog.clear();

	assert(tree.Ancestors("T") == "J P U S");
	assert(tree.Ancestors("F") == "J D G E");
	assert(tree.Ancestors("Q") == "no ancestors were found");

	// even works with other types!

	TreeType<int> numberTree;
	numberTree.PutItem(3);
	numberTree.PutItem(5);
	numberTree.PutItem(1);
	numberTree.PutItem(INT_MAX);
	numberTree.PutItem(INT_MIN);

	assert(numberTree.Ancestors(INT_MAX) == "3 5");

	std::cout << "Tests finished successfully :)" << std::endl;
	return 0;
}
