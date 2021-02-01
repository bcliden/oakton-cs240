/**
 * Lab 1: ticTacToe Driver
 *
 * Written by Benjamin Liden
 * 		for Prof. Temesvari's CS240
 * 		on 1/31/2021
 */

#include <iostream>
#include <sstream>
#include <assert.h>

#include "ticTacToe.h"

using namespace std;

void runGame();
void testSuite();
void testWin();
void testDraw();
void testDuplicateInputs();
void testPlayMultiple();

int main() {
	// to play a normal game:
	runGame();
	// to run the test suite:
	testSuite();
	return 0;
}

void testSuite(){
	testWin();
	testDraw();
	testDuplicateInputs();
	testPlayMultiple();
	cout << "All Tests Passed." << endl;
}

void runGame() {
	ticTacToe game;
	game.play();
}

void testWin() {
	stringstream in;
	in << "1 1" << endl // x
			<< "1 3" << endl // o
			<< "2 1" << endl // x
			<< "2 3" << endl // o
			<< "3 1" << endl // x wins
			<< "n" << endl; // don't continue
	stringstream out;
	ticTacToe game { in, out };
	game.play();

	// https://www.cplusplus.com/reference/string/string/find/
	assert(out.str().find("Player X won") != string::npos);
}

void testDraw() {
	stringstream in;
	in << "1 1" << endl // x
			<< "2 2" << endl // o
			<< "3 3" << endl // x
			<< "1 3" << endl // o
			<< "3 1" << endl // x
			<< "3 2" << endl // o
			<< "2 3" << endl // x
			<< "2 1" << endl // o
			<< "1 2" << endl // x
			<< "n" << endl; // don't continue
	stringstream out;
	ticTacToe game { in, out };
	game.play();

	// https://www.cplusplus.com/reference/string/string/find/
	assert(out.str().find("it was a draw") != string::npos);
}

void testDuplicateInputs() {
	stringstream in;
	in << "1 1" << endl // x
			<< "1 3" << endl // o
			// repeated inputs will just prompt again
			<< "1 3" << endl // x
			<< "1 3" << endl // x
			<< "1 3" << endl // x
			<< "1 3" << endl // x
			<< "1 3" << endl // x
			<< "1 3" << endl // x
			<< "1 3" << endl // x
			<< "1 3" << endl // x
			// good selection is made and play resumes as normal
			<< "2 1" << endl // x
			<< "2 3" << endl // o
			<< "3 1" << endl // x wins
			<< "n" << endl; // don't continue
	stringstream out;
	ticTacToe game { in, out };
	game.play();

	// https://www.cplusplus.com/reference/string/string/find/
	assert(out.str().find("Player X won") != string::npos);
}

void testPlayMultiple() {
	stringstream in;
	in << "1 1" << endl // x
			<< "1 3" << endl // o
			<< "2 1" << endl // x
			<< "2 3" << endl // o
			<< "3 1" << endl // x wins
			<< "y" << endl // YES, continue
			<< "1 1" << endl // x
			<< "2 2" << endl // o
			<< "3 3" << endl // x
			<< "1 3" << endl // o
			<< "3 1" << endl // x
			<< "3 2" << endl // o
			<< "2 3" << endl // x
			<< "2 1" << endl // o
			<< "1 2" << endl // x. draw condition
			<< "n" << endl; // don't continue
	stringstream out;
	ticTacToe game { in, out };
	game.play();

	// https://www.cplusplus.com/reference/string/string/find/
	assert(out.str().find("Player X won") != string::npos); // first game result
	assert(out.str().find("it was a draw") != string::npos); // second game result

}
