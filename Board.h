#include "Pieces.h"
#include <array>
#include <cstdint>
#include <unordered_map>

using BitBoard = std::uint64_t;

class Board {
public:
	Board();

private:
	bool white_can_castle_kingside;
	bool white_can_castle_queenside;
	bool black_can_castle_kingside;
	bool black_can_castle_queenside;
	std::pair<std::pair<Color, Piece>, BitBoard> white_pawns_;
	std::pair<std::pair<Color, Piece>, BitBoard> white_rooks_;
	std::pair<std::pair<Color, Piece>, BitBoard> white_knights_;
	std::pair<std::pair<Color, Piece>, BitBoard> white_bishops_;
	std::pair<std::pair<Color, Piece>, BitBoard> white_queens_;
	std::pair<std::pair<Color, Piece>, BitBoard> white_king_;
	std::pair<std::pair<Color, Piece>, BitBoard> black_pawns_;
	std::pair<std::pair<Color, Piece>, BitBoard> black_rooks_;
	std::pair<std::pair<Color, Piece>, BitBoard> black_knights_;
	std::pair<std::pair<Color, Piece>, BitBoard> black_bishops_;
	std::pair<std::pair<Color, Piece>, BitBoard> black_queens_;
	std::pair<std::pair<Color, Piece>, BitBoard> black_king_;
};