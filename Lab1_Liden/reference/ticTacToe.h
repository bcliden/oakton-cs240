//Ivan Temesvari
//CSC 240-0C1
//Summer 2011
//May 23, 2011
//This is the header file for the ticTacToe game described on p. 58
//of Lab Exercises in Data Structures with C++ by Malik 2010
#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <string>

using namespace std;
 
enum status {WIN, DRAW, CONTINUE};

class ticTacToe
{
public:
	void play();
       //Function to start the play.

    void displayBoard() const;
       //Function to print the board.

    bool isValidMove(int x, int y) const;
       //Function to determine if a move is valid.

	bool getXOMove(char moveSymbol);
       //Function to get a move for a player

    status gameStatus();
       //Function to determine the current status of the game.

    void reStart();
       //Function to restart the game.

    ticTacToe();
       //Default constructor.
       //Postcondition: Initializes the board to an empty state.

private:
    char board[3][3];
    int noOfMoves; 
};

#endif
