#include "fen/fen.h"
#include "pieces/pieces.h"
#include "utils/utils.h"

#include <array>
#include <iostream>
#include <stdexcept>
#include <string_view>

bool
isValidLetter(const char& ch)
{
  return (ch == 'r' || ch == 'b' || ch == 'n' || ch == 'k' || ch == 'q' ||
          ch == 'p' || ch == 'R' || ch == 'N' || ch == 'B' || ch == 'Q' ||
          ch == 'K' || ch == 'P');
}

// void print(const std::array<Chess::Piece, 64> arr) 
// {
//   for (int i = 56; i >= 0; i -= 8) {
//     for (int j = 0; j < 8; j++) {
//       std::cout << Chess::pieceToChar(arr[i + j]) << ' ';
//     }
//     std::cout << '\n';
//   }
//   return;
// }

std::array<Chess::Piece, 64>
parseFenString(const std::string_view& fen_string)
{
  std::array<Chess::Piece, 64> board_arr;
  board_arr.fill({Chess::Piece_type::None, Chess::Color_type::None});
  // print(board_arr);
  int idx = 56;
  for (const char& ch : fen_string) {
    // std::cout << ch << std::endl;
    if (ch == ' ')
      break;

    if (isValidLetter(ch)) {
      board_arr[idx++] = Chess::charToPiece[ch]; // idx is updated after the
                                                 // statement is executed
    } else if (ch <= '8' && ch >= '1') {
      int num = ch - '0';
      while (num--)
        board_arr[idx++] = { Chess::Piece_type::None, Chess::Color_type::None };
    } else if (ch == '/')
      idx -= 16;
    else
      throw std::invalid_argument("FEN string is not valid");

    // print(board_arr);
  }
  return board_arr;
}
// "r1bk3r/p2pBpNp/n4n2/1p1NP2P/6P1/3P4/P1P1K3/q5b1 "
