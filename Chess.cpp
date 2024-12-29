// Chess.cpp : Defines the entry point for the application.
//
#include "Chess.h"
#include "Board.h"

int main() {
	Board chess_board;
	chess_board.clearBoard();
	chess_board.setPieceOnSquare(Piece::Pawn, Color::White, Square::a2);
	chess_board.setPieceOnSquare(Piece::Knight, Color::Black, Square::b3);
	std::cout << "Original Board: \n";
	chess_board.printAllPieces();
	std::cout << "BitBoard of places pawn can move, when placed on a2\n";
	printU64(chess_board.whitePawnValid(Square::a2));
	return 0;
}