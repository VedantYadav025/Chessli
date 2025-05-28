#include "fen/fen.h"
#include "pieces/pieces.h"
#include <array>
#include <stdexcept>

bool isValidLetter(const char& ch) {
  return (ch == 'r' || ch == 'b' || ch == 'n' || ch == 'k' || ch == 'q' || ch =='p' || ch == 'R' || ch == 'N' || ch == 'B' || ch == 'Q' || ch == 'K' || ch == 'P');
}

std::array<Chess::Piece, 64>
parseFenString(const std::string_view& fen_string) 
{
  std::array<Chess::Piece, 64> board_rep{};
  for (const auto &ch: fen_string) {
    if (ch <= '8' && ch >= '1') {
	 
    }
		else if (isValidLetter(ch)) {
    
    }
    else
      throw std::invalid_argument("Invalid FEN string");
  }
  return board_rep; 
}

