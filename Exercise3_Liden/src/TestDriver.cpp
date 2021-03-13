//============================================================================
// Name        : Exercise3_Liden.cpp
// Author      : Benjamin Liden
// Date        : March 13, 2021
// Class       : CS240 Data Structures
// Professor   : Ivan Temesvari
// Description : Exercise 3 Solution
//============================================================================

#include <iostream>
#include <sstream>
#include <cassert>
#include "LinkedQueue.h"

std::string const verifiedOutput = R"(8 6 7 5 3 0 9 
8
6
7 5 3 0 9 
7 5 3 0 9 
7
5 3 0 9 
7 5 3 0 9 
)";

int main() {
	std::stringstream testLog;

	LinkedQueue q;
	q.Enqueue(8);
	q.Enqueue(6);
	q.Enqueue(7);
	q.Enqueue(5);
	q.Enqueue(3);
	q.Enqueue(0);
	q.Enqueue(9);
	q.Print(testLog);

	int item;
	q.Dequeue(item);
	testLog << item << std::endl;
	q.Dequeue(item);
	testLog << item << std::endl;
	q.Print(testLog);

	LinkedQueue q2(q); //call copy constructor
	q2.Print(testLog);
	q2.Dequeue(item);
	testLog << item << std::endl;
	q2.Print(testLog);

	LinkedQueue q1;
	q1 = q; //call assignment operator=
	q1.Print(testLog);

//	std::cout << testLog.str() << std::endl;

	assert(testLog.str() == verifiedOutput);
	std::cout << "Tests finished without error." << std::endl;
	return 0;
}
