// Chess.cpp : Defines the entry point for the application.
//
#include "Chess.h"
#include "Board.h"
#include <iostream>

int main() {
	Board chess_board;
	chess_board.clearBoard();
	chess_board.setPieceOnSquare(Piece::Rook, Color::White, Square::a2);
	chess_board.printAllPieces();
	std::cout << "\n\n\n";
	printU64(chess_board.whiteRookValid(Square::a2));
	return 0;
}