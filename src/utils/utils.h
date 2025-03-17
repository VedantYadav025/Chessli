#pragma once

#include "chess_constants.h"
#include "../pieces.h"
#include <unordered_map>
#include <stdexcept>
#include <cstdint>
#include <string_view>
#include <cctype>
#include <array>

namespace Chess {

	// bits manipulations
#define get_bit(bitboard, square) (bitboard & (1ULL << square))
#define set_bit(bitboard, square) (bitboard |= (1ULL << square))
#define pop_bit(bitboard, square) (get_bit(bitboard, square) ? (bitboard ^= (1ULL << square)) : 0)

	struct Move {
		Square from_square, to_square;
	};

	std::unordered_map<Square, char> parseFEN(const std::string_view& fen_string);

	std::vector<Square> squaresOfPiece(const std::unordered_map<Square, char>& board_map, const std::uint64_t& piece_idx);

	std::array<bool, 4> castlingRights(const std::string_view& fen_string);

	constexpr inline std::uint64_t initialBitBoard(const Piece& piece, const Color& color) {
		switch (piece) {
		case Piece::King:   return (color == Color::White) ? WHITE_KING_INIT : BLACK_KING_INIT;
		case Piece::Queen:  return (color == Color::White) ? WHITE_QUEEN_INIT : BLACK_QUEEN_INIT;
		case Piece::Rook:   return (color == Color::White) ? WHITE_ROOK_INIT : BLACK_ROOK_INIT;
		case Piece::Bishop: return (color == Color::White) ? WHITE_BISHOP_INIT : BLACK_BISHOP_INIT;
		case Piece::Knight: return (color == Color::White) ? WHITE_KNIGHT_INIT : BLACK_KNIGHT_INIT;
		case Piece::Pawn:   return (color == Color::White) ? WHITE_PAWN_INIT : BLACK_PAWN_INIT;
		default:            throw std::invalid_argument("Not a valid piece");  // Invalid piece
		}
	}

	constexpr inline int indexOfPiece(const Piece& piece, const Color& color) {
		switch (piece) {
		case Piece::King: return (color == Color::White) ? WHITE_KING_IDX : BLACK_KING_IDX;
		case Piece::Queen: return (color == Color::White) ? WHITE_QUEEN_IDX : BLACK_QUEEN_IDX;
		case Piece::Rook: return (color == Color::White) ? WHITE_ROOK_IDX : BLACK_ROOK_IDX;
		case Piece::Bishop: return (color == Color::White) ? WHITE_BISHOP_IDX : BLACK_BISHOP_IDX;
		case Piece::Knight: return (color == Color::White) ? WHITE_KNIGHT_IDX : BLACK_KNIGHT_IDX;
		case Piece::Pawn: return (color == Color::White) ? WHITE_PAWN_IDX : BLACK_PAWN_IDX;
		default: throw std::invalid_argument("Not a valid piece");  // Invalid piece
		}
	}

	inline std::unordered_map<Square, char> makeInitialBoardMap() {
		std::unordered_map<Square, char> mp;

		// Initialize White pieces
		mp[Square::a1] = 'R'; mp[Square::b1] = 'N'; mp[Square::c1] = 'B'; mp[Square::d1] = 'Q';
		mp[Square::e1] = 'K'; mp[Square::f1] = 'B'; mp[Square::g1] = 'N'; mp[Square::h1] = 'R';
		mp[Square::a2] = 'P'; mp[Square::b2] = 'P'; mp[Square::c2] = 'P'; mp[Square::d2] = 'P';
		mp[Square::e2] = 'P'; mp[Square::f2] = 'P'; mp[Square::g2] = 'P'; mp[Square::h2] = 'P';

		// Initialize Black pieces
		mp[Square::a8] = 'r'; mp[Square::b8] = 'n'; mp[Square::c8] = 'b'; mp[Square::d8] = 'q';
		mp[Square::e8] = 'k'; mp[Square::f8] = 'b'; mp[Square::g8] = 'n'; mp[Square::h8] = 'r';
		mp[Square::a7] = 'p'; mp[Square::b7] = 'p'; mp[Square::c7] = 'p'; mp[Square::d7] = 'p';
		mp[Square::e7] = 'p'; mp[Square::f7] = 'p'; mp[Square::g7] = 'p'; mp[Square::h7] = 'p';

		return mp;
	}

	inline constexpr int count_bits(std::uint64_t bitboard) {
		// bit count
		int count = 0;

		// pop bits untill bitboard is empty
		while (bitboard)
		{
			// increment count
			count++;

			// consecutively reset least significant 1st bit
			bitboard &= bitboard - 1;
		}

		// return bit count
		return count;
	}

}