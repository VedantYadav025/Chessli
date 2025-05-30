#pragma once

#include "pieces/pieces.h"
#include <array>
#include <cstddef>
#include <cstdint>
#include <unordered_map>



namespace Chess {

using BitBoard = std::uint64_t;

constexpr void
unsetBit(BitBoard& bitboard, const size_t& bit)
{
  bitboard &= ~(1ULL << bit);
}

constexpr void
setBit(BitBoard& bitboard, const size_t& bit)
{
  bitboard |= 1ULL << bit;
}

constexpr std::array<BitBoard, 8> mask_rank = {
  0x00000000000000FF, 0x000000000000FF00, 0x0000000000FF0000,
  0x00000000FF000000, 0x000000FF00000000, 0x0000FF0000000000,
  0x00FF000000000000, 0xFF00000000000000,
};

constexpr std::array<BitBoard, 8> mask_file = {
  0x0101010101010101, 0x0202020202020202, 0x0404040404040404,
  0x0808080808080808, 0x1010101010101010, 0x2020202020202020,
  0x4040404040404040, 0x8080808080808080,
};

constexpr std::array<BitBoard, 8> clear_rank = {
  ~mask_rank[0], ~mask_rank[1], ~mask_rank[2], ~mask_rank[3],
  ~mask_rank[4], ~mask_rank[5], ~mask_rank[6], ~mask_rank[7],
};

constexpr std::array<BitBoard, 8> clear_file = {
  ~mask_file[0], ~mask_file[1], ~mask_file[2], ~mask_file[3],
  ~mask_file[4], ~mask_file[5], ~mask_file[6], ~mask_file[7],
};

inline std::unordered_map<char, Piece> charToPiece = {
  { 'r', { Piece_type::Rook, Color_type::Black } },
  { 'n', { Piece_type::Knight, Color_type::Black } },
  { 'b', { Piece_type::Bishop, Color_type::Black } },
  { 'q', { Piece_type::Queen, Color_type::Black } },
  { 'k', { Piece_type::King, Color_type::Black } },
  { 'p', { Piece_type::Pawn, Color_type::Black } },

  { 'R', { Piece_type::Rook, Color_type::White } },
  { 'N', { Piece_type::Knight, Color_type::White } },
  { 'B', { Piece_type::Bishop, Color_type::White } },
  { 'Q', { Piece_type::Queen, Color_type::White } },
  { 'K', { Piece_type::King, Color_type::White } },
  { 'P', { Piece_type::Pawn, Color_type::White } },
};

void
printBitBoard(const BitBoard& bitboard);

}
