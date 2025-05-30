// Entry point for the application
#include "board/board.h"
#include "fen/fen.h"
#include "square/square.h"
#include "utils/utils.h"
#include "validMoveGenerator/validMoveGenerator.h"

int
main()
{
  Chess::Board board("r1bk3r/p2pBpNp/n4n2/1p1NP2P/6P1/3P4/P1P1K3/q5b1 ");
  Chess::validMoveGenerator engine(board);
  board.printBoard();
  Chess::BitBoard attack = engine.bitboardOfValidMoves(Chess::Square::a1);
  Chess::printBitBoard(attack);
  return 0;
}
