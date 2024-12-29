// Chess.cpp : Defines the entry point for the application.
//
#include "Chess.h"
#include "Board.h"

int main() {
	Board chess_board;
	chess_board.clearBoard();
	chess_board.setPieceOnSquare(Piece::King, Color::White, Square::a1);
	std::cout << "Original Board: \n";
	chess_board.printAllPieces();
	std::cout << "\n\n";
	std::cout << "BitBoard of Squares where King on a1 can attack: \n";
	printU64(chess_board.whiteKingValid());
	return 0;
}