#pragma once

#include <limits>
#include <random>

// random number generation syntax initially provided by:
// https://docs.microsoft.com/en-us/cpp/standard-library/random

class RandomInt {
public:
	RandomInt(int lower = std::numeric_limits<int>::min(), int upper =
			std::numeric_limits<int>::max()) :
			lower(lower), upper(upper), gen(rd()), dist(lower, upper) {
	}

	int getNumber() {
		return dist(gen);
	}

	int lowerLimit() {
		return lower;
	}

	int upperLimit() {
		return upper;
	}

private:
	int lower;
	int upper;
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_int_distribution<> dist;
};
