#include "engine/engine.h"
#include "board/board.h"
#include "pieces/pieces.h"
#include "square/square.h"
#include "utils/utils.h"
#include "validMoveGenerator/validMoveGenerator.h"
#include <iostream>
#include <vector>

// how to get legal moves from valid moves
// see if king is not in check

// if king move, see if it does not go to any square attacked by the opposing
// square if not a king move, the only way to get checked is by moving a pinned
// piece for castling, we'll have to work some extra (basically, no square b/w
// king and rook should be under attack)

namespace Chess {

Engine::Engine(const Board& board)
  : m_board(board)
{
}

std::vector<Move>
Engine::getLegalMoves(const Square& square) const
{
  std::vector<Move> legal_moves;
  BitBoard valid_moves =
    validMoveGenerator(m_board).bitboardOfValidMoves(square);
  const Piece piece = m_board.getPieceAtSquare(square);

  if (piece.m_piece == Piece_type::King) {
    if (piece.m_color == Color_type::White) {
      // std::cout << "Here\n";
      valid_moves &= ~this->allBlackValidAttacks(); // this is the problem
    } else {
      valid_moves &= ~this->allWhiteValidAttacks();
    }
  }

  while (valid_moves) {
    int idx = __builtin_ctzll(valid_moves);
    legal_moves.push_back({ square, static_cast<Square>(idx) });
    valid_moves &= valid_moves - 1;
  }
  return legal_moves;
}

BitBoard
Engine::allWhiteValidAttacks() const
{
  validMoveGenerator move_gen(m_board);
  std::vector<Square> squaresOfWhites;
  BitBoard whites = m_board.allWhitePiecesBitBoard(); // copy, so can be edited
  while (whites) {
    int idx = __builtin_ctzll(whites);
    squaresOfWhites.push_back(static_cast<Square>(idx));
    whites &= whites - 1;
  }
  BitBoard white_valids = 0ULL;
  for (const Square& sq : squaresOfWhites) {
    if (m_board.getPieceAtSquare(sq).m_piece != Piece_type::Pawn)
      white_valids |= move_gen.bitboardOfValidMoves(sq);
    else 
      white_valids |= move_gen.getPawnAttacks(sq);
  }
  return white_valids;
}

BitBoard
Engine::allBlackValidAttacks() const
{
  validMoveGenerator move_gen(m_board);
  std::vector<Square> squaresOfWhites;
  BitBoard blacks = m_board.allBlackPiecesBitBoard(); // copy, so can be edited
  while (blacks) {
    int idx = __builtin_ctzll(blacks);
    squaresOfWhites.push_back(static_cast<Square>(idx));
    blacks &= blacks- 1;
  }
  // std::cout << "Here\n";
  BitBoard black_valids = 0ULL;
  for (const Square& sq : squaresOfWhites) {
    if (m_board.getPieceAtSquare(sq).m_piece != Piece_type::Pawn)
      black_valids |= move_gen.bitboardOfValidMoves(sq);
    else 
      black_valids |= move_gen.getPawnAttacks(sq);
  }
  return black_valids;
}

bool
Engine::isKingInCheck(const Color_type& color) const
{
  if (color == Color_type::White) {
    BitBoard black_attacks = this->allBlackValidAttacks();
    return (((black_attacks & m_board.getBitBoard(
                                { Piece_type::King, Color_type::White })) == 0)
              ? false
              : true);
  } else if (color == Color_type::Black) {

    BitBoard white_attacks = this->allWhiteValidAttacks();
    return (((white_attacks & m_board.getBitBoard(
                                { Piece_type::King, Color_type::Black })) == 0)
              ? false
              : true);
  } else {
    throw std::invalid_argument("None is not a valid color for any King\n");
  }
  return false;
}

}