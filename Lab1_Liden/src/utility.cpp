/**
 * Lab 1: utility.h implementations.
 *
 * Written by Benjamin Liden
 * 		for Prof. Temesvari's CS240
 * 		on 1/31/2021
 */

#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>

#include "utility.h"


/*
 * Get a given player's mark.
 */
char playerToChar(const player &p) {
	switch (p) {
	case player::X:
		return X_MARK;
	case player::O:
		return O_MARK;
	default:
		throw std::invalid_argument("Received unknown player token");
	}
}

/**
 * Are all three marks the same valid player marks?
 */
bool matchMarks(const char &one, const char &two, const char &three) {
	// don't match any empty spaces
	if (one == EMPTY_MARK || two == EMPTY_MARK || three == EMPTY_MARK) {
		return false;
	}
	// then see if all marks match
	return one == two && two == three;
}

/**
 * Get coordinates from user via stdin.
 *
 * @param currentCoords is the coords struct to read values into.
 *
 * input validation & clearing from https://isocpp.org/wiki/faq/input-output#istream-and-ignore
 */
void getCoords(std::istream& in, std::ostream& out, const std::string message, coords &inputCoords) {
	using namespace std;

	while (true) {
		out << message << endl;
		in >> inputCoords.row >> inputCoords.col;
		if (in.fail()) {
			in.clear();
			in.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		break;
	}
}

/**
 * Get a string from user via stdin.
 *
 * @param currentCoords is the coords struct to read values into.
 *
 * input validation & clearing from https://isocpp.org/wiki/faq/input-output#istream-and-ignore
 */
void getString(std::istream& in, std::ostream& out, const std::string &message, std::string &inputString) {
	using namespace std;

	while (true) {
		out << message << endl;
		in >> inputString;
		if (in.fail()) {
			in.clear();
			in.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		break;
	}
}

