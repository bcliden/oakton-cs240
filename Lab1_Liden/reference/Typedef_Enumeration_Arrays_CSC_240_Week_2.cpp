//============================================================================
// Name        : Typedef_Enumeration_Arrays_CSC_240_Week_2.cpp
// Author      : Ivan Temesvari
// Version     : 1/29/2019
// Copyright   :
// Description : This program gives an example of enum and typedef with an array of structs
//============================================================================

#include <iostream>
#include <string>
using namespace std;

enum NameType {FIRST, SECOND, THIRD};

struct Name{
	string first;
	string middle;
	string last;
};

const int NUM_ITEMS = 3;
typedef Name NamesArray[NUM_ITEMS];

int main() {
	Name myName;
	myName.first = "Billy";
	myName.middle = "Bob";
	myName.last = "Thornton";

	Name herName;
	herName.first = "Sally";
	herName.middle = "Jessie";
	herName.last = "James";

	cout << herName.middle << endl;

	NamesArray someNames;
	someNames[FIRST] = herName;
	someNames[SECOND] = myName;

	someNames[FIRST].middle = "Sue";
	cout << someNames[FIRST].first << endl;

	return 0;
}
