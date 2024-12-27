#include <iostream>

enum Color {
	White,
	Black,
	ColorLess,  // for printing 
};

enum Piece {
	Pawn,
	Knight,
	Bishop,
	Rook,
	Queen,
	King,
};

std::int32_t  valueOfPiece(const Piece& piece) {
	if (piece == 0)
		return 1;
	else if (piece == 1)
		return 3;
	else if (piece == 2)
		return 3;
	else if (piece == 3)
		return 5;
	else if (piece == 4)
		return 9;
	else if (piece == 5)
		return INT32_MAX;
	else
		throw std::invalid_argument("Invalid piece");
}
