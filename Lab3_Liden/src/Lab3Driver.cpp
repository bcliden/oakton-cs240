/*
 * Lab 3.
 * Test Driver for Delete and ShiftRight implementations on ArrayBackedUnsortedType
 *
 * There are a few alterations to the original test driver, namely:
 * 		- added print streams
 * 		- extra ShiftRights
 *
 * 	Written for Prof. I. Temesvari's CS240 at Oakton CC.
 *	Author: Benjamin Liden
 */
#include <assert.h>
#include <iostream>
#include <sstream>

#include "ArrayList/array_unsorted.h"
#include "ItemType.h"

using Item::ItemType;

const std::string expectedOutput = R"((original) length: 5
4, 5, 4, 4, 8
(shifted right) length: 5
8, 4, 5, 4, 4
(shifted right) length: 5
4, 8, 4, 5, 4
(shifted right) length: 5
4, 4, 8, 4, 5
(delete all 4s) length: 2
5, 8
(shift right) length: 2
8, 5
)";

void testImproved();
void testOriginal();

int main() {
//	testOriginal(); // Professor: here are the original cases provided
	testImproved();
	std::cout << "Tests finished successfully" << std::endl;
	return 0;
}

/*
 * This is the original test case included with the assignment.
 */
void testOriginal(){
	using namespace std;

	ArrayBackedUnsortedType classList;
	classList.PutItem(ItemType(4));
	classList.PutItem(ItemType(5));
	classList.PutItem(ItemType(4));
	classList.PutItem(ItemType(4));
	classList.PutItem(ItemType(8));
	cout << "(original) length: " << classList.GetLength() << endl;
	classList.ResetList();
	classList.Print();
	classList.ShiftRight();
	cout << "(shifted right) length: " << classList.GetLength() << endl;
	classList.ResetList();
	classList.Print();
	classList.DeleteItem(ItemType(4));
	cout << "(delete all 4s) length: " << classList.GetLength() << endl;
	classList.ResetList();
	classList.Print();
	classList.ShiftRight();
	cout << "(shift right) length: " << classList.GetLength() << endl;
	classList.ResetList();
	classList.Print();
}

/*
 * This is a slightly improved test suite using print streams to verify correctness.
 */
void testImproved(){
	using namespace std;
	stringstream testOutput;

	ArrayBackedUnsortedType classList;
	classList.PutItem(ItemType(4));
	classList.PutItem(ItemType(5));
	classList.PutItem(ItemType(4));
	classList.PutItem(ItemType(4));
	classList.PutItem(ItemType(8));
	testOutput << "(original) length: " << classList.GetLength() << endl;
	classList.ResetList();
	classList.Print(testOutput);
	classList.ShiftRight();
	testOutput << "(shifted right) length: " << classList.GetLength() << endl;
	classList.ResetList();
	classList.Print(testOutput);
	classList.ShiftRight();
	testOutput << "(shifted right) length: " << classList.GetLength() << endl;
	classList.ResetList();
	classList.Print(testOutput);
	classList.ShiftRight();
	testOutput << "(shifted right) length: " << classList.GetLength() << endl;
	classList.ResetList();
	classList.Print(testOutput);
	classList.DeleteItem(ItemType(4));
	testOutput << "(delete all 4s) length: " << classList.GetLength() << endl;
	classList.ResetList();
	classList.Print(testOutput);
	classList.ShiftRight();
	testOutput << "(shift right) length: " << classList.GetLength() << endl;
	classList.ResetList();
	classList.Print(testOutput);

	assert(testOutput.str() == expectedOutput);
}
