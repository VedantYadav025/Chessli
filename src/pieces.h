#pragma once
#include <cstdint>

namespace Chess
{

	enum class Piece : std::uint32_t
	{
		Pawn,
		Knight,
		Bishop,
		Rook,
		Queen,
		King,
		None,
	};

	enum class Color : std::uint16_t
	{
		Black,
		White,
		None,
	};

	inline std::uint32_t valueOfPiece(Piece piece)
	{
		switch (piece) {
		case Piece::Pawn: return 1;
		case Piece::Knight: return 3;
		case Piece::Bishop: return 3;
		case Piece::Rook: return 5;
		case Piece::Queen: return 9;
		case Piece::King: return 0; // King is invaluable
		case Piece::None: return 0;
		default: return 0;
		}
	}
}