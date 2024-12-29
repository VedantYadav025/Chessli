#include <iostream>
#include <cstdint>
#include <cassert>
using BitBoard = std::uint64_t;

const enum class Color: std::uint16_t {
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

inline bool getBitOfBitBoard(const BitBoard& bitboard, const std::int8_t index) {
	if (index < 0 || index > 63)
		throw std::invalid_argument("Index is out of range\n");
	return (bitboard >> index) & 1;
}


inline BitBoard maskRank(const std::uint8_t &index) {
	if (index < 0 || index > 7)
		throw std::invalid_argument("Index out of range\n");
	BitBoard mask = 0x00000000000000FF;
	mask = mask << (8 * index);
	return mask;
}

inline BitBoard maskFile(const std::uint8_t& index) {
	if (index < 0 || index > 7)
		throw std::invalid_argument("Index is out of range\n");
	BitBoard mask = 0x0101010101010101;
	mask = mask << index;
	return mask;
}

inline BitBoard clearFile(const std::uint8_t& index) {
	if (index < 0 || index > 7)
		throw std::invalid_argument("Index is out of range\n");
	return ~maskFile(index);
}

void printU64(const BitBoard& bitboard) {
	// Loop through the bits in chunks of 8
	for (int i = 56; i >= 0; i -= 8) {
		// Print each chunk of 8 bits
		for (int j = 0; j <= 7; ++j) {
			std::cout << ((bitboard >> (i + j)) & 1);
		}
		std::cout << std::endl;
	}
}


