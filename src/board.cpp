#include "board/board.h"
#include "fen/fen.h"
#include "pieces/pieces.h"
#include "square/square.h"
#include "utils/constants.h"
#include "utils/utils.h"
#include "validMoveGenerator/validMoveGenerator.h"

#include <iostream>
#include <stdexcept>
#include <string_view>

namespace Chess {

Board::Board()
{
  m_bitboards[WHITE_PAWN_IDX] = WHITE_PAWN_INITIAL_POSITION;
  m_bitboards[WHITE_KNIGHT_IDX] = WHITE_KNIGHT_INITIAL_POSITION;
  m_bitboards[WHITE_BISHOP_IDX] = WHITE_BISHOP_INITIAL_POSITION;
  m_bitboards[WHITE_ROOK_IDX] = WHITE_ROOK_INITIAL_POSITION;
  m_bitboards[WHITE_QUEEN_IDX] = WHITE_QUEEN_INITIAL_POSITION;
  m_bitboards[WHITE_KING_IDX] = WHITE_KING_INITIAL_POSITION;

  m_bitboards[BLACK_PAWN_IDX] = BLACK_PAWN_INITIAL_POSITION;
  m_bitboards[BLACK_KNIGHT_IDX] = BLACK_KNIGHT_INITIAL_POSITION;
  m_bitboards[BLACK_BISHOP_IDX] = BLACK_BISHOP_INITIAL_POSITION;
  m_bitboards[BLACK_ROOK_IDX] = BLACK_ROOK_INITIAL_POSITION;
  m_bitboards[BLACK_QUEEN_IDX] = BLACK_QUEEN_INITIAL_POSITION;
  m_bitboards[BLACK_KING_IDX] = BLACK_KING_INITIAL_POSITION;

  m_piece_at_array[static_cast<int>(Square::h8)] = { Piece_type::Rook,
                                                     Color_type::Black };
  m_piece_at_array[static_cast<int>(Square::g8)] = { Piece_type::Knight,
                                                     Color_type::Black };
  m_piece_at_array[static_cast<int>(Square::f8)] = { Piece_type::Bishop,
                                                     Color_type::Black };
  m_piece_at_array[static_cast<int>(Square::e8)] = { Piece_type::Queen,
                                                     Color_type::Black };
  m_piece_at_array[static_cast<int>(Square::d8)] = { Piece_type::King,
                                                     Color_type::Black };
  m_piece_at_array[static_cast<int>(Square::c8)] = { Piece_type::Bishop,
                                                     Color_type::Black };
  m_piece_at_array[static_cast<int>(Square::b8)] = { Piece_type::Knight,
                                                     Color_type::Black };
  m_piece_at_array[static_cast<int>(Square::a8)] = { Piece_type::Rook,
                                                     Color_type::Black };

  for (int i = static_cast<int>(Square::a7); i <= static_cast<int>(Square::h7);
       ++i) {
    m_piece_at_array[i] = { Piece_type::Pawn, Color_type::Black };
  }

  for (int i = static_cast<int>(Square::a2); i <= static_cast<int>(Square::h2);
       ++i) {
    m_piece_at_array[i] = { Piece_type::Pawn, Color_type::White };
  }
  m_piece_at_array[static_cast<int>(Square::a1)] = { Piece_type::Rook,
                                                     Color_type::White };
  m_piece_at_array[static_cast<int>(Square::b1)] = { Piece_type::Knight,
                                                     Color_type::White };
  m_piece_at_array[static_cast<int>(Square::c1)] = { Piece_type::Bishop,
                                                     Color_type::White };
  m_piece_at_array[static_cast<int>(Square::d1)] = { Piece_type::Queen,
                                                     Color_type::White };
  m_piece_at_array[static_cast<int>(Square::e1)] = { Piece_type::King,
                                                     Color_type::White };
  m_piece_at_array[static_cast<int>(Square::f1)] = { Piece_type::Bishop,
                                                     Color_type::White };
  m_piece_at_array[static_cast<int>(Square::g1)] = { Piece_type::Knight,
                                                     Color_type::White };
  m_piece_at_array[static_cast<int>(Square::h1)] = { Piece_type::Rook,
                                                     Color_type::White };

  for (int i = static_cast<int>(Square::a3); i <= static_cast<int>(Square::h6);
       ++i) {
    m_piece_at_array[i] = { Piece_type::None, Color_type::None };
  }
}

Board::Board(const std::string_view& fen_string)
  : m_piece_at_array(parseFenString(fen_string))
{
  m_bitboards.fill(0ULL);
  Piece piece;
  for (int i = 0; i < 64; i++) {
    piece = m_piece_at_array[i];
    setBit(m_bitboards[pieceToIndex(piece)], i); 
  }
}

void
Board::printBoard() const
{
  for (int i = 56; i >= 0; i -= 8) {
    std::cout << (i + 1) / 8 + 1 << "  ";
    for (int j = 0; j < 8; j++) {
      std::cout << pieceToChar(m_piece_at_array[i + j]) << ' ';
    }
    std::cout << '\n';
  }
  std::cout << "\n   "
            << "a b c d e f g h\n";
}

void
Board::makeMove(const Move& move)
{
  const Square from = move.m_from; // d7
  const Square to = move.m_to;     // d5

  const Piece piece_at_from =
    m_piece_at_array[static_cast<int>(from)]; // Black Pawn
  const Piece piece_at_to = m_piece_at_array[static_cast<int>(to)]; // None

  if (piece_at_from.m_piece == Piece_type::None)
    throw std::invalid_argument("Not piece at that square to move\n");

  if (piece_at_from.m_color == piece_at_to.m_color)
    throw std::invalid_argument(
      "Piece cannot capture it's own color's piece\n");

  // Remove the piece from the from square
  // std::cout << static_cast<int>(from) << " " << static_cast<int>(to) << "\n";
  unsetBit(m_bitboards[indexOfPiece(piece_at_from)], static_cast<int>(from));
  // std::cout << "After unsetting the bit\n";
  // printBitBoard(m_bitboards[indexOfPiece(piece_at_from)]);
  setBit(m_bitboards[indexOfPiece(piece_at_from)], static_cast<int>(to));

  if (piece_at_to.m_piece != Piece_type::None) {
    unsetBit(m_bitboards[indexOfPiece(piece_at_to)], static_cast<size_t>(to));
  }

  m_piece_at_array[static_cast<int>(from)] = { Piece_type::None,
                                               Color_type::None };
  m_piece_at_array[static_cast<int>(to)] = piece_at_from;
}

Piece
Board::getPieceAtSquare(const Square& square) const
{
  return m_piece_at_array[static_cast<int>(square)];
}

BitBoard
Board::allWhitePiecesBitBoard() const
{
  return m_bitboards[WHITE_PAWN_IDX] | m_bitboards[WHITE_KNIGHT_IDX] |
         m_bitboards[WHITE_BISHOP_IDX] | m_bitboards[WHITE_ROOK_IDX] |
         m_bitboards[WHITE_QUEEN_IDX] | m_bitboards[WHITE_KING_IDX];
}

BitBoard
Board::allBlackPiecesBitBoard() const
{
  return m_bitboards[BLACK_PAWN_IDX] | m_bitboards[BLACK_KNIGHT_IDX] |
         m_bitboards[BLACK_BISHOP_IDX] | m_bitboards[BLACK_ROOK_IDX] |
         m_bitboards[BLACK_QUEEN_IDX] | m_bitboards[BLACK_KING_IDX];
}

BitBoard
Board::getBitBoard(const Piece& piece) const 
{
  return m_bitboards[indexOfPiece(piece)];
}

BitBoard
Board::allPiecesBitBoard() const
{
  return this->allBlackPiecesBitBoard() | this->allWhitePiecesBitBoard();
}




} // namespace Chess
