#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include "utils/utils.h"

namespace Chess {

inline std::array<BitBoard, 64> getRookMagics() {
  std::ifstream file("rook_magics.txt");
  std::array<BitBoard, 64> rook_magics;
  std::string line;
  for (int i = 0; i < 64; i++) {
    std::getline(file, line);
    rook_magics[i] = std::stoull(line);
  }
  return rook_magics;
}

inline std::array<BitBoard, 64> getBishopMagics() {
  std::ifstream file("bishop_magics.txt");
  std::array
}

}  // namespace Chess
