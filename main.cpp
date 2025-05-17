// Entry point for the application
#include "board/board.h"
#include "chess.h"
#include "square/square.h"
#include "utils/utils.h"
#include "validMoveGenerator/validMoveGenerator.h"

#include <iostream>

int main() {
  Chess::Board board;
  Chess::validMoveGenerator moveGen(board);
  board.makeMove({Chess::Square::e2, Chess::Square::e4});
  board.makeMove({Chess::Square::d7, Chess::Square::d5});
  Chess::BitBoard valid_moves = moveGen.bitboardOfValidMoves(Chess::Square::d5);
  Chess::printBitBoard(valid_moves);
  return 0;
}