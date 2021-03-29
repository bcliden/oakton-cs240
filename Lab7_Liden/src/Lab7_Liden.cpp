//============================================================================
// Name        : Lab 7
// Author      : Benjamin Liden
// Date        : Mar 29, 2021
// Professor   : Ivan Temesvari
// Course	   : CS240 Data Structures
//============================================================================

#include <iostream>
#include <cassert>
#include "Memoized.h"

void testRegularVersion();
void testMemoizedVersion();
void testLargeMemoizedVersion();
void testLargeRegularVersion();
void testHugeMemoizedVersion();

int timesCalculated = 0;
/*
 * This is the original, fixed recursive NumPaths solution.
 */
int NumPaths(int row, int col, int n) {
	if (row == n || col == n) {
		return 1;
	}
	++timesCalculated;
	return NumPaths(row + 1, col, n) + NumPaths(row, col + 1, n);
}

int main() {
	testRegularVersion();
	testLargeRegularVersion();
	testMemoizedVersion();
	testLargeMemoizedVersion();
	testHugeMemoizedVersion();

	printf("Tests finished without error\n");
	return 0;
}

void testRegularVersion() {
	int const grid_size = 5;
	timesCalculated = 0;

	int result = NumPaths(1, 1, grid_size);

//	printf("%d times - %d paths\n", timesCalculated, result);
	assert(result == 70);
	assert(timesCalculated == 69);
}

void testMemoizedVersion() {
	int const grid_size = 5;
	memoizedVersion::Metrics metrics;
	int result = memoizedVersion::NumPaths<grid_size>(1, 1, metrics);

//	metrics.print();
	assert(result == 70);
	assert(metrics.calledTimes == 33);
	assert(metrics.hadToCalculate == 16);
	assert(metrics.gotFromCache == 9);
}

void testLargeRegularVersion() {
	int const larger_size = 15;
	timesCalculated = 0;

	int result = NumPaths(1, 1, larger_size);

//	printf("%d times - %d paths\n", timesCalculated, result);
	assert(result == 40116600);
	assert(timesCalculated == 40116599);
}

void testLargeMemoizedVersion() {
	int const larger_size = 15;
	memoizedVersion::Metrics metrics;
	int result = memoizedVersion::NumPaths<larger_size>(1, 1, metrics);

//	metrics.print();
	assert(result == 40116600);
	assert(metrics.calledTimes == 393);
	assert(metrics.hadToCalculate == 196);
	assert(metrics.gotFromCache == 169);
}

void testHugeMemoizedVersion() {
	int const larger_size = 20;
	memoizedVersion::Metrics metrics;
	int result = memoizedVersion::NumPaths<larger_size>(1, 1, metrics);

//	metrics.print();
	assert(result == 985525432);
	assert(metrics.calledTimes == 723);
	assert(metrics.hadToCalculate == 361);
	assert(metrics.gotFromCache == 324);
}
