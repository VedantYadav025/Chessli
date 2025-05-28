#pragma once

#include "../board/board.h"
#include "square/square.h"
#include "utils/utils.h"

namespace Chess {

class validMoveGenerator {
 public:
  explicit validMoveGenerator(const Board& board);
  [[nodiscard]] BitBoard bitboardOfValidMoves(const Square& square) const;
  void printBoard() const;

 private:
  const Board& m_board;
  // direction sensitive piece move functions

 private:
  [[nodiscard]] BitBoard whitePawnValidBitBoard(const Square& sq) const;
  [[nodiscard]] BitBoard blackPawnValidBitBoard(const Square& sq) const;

  // direction agnostic piece move  functions
 private:
  [[nodiscard]] static BitBoard kingValidBitBoard(const Square& square);
  [[nodiscard]] static BitBoard knightValidBitBoard(const Square& square);
  [[nodiscard]] BitBoard rookValidBitBoard(const Square& square) const;
  [[nodiscard]] BitBoard bishopValidBitBoard(const Square& square) const;
  [[nodiscard]] static BitBoard queenValidBitBoard(const Square& square);
};

}  // namespace Chess
