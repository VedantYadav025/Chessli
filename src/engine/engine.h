#pragma once
#include "../board.h"
#include "engine.h"
#include "magic.h"

#include <vector>

namespace Chess {
class Engine {
public:
  Engine(Board &board);
  BitBoard whiteKingValid(const Square &sq) const;
  BitBoard blackKingValid(const Square &sq) const;
  BitBoard whiteKnightValid(const Square &sq) const;
  BitBoard blackKnightValid(const Square &sq) const;
  BitBoard whitePawnValid(const Square &sq) const;
  BitBoard blackPawnValid(const Square &sq) const;
  BitBoard whiteRookValid(const Square &sq) const;
  BitBoard blackRookValid(const Square &sq) const;
  BitBoard whiteBishopValid(const Square &sq) const;
  BitBoard blackBishopValid(const Square &sq) const;
  BitBoard whiteQueenValid(const Square &sq) const;
  BitBoard blackQueenValid(const Square &sq) const;
  BitBoard legalMoves(const Piece &piece, const Color &color,
                      const Square &sq) const;
  BitBoard allSquaresWhiteAttacks() const;  // usefull in checking if king is in check
  BitBoard allSquaresBlackAttacks() const;  // same

private:
  Board &board_;
  std::vector<std::vector<BitBoard>> rook_attacks_;
  std::vector<std::vector<BitBoard>> bishop_attacks_;
};
} // namespace Chess
