#include "Pieces.h"
#include <cstdint>

class BitBoard {
public:
	BitBoard(Piece& piece, Color& color);
	void printBitBoard() const;
private:
	std::uint64_t bitboard_;
	Piece piece_;
	Color color_;
};