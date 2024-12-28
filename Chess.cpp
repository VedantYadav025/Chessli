// Chess.cpp : Defines the entry point for the application.
//
#include "Chess.h"

int main() {
	Board chess_board;
	std::cout << "ALL BLACK PIECES\n";
	chess_board.printAllBlackPieces();
	std::cout << "ALL WHITE PIECES\n";
	chess_board.printAllWhitePieces();
	std::cout << "Value of Rook " << valueOfPiece(Piece::Rook) << '\n';
	return 0;
}