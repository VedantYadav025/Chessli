#include "bitboard.h"

void Chess::printBitBoard(const BitBoard& bitboard)
{
	for (int rank = 7; rank >= 0; --rank) {
		std::cout << (rank + 1) << "  ";
 		for (int file = 0; file < 8; ++file) {
			int bit_index = rank * 8 + file;
			std::cout << ((bitboard & (1ULL << bit_index)) ? '1' : '0') << ' ';
		}
		std::cout << '\n';
	}
	std::cout << "   a b c d e f g h\n";
}
