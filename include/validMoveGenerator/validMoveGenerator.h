#include <array>
#include "../board/board.h"
#include "square/square.h"
#include "utils/utils.h"
#include "../magic/magic.h"

namespace Chess {

class validMoveGenerator {
 public:
  validMoveGenerator(const Board& board);
  BitBoard bitboardOfValidMoves(const Square& square) const;
  void printBoard() const;

 private:
  const Board& m_board;

  const std::array<BitBoard, 64>  rook_masks = getRookMasks();
  const std::array<BitBoard, 64> bishop_masks = getBishopMasks();

  const std::array<BitBoard, 64> rook_magics = getRookMagics();
  const std::array<BitBoard, 64> bishop_magics = getBishopMagics();

  const std::array<BitBoard, 64> rook_rellevant_bits = getRookRellevantBits();
  const std::array<BitBoard, 64> bishop_rellevant_bits = getBishopRellevantBits();

  const std::array<std::array<BitBoard, 4096>, 64> rook_attacks = getRookAttacks();
  const std::array<std::array<BitBoard, 512>, 64> bishop_attacks = getBishopAttacks();

  // direction sensitive piece move functions
 private:
  BitBoard whitePawnValidBitBoard(const Square& sq) const;
  BitBoard blackPawnValidBitBoard(const Square& sq) const;

  // direction agnostic piece move funcitons
 private:
  BitBoard kingValidBitBoard(const Square& square) const;
  BitBoard knightValidBitBoard(const Square& square) const;
  BitBoard rookValidBitBoard(const Square& square) const;
  BitBoard bishopValidBitBoard(const Square& square) const;
  BitBoard queenValidBitBoard(const Square& square) const;
};

}  // namespace Chess
