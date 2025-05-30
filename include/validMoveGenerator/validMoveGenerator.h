#pragma once

#include "../board/board.h"
#include "square/square.h"
#include "utils/utils.h"

namespace Chess {

class validMoveGenerator
{
public:
  explicit validMoveGenerator(const Board& board);
  [[nodiscard]] BitBoard bitboardOfValidMoves(const Square& square) const;
  void printBoard() const;
  BitBoard getPawnAttacks(const Square& square) const;

private:
  const Board& m_board;

private:
  // direction sensitive piece move functions
  [[nodiscard]] BitBoard whitePawnValidBitBoard(const Square& sq) const;
  [[nodiscard]] BitBoard blackPawnValidBitBoard(const Square& sq) const;

  // direction agnostic piece move  functions
private:
  [[nodiscard]] static BitBoard kingValidBitBoard(const Square& square);
  [[nodiscard]] static BitBoard knightValidBitBoard(const Square& square);
  [[nodiscard]] BitBoard rookValidBitBoard(const Square& square) const;
  [[nodiscard]] BitBoard bishopValidBitBoard(const Square& square) const;
  [[nodiscard]] BitBoard queenValidBitBoard(const Square& square) const;
};

} // namespace Chess
