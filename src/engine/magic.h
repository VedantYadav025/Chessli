#pragma once
#include <cstdint>
#include "../board.h"
#include "../bitboard.h"
namespace Chess {

	extern const int rook_relevant_bits[64];
	extern const int bishop_relevant_bits[64];

	// rook magic numbers
	extern const std::uint64_t rook_magics[64];
	extern const std::uint64_t bishop_magics[64];
	// 
	// extern const std::array<std::array<BitBoard, 512>, 64> bishop_attacks, rook_attacks;

	// get index of LS1B in bitboard
	int get_ls1b_index(const BitBoard& bitboard);

	BitBoard set_occupancy(int index, int bits_in_mask, BitBoard attack_mask);

	// rook attacks
	BitBoard rook_attacks_on_the_fly(int square, BitBoard block);
	BitBoard bishop_attacks_on_the_fly(int square, BitBoard block);

	//std::array<std::array<BitBoard, 4096>, 64> initRookAttack();
	std::vector<std::vector<BitBoard>> initRookAttack();
	std::vector<std::vector<BitBoard>> initBishopAttack();
}