#include "Pieces.h"
#include <cstdint>

class BitBoard {
public:
	BitBoard(Piece& piece, Color& color);
	void printBitBoard() const;
	BitBoard allWhitePieces() const;
	BitBoard allBlackPieces() const;
	BitBoard allPieces() const;
private:
	std::uint64_t bitboard_;
	Piece piece_;
	Color color_;
};