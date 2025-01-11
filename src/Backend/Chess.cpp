// Chess.cpp : Defines the entry point for the application.
//
#include "Board.h"
#include "utils.h"
#include <iostream>

int main() {
	Board chess_board;
	chess_board.clearBoard();
	chess_board.setPieceOnSquare(Piece::Rook, Color::White, Square::a1);
	chess_board.setPieceOnSquare(Piece::Knight, Color::White, Square::f1);
	chess_board.setPieceOnSquare(Piece::Pawn, Color::Black, Square::a5);
	chess_board.setPieceOnSquare(Piece::King, Color::Black, Square::a6);
	chess_board.printAllPieces();
	std::cout << "\n\n\n";
	printU64(chess_board.whiteRookValid(Square::a1));
	return 0;
}
