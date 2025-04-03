// Chessli.cpp : Defines the entry point for the application.
//

#include "Chessli.h"

int main()
{
	std::string_view fen_string = "2kr1bnr/1ppbpppp/p1n5/8/3P4/2N2N2/PPP1BPPP/R1BR2K1 b";
	Chess::Game chess_game(fen_string);
	chess_game.printBoard();
	std::cout << "*****************************\n\n";
	// Chess::printBitBoard(chess_game.getEngine().whiteBishopValid(Chess::Square::e2));
	return 0;
}
