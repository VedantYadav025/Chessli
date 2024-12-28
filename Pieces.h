#include <iostream>

enum class Color: std::uint16_t {
	White = 0,
	Black,
};

const enum class Piece : std::uint16_t{
	Pawn = 0,
	Knight,
	Bishop,
	Rook,
	Queen,
	King,
};

struct PieceInfo {
	Color color_;
	Piece piece_;
	BitBoard bitboard_;
};

// valueOfPiece(white_pawns_.piece_)

inline std::int32_t  valueOfPiece(const Piece& piece) {
	if (piece == Piece::Pawn)
		return 1;
	else if (piece == Piece::Knight || piece == Piece::Bishop)
		return 3;
	else if (piece == Piece::Rook)
		return 5;
	else if (piece == Piece::Queen)
		return 9;
	else if (piece == Piece::King)
		return INT32_MAX;
	else
		throw std::invalid_argument("Invalid piece");
}
