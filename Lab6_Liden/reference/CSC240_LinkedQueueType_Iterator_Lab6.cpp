//============================================================================
// Name        : CSC240_Queue_Linked.cpp
// Author      : Ivan Temesvari
// Version     : 3/12/2019
// Copyright   : Your copyright notice
// Description : Lab 6 CSC 240
//============================================================================

#include <iostream>
#include "LinkedQueueType.h"
using namespace std;

int main() {
	LinkedQueueType q;
	q.Enqueue(8);
	q.Enqueue(6);
	q.Enqueue(7);
	q.Enqueue(5);
	q.Enqueue(3);
	q.Enqueue(0);
	q.Enqueue(9);
	//Use iterator to print.
	for (int& x : q) {
	    cout << x << " ";
	}
	cout << endl;
	return 0;
}
