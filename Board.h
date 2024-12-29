#pragma once

#include "Pieces.h"
#include <array>
#include <cstdint>
#include <string>
#include <cctype>
#include <algorithm>
#include <unordered_map>

enum class Square : std::uint8_t {
	a1 = 0, b1, c1, d1, e1, f1, g1, h1,
	a2, b2, c2, d2, e2, f2, g2, h2,
	a3, b3, c3, d3, e3, f3, g3, h3,
	a4, b4, c4, d4, e4, f4, g4, h4,
	a5, b5, c5, d5, e5, f5, g5, h5,
	a6, b6, c6, d6, e6, f6, g6, h6,
	a7, b7, c7, d7, e7, f7, g7, h7,
	a8, b8, c8, d8, e8, f8, g8, h8
};

inline std::int16_t rank(const Square& sq) {
	return (static_cast<std::int16_t>(sq) / 8 + 1);
}

inline std::string toLower(const std::string& str) {
	std::string lowerStr = str;
	std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
		[](unsigned char c) { return std::tolower(c); });
	return lowerStr;
}

// Conversion function: string to Square
inline Square stringToSquare(const std::string& input) {
	static const std::unordered_map<std::string, Square> squareMap = {
		{"a1", Square::a1}, {"b1", Square::b1}, {"c1", Square::c1}, {"d1", Square::d1},
		{"e1", Square::e1}, {"f1", Square::f1}, {"g1", Square::g1}, {"h1", Square::h1},
		{"a2", Square::a2}, {"b2", Square::b2}, {"c2", Square::c2}, {"d2", Square::d2},
		{"e2", Square::e2}, {"f2", Square::f2}, {"g2", Square::g2}, {"h2", Square::h2},
		{"a3", Square::a3}, {"b3", Square::b3}, {"c3", Square::c3}, {"d3", Square::d3},
		{"e3", Square::e3}, {"f3", Square::f3}, {"g3", Square::g3}, {"h3", Square::h3},
		{"a4", Square::a4}, {"b4", Square::b4}, {"c4", Square::c4}, {"d4", Square::d4},
		{"e4", Square::e4}, {"f4", Square::f4}, {"g4", Square::g4}, {"h4", Square::h4},
		{"a5", Square::a5}, {"b5", Square::b5}, {"c5", Square::c5}, {"d5", Square::d5},
		{"e5", Square::e5}, {"f5", Square::f5}, {"g5", Square::g5}, {"h5", Square::h5},
		{"a6", Square::a6}, {"b6", Square::b6}, {"c6", Square::c6}, {"d6", Square::d6},
		{"e6", Square::e6}, {"f6", Square::f6}, {"g6", Square::g6}, {"h6", Square::h6},
		{"a7", Square::a7}, {"b7", Square::b7}, {"c7", Square::c7}, {"d7", Square::d7},
		{"e7", Square::e7}, {"f7", Square::f7}, {"g7", Square::g7}, {"h7", Square::h7},
		{"a8", Square::a8}, {"b8", Square::b8}, {"c8", Square::c8}, {"d8", Square::d8},
		{"e8", Square::e8}, {"f8", Square::f8}, {"g8", Square::g8}, {"h8", Square::h8}
	};

	std::string lowerInput = toLower(input);
	auto it = squareMap.find(lowerInput);
	if (it != squareMap.end()) {
		return it->second;
	}
	else {
		throw std::invalid_argument("Invalid square name: " + input);
	}
}

inline BitBoard bitboardOfSquare(const Square& square_name) {
	if (static_cast<std::uint8_t>(square_name) < 0 || static_cast<std::uint8_t>(square_name) > 63)
		throw std::invalid_argument("Not a valid square\n");
	return (1ULL << static_cast<std::uint8_t>(square_name));
}


class Board {
public:
	Board();
	void clearBoard();
	void setPieceOnSquare(const Piece& p, const Color& c, const Square& sq);
	BitBoard allWhitePieces() const;
	BitBoard allBlackPieces() const;
	BitBoard allPieces() const;
	BitBoard whiteKingValid(const Square& sq) const;
	BitBoard blackKingValid(const Square& sq) const;
	BitBoard whiteKnightValid(const Square& sq) const;
	BitBoard blackKnightValid(const Square& sq) const;
	BitBoard whitePawnValid(const Square& sq) const;
	BitBoard blackPawnValid(const Square& sqj) const;
	void printBitBoard(const Piece &p, const Color &c) const;
	void printAllWhitePieces() const;
	void printAllBlackPieces() const;
	void printAllPieces() const;
	PieceInfo& getPieceInfo(const Piece& p, const Color& c);

private:
	bool white_can_castle_kingside;
	bool white_can_castle_queenside;
	bool black_can_castle_kingside;
	bool black_can_castle_queenside;
	PieceInfo white_rooks_;
	PieceInfo white_knights_;
	PieceInfo white_pawns_;
	PieceInfo white_bishops_;
	PieceInfo white_queens_;
	PieceInfo white_king_;
	PieceInfo black_pawns_;
	PieceInfo black_rooks_;
	PieceInfo black_knights_;
	PieceInfo black_bishops_;
	PieceInfo black_queens_;
	PieceInfo black_king_;
};