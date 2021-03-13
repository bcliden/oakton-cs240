//============================================================================
// Name        : Lab 5
// Author      : Benjamin Liden
// Date        : 3/13/2021
// Professor   : Ivan Temesvari
// Course      : CS240 Data Structures
//============================================================================

#include <iostream>
#include <sstream>
#include <cassert>

#include "stack/ArrayStack.h"

std::string verifiedOutput = R"(Stack is empty.
44543
88583
Stack is empty.
44543
The stacks are NOT identical.
)";

int main() {
	std::stringstream testLog;

	try {
		ArrayStack stack;
		stack.Print(testLog);
		stack.Push(4);
		stack.Push(4);
		stack.Push(5);
		stack.Push(4);
		stack.Push(3);
		stack.Push(4);
		stack.Print(testLog);
		ReplaceItem(stack, 4, 8);
		stack.Print(testLog);

		ArrayStack myStack;
		myStack.Print(testLog);
		myStack.Push(4);
		myStack.Push(4);
		myStack.Push(5);
		myStack.Push(4);
		myStack.Push(3);
		myStack.Push(4);
		myStack.Print(testLog);

		if (Identical(stack, myStack)) {
			testLog << "The stacks are identical." << std::endl;
		} else {
			testLog << "The stacks are NOT identical." << std::endl;
		}
	} catch (const FullStack &e) {
		testLog << "Stack is full!" << std::endl;
	} catch (const EmptyStack &e) {
		testLog << "Stack is empty!" << std::endl;
	}

//	std::cout << testLog.str() << std::endl;
	assert(verifiedOutput == testLog.str());
	std::cout << "Tests finished with no failures" << std::endl;
	return 0;
}
