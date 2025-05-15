// Entry point for the application

#include "board/board.h"
#include "chess.h"
#include "square/square.h"
#include "utils/utils.h"
#include "validMoveGenerator/validMoveGenerator.h"

#include <iostream>


// void test() {
//   Chess::BitBoard bitboard = 0x00FF000000000000;
//   Chess::printBitBoard(bitboard);
//   Chess::unsetBit(bitboard, 51);
//   Chess::printBitBoard(bitboard);
// }

int main() {
  Chess::Board board; 
  Chess::validMoveGenerator moveGen(board);
  board.makeMove({Chess::Square::e2, Chess::Square::e4});
  board.makeMove({Chess::Square::d7, Chess::Square::d5});
  Chess::BitBoard valid_moves = moveGen.bitboardOfValidMoves(Chess::Square::d5);
  Chess::printBitBoard(valid_moves);
  return 0;
}
