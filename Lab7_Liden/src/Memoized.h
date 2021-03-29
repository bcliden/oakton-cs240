#pragma once

//============================================================================
// Name        : Lab 7
// Author      : Benjamin Liden
// Date        : Mar 29, 2021
// Professor   : Ivan Temesvari
// Course	   : CS240 Data Structures
//============================================================================

#include <iostream>
#include "TwoDimensionCache.h"

namespace memoizedVersion {

class Metrics {
public:
	int size = 0;
	int calledTimes = 0;
	int hadToCalculate = 0;
	int gotFromCache = 0;
	Metrics() :
			calledTimes(0), hadToCalculate(0), gotFromCache(0) {
	}
	void print(std::ostream &out = std::cout) {
		out << size << 'x' << size << " grid | " << "called " << calledTimes
				<< " times |" << " Had to calculate: " << hadToCalculate
				<< " | " << "Got from cache: " << gotFromCache << std::endl;
	}
};

/**
 * Recursively calculate the number of paths possible in
 * 		an nxn square.
 *
 * 	Needs starting point (row, col) and value cache reference to begin.
 *
 * 	Will also capture metrics as it works.
 */
template<int size>
int _NumPaths(int row, int col, TwoDimensionCache<int> &cache, Metrics &m) {
	++m.calledTimes;
	if (row == size || col == size) {
		return 1;
	}

	if (cache.has(row, col)) {
		++m.gotFromCache;
		return cache.get(row, col);
	}

	++m.hadToCalculate;
	int result = _NumPaths<size>(row + 1, col, cache, m)
			+ _NumPaths<size>(row, col + 1, cache, m);
	cache.store(row, col, result);
	return result;
}

/**
 * This is the top-level function that initializes the cache.
 * Same signature as the non-memoized version.
 *
 * It calls the underscore-prefixed version, which does the recursive action.
 */
template<int size>
int NumPaths(int row, int col, Metrics &m) {
	m.size = size;
	TwoDimensionCache<int> cache { size, INT_MIN };
	int result = _NumPaths<size>(row, col, cache, m);
	return result;
}
}
