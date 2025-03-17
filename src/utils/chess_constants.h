#pragma once

#include <cstdint>
#include <stdexcept>
#include <string>
#include <ostream>

namespace Chess {

	enum class Square : std::uint8_t
	{
		a1, b1, c1, d1, e1, f1, g1, h1,
		a2, b2, c2, d2, e2, f2, g2, h2,
		a3, b3, c3, d3, e3, f3, g3, h3,
		a4, b4, c4, d4, e4, f4, g4, h4,
		a5, b5, c5, d5, e5, f5, g5, h5,
		a6, b6, c6, d6, e6, f6, g6, h6,
		a7, b7, c7, d7, e7, f7, g7, h7,
		a8, b8, c8, d8, e8, f8, g8, h8
	};

	inline std::ostream& operator<<(std::ostream& os, const Square& sq) 
	{
		char file = 'a' + (static_cast<int>(sq) % 8);
		char rank = '1' + (static_cast<int>(sq) / 8);

		os << file << rank;
		return os;
	}

	inline constexpr std::uint32_t squareToBit(const Square& square) 
	{
		return static_cast<std::uint32_t> (square);
	}

	char pieceToLetter(std::uint64_t piece_idx);

	extern const std::uint64_t WHITE_KING_INIT;
	extern const std::uint64_t BLACK_KING_INIT;
	extern const std::uint64_t WHITE_QUEEN_INIT;
	extern const std::uint64_t BLACK_QUEEN_INIT;
	extern const std::uint64_t WHITE_ROOK_INIT;
	extern const std::uint64_t BLACK_ROOK_INIT;
	extern const std::uint64_t WHITE_BISHOP_INIT;
	extern const std::uint64_t BLACK_BISHOP_INIT;
	extern const std::uint64_t WHITE_KNIGHT_INIT;
	extern const std::uint64_t BLACK_KNIGHT_INIT;
	extern const std::uint64_t WHITE_PAWN_INIT;
	extern const std::uint64_t BLACK_PAWN_INIT;

	/*
	The Board class will have 12 bit boards, of each (piece,type) pair.
	I will store them in a std::array, and for indexing them, I am creating these
	aliases
	*/
	extern const int WHITE_KING_IDX;
	extern const int BLACK_KING_IDX;
	extern const int WHITE_QUEEN_IDX;
	extern const int BLACK_QUEEN_IDX;
	extern const int WHITE_ROOK_IDX;
	extern const int BLACK_ROOK_IDX;
	extern const int WHITE_BISHOP_IDX;
	extern const int BLACK_BISHOP_IDX;
	extern const int WHITE_KNIGHT_IDX;
	extern const int BLACK_KNIGHT_IDX;
	extern const int WHITE_PAWN_IDX;
	extern const int BLACK_PAWN_IDX;


	extern const int WHITE_KING_SIDE;
	extern const int WHITE_QUEEN_SIDE;
	extern const int BLACK_KING_SIDE;
	extern const int BLACK_QUEEN_SIDE;
}