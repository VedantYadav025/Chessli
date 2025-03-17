// Chessli.cpp : Defines the entry point for the application.
//

#include "Chessli.h"


int main()
{
	/*
	Chess::Game chess_game;
	//std::string_view fen_string = "4k2r/6r1/8/8/8/8/3R4/R3K3 w Qk";
	chess_game.printBoard();
	chess_game.makeMove({ Chess::Square::e2, Chess::Square::e4 });
	chess_game.makeMove({ Chess::Square::d7, Chess::Square::d5 });
	std::cout << "*******************\n";
	chess_game.printBoard();
	std::cout << "*******************\n";
	Chess::printBitBoard(chess_game.getEngine().blackPawnValid(Chess::Square::d5));
	*/
	for (std::size_t i = 0; i < 64; i++)
	{
		std::cout << "Square: " << static_cast<Chess::Square>(i) << std::endl;
		Chess::printBitBoard(Chess::rook_mask[i]);
	}
	return 0;
}
