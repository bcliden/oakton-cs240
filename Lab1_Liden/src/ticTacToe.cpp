/**
 * Lab 1: ticTacToe implementation
 *
 * Written by Benjamin Liden
 * 		for Prof. Temesvari's CS240
 * 		on 1/31/2021
 */

#include <iostream>
#include <string>
#include <sstream>

#include "ticTacToe.h"
#include "utility.h"

using namespace std;



// TicTacToe Definition

void ticTacToe::play() {
	status gameCondition = status::CONTINUE;
	player currentPlayer = player::X;

	// Main Loop, runs while game is not a win or draw
	while (gameCondition == status::CONTINUE) {
		// 1. Draw board
		displayBoard();

		// cast currentPlayer as char to match function signature
		// 2. Get Player Move and return
		gameCondition = getXOMove(currentPlayer);

		// 3. Swap Active Player if continuing
		if (gameCondition == status::CONTINUE) {
			if (currentPlayer == player::X) {
				currentPlayer = player::O;
			} else /* currentPlayer is O */{
				currentPlayer = player::X;
			}
		}
	}

	// 4. Print final board and win/draw message
	displayBoard();
	if (gameCondition == status::DRAW) {
		out << "Darn, it was a draw." << endl;
	} else { // gameCondition is status::WIN
		out << "Congratulations, Player " << playerToChar(currentPlayer)
				<< " won in " << noOfMoves << " moves!" << endl;
	}

	// 5. Ask if the user wants to play again?
	string wantsToContinue;
	while (true) {
		getString(in, out, "Play again? Y/N", wantsToContinue);

		// if char is not y/Y/n/N, keep asking
		if (wantsToContinue != "y" && wantsToContinue != "Y"
				&& wantsToContinue != "n" && wantsToContinue != "N") {
			continue;
		}

		break;
	}

	if (wantsToContinue == "y" || wantsToContinue == "Y") {
		reStart();
	} else {
		out << "Thanks for playing!" << endl;
	}

}

/**
 * Prints entire board in from class.
 *
 * Currently locked into a 3x3 board size.
 *
 *   1   2   3
 * 1   |   |
 *  ---|---|---
 * 2   |   |
 *  ---|---|---
 * 3   |   |
 *
 */
void ticTacToe::displayBoard() const {
	out << "   1   2   3" << endl;
	out << endl;
	out << "1  " << board[0][0] << " | " << board[0][1] << " | " << board[0][2]
			<< endl;
	out << "  ---|---|---" << endl;
	out << "2  " << board[1][0] << " | " << board[1][1] << " | " << board[1][2]
			<< endl;
	out << "  ---|---|---" << endl;
	out << "3  " << board[2][0] << " | " << board[2][1] << " | " << board[2][2]
			<< endl;
	out << endl;
}

/**
 * Are the following coordinates a valid move?
 *
 * @param x: row
 * @param y: col
 */
bool ticTacToe::isValidMove(coords cellCoords) const {
	try {
		// check space at coords against empty space
		char space = board[cellCoords.row][cellCoords.col];
		if (space == EMPTY_MARK) {
			return true;
		}
	} catch (...) {
		// continue to return statement below
	}
	return false;
}

/**
 * Get move from player, validate it, and return game status
 *
 * @param moveSymbol: char of current player
 */
status ticTacToe::getXOMove(player currentPlayer) {
	coords currentCoords { -1, -1 }; // definitely an invalid move

	// while we have no valid move for this board, keep asking
	do {
		// get coordinates from user
		stringstream message;
		message << "Player " << playerToChar(currentPlayer) << " enter move: " << endl;
		getCoords(in, out, message.str(), currentCoords);

		// subtract one from the selections to match board array indices
		currentCoords.row -= 1;
		currentCoords.col -= 1;
	} while (!isValidMove(currentCoords));

	// add square onto board
	board[currentCoords.row][currentCoords.col] = playerToChar(currentPlayer);

	// increment noOfMoves
	noOfMoves += 1;

	return gameStatus();
}

/**
 *	Check game status for WIN & DRAW, or else continue
 */
status ticTacToe::gameStatus() {
	if ( /* check rows */
	matchMarks(board[0][0], board[0][1], board[0][2])
			|| matchMarks(board[1][0], board[1][1], board[1][2])
			|| matchMarks(board[2][0], board[2][1], board[2][2])
			/* check columns */
			|| matchMarks(board[0][0], board[1][0], board[2][0])
			|| matchMarks(board[0][1], board[1][1], board[2][1])
			|| matchMarks(board[0][2], board[1][2], board[2][2])
			/* check diagonals */
			|| matchMarks(board[0][0], board[1][1], board[2][2])
			|| matchMarks(board[0][2], board[1][1], board[2][0])) {
		return status::WIN;
	}

	// check if ANY squares are EMPTY
	for (auto const &row : board) {
		for (char const &cell : row) {
			// if a single cell is empty, we can continue playing. return immediately.
			if (cell == EMPTY_MARK) {
				return status::CONTINUE;
			}
		}
	}

	// at this point, we know no WIN is met and no spaces are empty.
	// This state MUST be a draw!
	return status::DRAW;
}

/**
 * Restart the game: reset all marks and number of moves, begin play.
 */
void ticTacToe::reStart() {
	resetBoard();
	play();
}

/**
 * Primary constructor. Initializes to empty board ready for play.
 */
ticTacToe::ticTacToe()
	:in(cin), out(cout)
{
	resetBoard();
}


/**
 * Secondary constructor for injecting streams for testing/extensibility.
 */
ticTacToe::ticTacToe(istream &inStream, ostream &outStream)
	:in(inStream), out(outStream)
{
	resetBoard();
}

/**
 * Initialize board to empty state.
 *
 * @Private
 *
 * loop as seen here: https://en.cppreference.com/w/cpp/language/range-for
 */
// PRIVATE MEMBERS
void ticTacToe::resetBoard() {
	for (auto& row : board) { // auto row OR char (&row)[3]. keeping auto for simplicity.
		for (char &cell : row) {
			cell = EMPTY_MARK;
		}
	}

	noOfMoves = 0;
}
