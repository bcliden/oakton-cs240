// Write a recursive TreeType member function called Ancestors that returns a string
// representing the ancestors (in reverse order) of a particular node whose info member contains value.
// Use the following signature:
// string TreeType<ItemType>::Ancestors(ItemType item)
// Ivan Temesvari
// 3/11/2019


#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
#include <string>
#include "TreeType.h"
using namespace std;

int main(){
	TreeType<string> tree;
	OrderType order;
	string item;
	ofstream outFile;      // file containing output
	string outFileName;    // output file external name
	cout << "Enter name of output file; press return." << endl;
	cin  >> outFileName;
	outFile.open(outFileName.c_str());

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

	order = IN_ORDER;
	tree.ResetTree(order);
	tree.Print(outFile);

	cout << tree.Ancestors("T") << endl;
	return 0;
}




