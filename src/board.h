#pragma once

#include "bitboard.h"
#include <array>
#include <iostream>

namespace Chess
{

	class Board
	{
	public:
		Board();
		Board(const std::string_view& fen_string);
		void printBoard() const;
		void makeMove(const Move& move);
		BitBoard allWhitePieces() const;
		BitBoard allBlackPieces() const;
		BitBoard allPieces() const;
		std::string getFEN() const;

	private:
		std::array<BitBoard, 12> bitboards_;
		std::array<bool, 4> right_to_castle_;
		Color side_to_move_;
		std::unordered_map<Square, char> board_map_;

	private:
		int indexOfPieceOccupyingSquare(const Square& sq) const; 
	};

}