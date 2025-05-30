// Entry point for the application
#include "board/board.h"
#include "engine/engine.h"
#include "fen/fen.h"
#include "move/move.h"
#include "square/square.h"
#include "utils/utils.h"
#include "validMoveGenerator/validMoveGenerator.h"

#include <iostream>
#include <vector>

int
main()
{
  Chess::Board board(
    "rn2q3/pppp1ppp/1k6/2b5/3Q1P2/1B6/PPP2p1P/RN2K1NR w KQ - 0 1");
  Chess::Engine engine(board);
  Chess::validMoveGenerator move_gen(board);

  Chess::printBitBoard(move_gen.bitboardOfValidMoves(Chess::Square::f2));

  const std::vector<Chess::Move> legal_moves =
    engine.getLegalMoves(Chess::Square::e1);

  board.printBoard();
  // std::cout << "Here\n";
  for (const auto& move : legal_moves) {
    Chess::printMove(move);
  }

  return 0;
}
