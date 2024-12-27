#include <iostream>

enum Color {
	White,
	Black,
};

enum Piece {
	Pawn,
	Knight,
	Bishop,
	Rook,
	Queen,
	King,
};

void valueOfPiece(const Piece& piece) {
	if (piece == 0)
		std::cout << "Pawn" << std::endl;
	else if (piece == 1)
		std::cout << "Knight" << std::endl;
	else if (piece == 2)
		std::cout << "Bishop" << std::endl;
	else if (piece == 3)
		std::cout << "Rook" << std::endl;
	else if (piece == 4)
		std::cout << "Queen" << std::endl;
	else if (piece == 5)
		std::cout << "King" << std::endl;
	else
		throw std::invalid_argument("Invalid piece");
}
