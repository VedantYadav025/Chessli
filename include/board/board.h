#pragma once

#include "../move/move.h"
#include "../pieces/pieces.h"
#include "../utils/utils.h"

#include <array>
#include <string_view>
#include <vector>

namespace Chess {

enum {
  WHITE_PAWN_IDX,
  WHITE_KNIGHT_IDX,
  WHITE_BISHOP_IDX,
  WHITE_ROOK_IDX,
  WHITE_QUEEN_IDX,
  WHITE_KING_IDX,
  BLACK_PAWN_IDX,
  BLACK_KNIGHT_IDX,
  BLACK_BISHOP_IDX,
  BLACK_ROOK_IDX,
  BLACK_QUEEN_IDX,
  BLACK_KING_IDX
};

constexpr BitBoard indexOfPiece(const Piece& piece) {
  switch (piece.m_piece) {
    case Piece_type::Pawn:
      return piece.m_color == Color_type::White ? WHITE_PAWN_IDX
                                                : BLACK_PAWN_IDX;
    case Piece_type::Knight:
      return piece.m_color == Color_type::White ? WHITE_KNIGHT_IDX
                                                : BLACK_KNIGHT_IDX;
    case Piece_type::Bishop:
      return piece.m_color == Color_type::White ? WHITE_BISHOP_IDX
                                                : BLACK_BISHOP_IDX;
    case Piece_type::Rook:
      return piece.m_color == Color_type::White ? WHITE_ROOK_IDX
                                                : BLACK_ROOK_IDX;
    case Piece_type::Queen:
      return piece.m_color == Color_type::White ? WHITE_QUEEN_IDX
                                                : BLACK_QUEEN_IDX;
    case Piece_type::King:
      return piece.m_color == Color_type::White ? WHITE_KING_IDX
                                                : BLACK_KING_IDX;
    default:
      return -1;
  }
}

class Board {
 public:
  explicit Board();
  explicit Board(const std::string_view& fen_string);
  void makeMove(const Move& move);
  void printBoard() const;
  BitBoard allWhitePiecesBitBoard() const;
  BitBoard allBlackPiecesBitBoard() const;
  BitBoard allPiecesBitBoard() const;
  Piece getPieceAtSquare(const Square& square) const;

 private:
  std::array<BitBoard, 12> m_bitboards;
  std::array<Piece, 64> m_piece_at_array;
};

}  // namespace Chess
