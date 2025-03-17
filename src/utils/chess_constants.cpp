#include "chess_constants.h"

namespace Chess
{

	const std::uint64_t WHITE_KING_INIT = (1ULL << squareToBit(Square::e1));
	const std::uint64_t BLACK_KING_INIT = (1ULL << squareToBit(Square::e8));
	const std::uint64_t WHITE_QUEEN_INIT = (1ULL << squareToBit(Square::d1));
	const std::uint64_t BLACK_QUEEN_INIT = (1ULL << squareToBit(Square::d8));
	const std::uint64_t WHITE_ROOK_INIT =
		(1ULL << squareToBit(Square::a1)) | (1ULL << squareToBit(Square::h1));
	const std::uint64_t BLACK_ROOK_INIT =
		(1ULL << squareToBit(Square::a8)) | (1ULL << squareToBit(Square::h8));
	const std::uint64_t WHITE_BISHOP_INIT =
		(1ULL << squareToBit(Square::c1)) | (1ULL << squareToBit(Square::f1));
	const std::uint64_t BLACK_BISHOP_INIT =
		(1ULL << squareToBit(Square::c8)) | (1ULL << squareToBit(Square::f8));
	const std::uint64_t WHITE_KNIGHT_INIT =
		(1ULL << squareToBit(Square::b1)) | (1ULL << squareToBit(Square::g1));
	const std::uint64_t BLACK_KNIGHT_INIT =
		(1ULL << squareToBit(Square::b8)) | (1ULL << squareToBit(Square::g8));
	const std::uint64_t WHITE_PAWN_INIT = 0x000000000000FF00;
	const std::uint64_t BLACK_PAWN_INIT = 0x00FF000000000000;

	const int WHITE_KING_IDX = 0;
	const int BLACK_KING_IDX = 1;
	const int WHITE_QUEEN_IDX = 2;
	const int BLACK_QUEEN_IDX = 3;
	const int WHITE_ROOK_IDX = 4;
	const int BLACK_ROOK_IDX = 5;
	const int WHITE_BISHOP_IDX = 6;
	const int BLACK_BISHOP_IDX = 7;
	const int WHITE_KNIGHT_IDX = 8;
	const int BLACK_KNIGHT_IDX = 9;
	const int WHITE_PAWN_IDX = 10;
	const int BLACK_PAWN_IDX = 11;

	const int WHITE_KING_SIDE = 0;
	const int WHITE_QUEEN_SIDE = 1;
	const int BLACK_KING_SIDE = 2;
	const int BLACK_QUEEN_SIDE = 3;

	char pieceToLetter(std::uint64_t piece_idx)
	{
		switch (piece_idx)
		{
		case (WHITE_KING_IDX):
			return 'K';
		case (BLACK_KING_IDX):
			return 'k';
		case (WHITE_QUEEN_IDX):
			return 'Q';
		case (BLACK_QUEEN_IDX):
			return 'q';
		case (WHITE_ROOK_IDX):
			return 'R';
		case (BLACK_ROOK_IDX):
			return 'r';
		case (WHITE_BISHOP_IDX):
			return 'B';
		case (BLACK_BISHOP_IDX):
			return 'b';
		case (WHITE_KNIGHT_IDX):
			return 'N';
		case (BLACK_KNIGHT_IDX):
			return 'n';
		case (WHITE_PAWN_IDX):
			return 'P';
		case (BLACK_PAWN_IDX):
			return 'p';
		default:
			break;
		}
		return 0;
	}
}  // namespace Chess