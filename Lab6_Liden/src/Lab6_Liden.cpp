//============================================================================
// Name        : Lab 6
// Author      : Benjamin Liden
// Date        : 3/14/2020
// Professor   : Ivan Temesvari
// Course 	   : CS240 Data Structures
//============================================================================

#include <iostream>
#include <sstream>
#include <cassert>
#include "LinkedQueue/LinkedQueue.h"

void testBasicQueueFunctions();
void testIterator();
void testTemplate();

int main() {
	testBasicQueueFunctions();
	testIterator();
	testTemplate();
	std::cout << "Tests finished without error." << std::endl;
	return 0;
}

void testBasicQueueFunctions() {
	// @formatter:off
	std::string const verifiedOutput = R"(8675309
8
6
75309
)";
	// @formatter:on

	std::stringstream testLog;

	LinkedQueue<int> q;
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

//	std::cout << testLog.str() << std::endl;
//	std::cout << verifiedOutput << std::endl;

	assert(testLog.str() == verifiedOutput);
}

void testIterator() {
	// @formatter:off
	std::string const verifiedOutput = R"(8675309
8675309
)";
	// @formatter:on

	std::stringstream testLog;

	LinkedQueue<int> q;
	q.Enqueue(8);
	q.Enqueue(6);
	q.Enqueue(7);
	q.Enqueue(5);
	q.Enqueue(3);
	q.Enqueue(0);
	q.Enqueue(9);

	// iterate multiple ways
	for (auto &x : q) { // ranged iterator
		testLog << x;
	}
	testLog << std::endl;

	for (auto it = q.begin(); it != q.end(); ++it) { // ranged iterator (under the hood)
		testLog << *it;
	}
	testLog << std::endl;

//	std::cout << testLog.str() << std::endl;
//	std::cout << verifiedOutput << std::endl;

	assert(testLog.str() == verifiedOutput);
}

void testTemplate() {
	// @formatter:off
	std::string const verifiedOutput = R"(abcdefg
abcdefg
)";
	// @formatter:on

	std::stringstream testLog;

	LinkedQueue<char> q;
	q.Enqueue('a');
	q.Enqueue('b');
	q.Enqueue('c');
	q.Enqueue('d');
	q.Enqueue('e');
	q.Enqueue('f');
	q.Enqueue('g');

	// iterate multiple ways
	for (auto &x : q) { // ranged iterator
		testLog << x;
	}
	testLog << std::endl;

	for (auto it = q.begin(); it != q.end(); ++it) { // ranged iterator (under the hood)
		testLog << *it;
	}
	testLog << std::endl;

//	std::cout << testLog.str() << std::endl;
//	std::cout << verifiedOutput << std::endl;

	assert(testLog.str() == verifiedOutput);
}
