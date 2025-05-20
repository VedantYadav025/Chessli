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
  board.makeMove({Chess::Square::a2, Chess::Square::a4});
  board.printBoard();
  Chess::BitBoard blah = moveGen.bitboardOfValidMoves(Chess::Square::a1);
  Chess::printBitBoard(blah);
  return 0;
}
