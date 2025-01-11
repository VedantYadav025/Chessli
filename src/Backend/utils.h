#pragma once 

#include "Pieces.h"
#include <cstdint>

inline std::uint64_t clearBit(const BitBoard& bitboard, const std::uint8_t &bit_pos) {
    std::uint64_t mask = ~(1ULL << bit_pos);
    return bitboard & mask;
}