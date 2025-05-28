#pragma once

#include "utils/utils.h"

#include <iostream>

namespace Chess {

void
printBitBoard(const BitBoard& bitboard)
{
  for (int i = 56; i >= 0; i -= 8) {
    std::cout << i / 8 + 1 << "| ";
    for (int j = 0; j < 8; j++) {
      std::cout << ((bitboard & (1ULL << (i + j))) ? '1' : '0') << ' ';
    }
    std::cout << std::endl;
  }
  std::cout << "\n  "
            << " a b c d e f g h\n";
}

}
