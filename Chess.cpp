// Chess.cpp : Defines the entry point for the application.
//
#include "Chess.h"
#include "Board.h"

int main() {
	Board chess_board;
	chess_board.clearBoard();
	chess_board.setPieceOnSquare(Piece::Knight, Color::Black, Square::a4);
	std::cout << "Set Piece on board\n";
	chess_board.printAllPieces();
	std::cout << "Attack BitBoard of White Knight\n";
	printU64(chess_board.whiteKnightValid());
	return 0;
}