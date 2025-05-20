#include <array>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <istream>
#include <string>
#include "utils/utils.h"

namespace Chess {

inline std::array<BitBoard, 64> getRookMagics() {
  std::ifstream file("rook_utils/rook_magics.txt");
  std::string line;
  std::array<BitBoard, 64> rook_magics;

  if (file.is_open()) {
    int i = 0;
    while (getline(file, line)) {
      rook_magics[i++] = std::stoull(line);
    }
  } else
    std::cout << "File is not open\n";
  return rook_magics;
}

inline std::array<BitBoard, 64> getBishopMagics() {
  std::ifstream file("bishop_utils/bishop_magics.txt");
  std::string line;
  std::array<BitBoard, 64> bishop_magics;

  if (file.is_open()) {
    int i = 0;
    while (getline(file, line)) {
      bishop_magics[i++] = std::stoull(line);
    }
  } else
    std::cout << "File is not open\n";
  return bishop_magics;
}

inline std::array<BitBoard, 64> getRookMasks() {
  std::ifstream file("rook_utils/rook_masks.txt");
  std::string line;
  std::array<BitBoard, 64> bishop_magics;

  if (file.is_open()) {
    int i = 0;
    while (getline(file, line)) {
      bishop_magics[i++] = std::stoull(line);
    }
  } else
    std::cout << "File is not open\n";
  return bishop_magics;
}

inline std::array<BitBoard, 64> getBishopMasks() {
  std::ifstream file("bishop_utils/bishop_masks.txt");
  std::string line;
  std::array<BitBoard, 64> bishop_magics;

  if (file.is_open()) {
    int i = 0;
    while (getline(file, line)) {
      bishop_magics[i++] = std::stoull(line);
    }
  } else
    std::cout << "File is not open\n";
  return bishop_magics;
}

inline std::array<BitBoard, 64> getRookRellevantBits() {
  std::ifstream file("rook_utils/rook_rellevant_bits.txt");
  std::string line;
  std::array<BitBoard, 64> bishop_magics;

  if (file.is_open()) {
    int i = 0;
    while (getline(file, line)) {
      bishop_magics[i++] = std::stoull(line);
    }
  } else
    std::cout << "File is not open\n";
  return bishop_magics;
}

inline std::array<BitBoard, 64> getBishopRellevantBits() {
  std::ifstream file("bishop_utils/bishop_rellevant_bits.txt");
  std::string line;
  std::array<BitBoard, 64> bishop_magics;

  if (file.is_open()) {
    int i = 0;
    while (getline(file, line)) {
      bishop_magics[i++] = std::stoull(line);
    }
  } else
    std::cout << "File is not open\n";
  return bishop_magics;
}

inline std::array<std::array<BitBoard, 4096>, 64> getRookAttacks() {
  std::ifstream file("rook_utils/rook_attacks.txt");
  std::string line;
  std::array<std::array<BitBoard, 4096>, 64> rook_attacks;

  if (file.is_open()) {
    for (int i = 0; i < 64; i++) {
      for (int j = 0; j < 4096; j++) {
        getline(file, line);
        rook_attacks[i][j] = std::stoull(line);
      }
    }
  }
  else 
    std::cout << "File is not open\n";
  return rook_attacks; 
}

inline std::array<std::array<BitBoard, 512>, 64> getBishopAttacks() {
  std::ifstream file("bishop_utils/bishop_attacks.txt");
  std::string line;
  std::array<std::array<BitBoard, 512>, 64> bishop_attacks;

  if (file.is_open()) {
    for (int i = 0; i < 64; i++) {
      for (int j = 0; j < 512; j++) {
        getline(file, line);
        bishop_attacks[i][j] = std::stoull(line);
      }
    }
  }
  else 
    std::cout << "File is not open\n";
  return bishop_attacks; 
}

}  // namespace Chess
