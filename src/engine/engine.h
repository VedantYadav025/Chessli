#pragma once
#include "../board.h"
#include "engine.h"
#include "magic.h"

namespace Chess
{
	class Engine
	{
	public:
		Engine(Board& board);
		BitBoard whiteKingValid(const Square& sq) const;
		BitBoard blackKingValid(const Square& sq) const;
		BitBoard whiteKnightValid(const Square& sq) const;
		BitBoard blackKnightValid(const Square& sq) const;
		BitBoard whitePawnValid(const Square& sq) const;
		BitBoard blackPawnValid(const Square& sq) const;
		BitBoard whiteRookValid(const Square& sq) const;
		BitBoard blackRookValid() const;
		BitBoard whiteBishopValid() const;
		BitBoard blackBishopValid() const;
		BitBoard whiteQueenValid() const;
		BitBoard blackQueenValid() const;
	private:
		Board& board_;
	};
}