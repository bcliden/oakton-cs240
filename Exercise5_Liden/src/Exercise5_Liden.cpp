//============================================================================
// Name        : Exercise 5
// Author      : Benjamin Liden
// Date        : April 23, 2021
// Professor   : Ivan Temesvari
// Course  	   : CS240 C++ Data Structures
//============================================================================

#include <iostream>
#include <thread>

#include "ParallelMergeSort.h"

int main() {
	gather_and_run_merge();
	std::cout << "Run finished without error." << std::endl;
	return 0;
}
