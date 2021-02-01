//Ivan Temesvari
//CSC 240-0C1
//Summer 2011
//May 23, 2011
//This is the header file for the ticTacToe game described on p. 58
//of Lab Exercises in Data Structures with C++ by Malik 2010
#pragma once

#include <iostream>
#include <string>
#include "utility.h"

enum class status {
	WIN, DRAW, CONTINUE
};

class ticTacToe {
public:
	void play();
	//Function to start the play.

	void displayBoard() const;
	//Function to print the board.

	bool isValidMove(coords cellCoords) const;
	//Function to determine if a move is valid.

	status getXOMove(player currentPlayer);
	//Function to get a move for a player

	status gameStatus();
	//Function to determine the current status of the game.

	void reStart();
	//Function to restart the game.

	ticTacToe();
	//Default constructor.
	//Postcondition: Initializes the board to an empty state.

	ticTacToe(std::istream& inStream, std::ostream& outStream);
	// add'l constructor for passing in streams

private:
	char board[3][3];
	int noOfMoves;

	/**
	 * Stream refs added for testing and extensibility
	 */
	std::istream& in;
	std::ostream& out;

	/**
	 * Member function added by Benjamin Liden.
	 * Resets board state to the default.
	 */
	void resetBoard();
};
