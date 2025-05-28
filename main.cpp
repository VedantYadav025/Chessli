// Entry point for the application
#include "board/board.h"
#include "square/square.h"
#include "utils/utils.h"
#include "validMoveGenerator/validMoveGenerator.h"

int
main()
{
  Chess::Board board;
  const Chess::validMoveGenerator moveGen(board);
  board.makeMove({ Chess::Square::b2, Chess::Square::b3 });
  board.printBoard();
  const Chess::BitBoard bitboard =
    moveGen.bitboardOfValidMoves(Chess::Square::c1);
  Chess::printBitBoard(bitboard);
  return 0;
}
