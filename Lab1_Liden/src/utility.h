/**
 * Lab 1
 *
 * Various loose utility functions used in TicTacToe files
 *
 * Written by Benjamin Liden
 * 		for Prof. Temesvari's CS240
 * 		on 1/31/2021
 */
#pragma once

#include <string>
#include <iostream>

#define EMPTY_MARK ' '
#define X_MARK 'X'
#define O_MARK 'O'

/*
 * Enum of possible players
 */
enum class player {
	X, O
};

/**
 * Pair of coordinates for plotting marks
 */
typedef struct coords {
	int row;
	int col;
} coords;

// Utility Function Declaration
bool matchMarks(const char &one, const char &two, const char &three);
char playerToChar(const player &p);
void getCoords(std::istream& in, std::ostream& out, const std::string message, coords &inputCoords);
void getString(std::istream& in, std::ostream& out, const std::string &message, std::string &inputString);
