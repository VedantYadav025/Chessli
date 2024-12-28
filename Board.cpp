#include "Board.h"

void printU64(const BitBoard &bitboard) {
  // Loop through the bits in chunks of 8
  for (int i = 56; i >= 0; i -= 8) {
    // Print each chunk of 8 bits
    for (int j = 7; j >= 0; --j) {
      std::cout << ((bitboard >> (i + j)) & 1);
    }
    std::cout << std::endl;
  }
}

Board::Board()
    : white_can_castle_kingside(true), white_can_castle_queenside(true),
      black_can_castle_kingside(true), black_can_castle_queenside(true) {
  // Initialize bitboards for the standard chess starting position
  this->white_pawns_ = {{Color::White, Piece::Pawn}, 0x000000000000FF00ULL};
  this->white_rooks_ = {{Color::White, Piece::Rook}, 0x0000000000000081ULL};
  this->white_knights_ = {{Color::White, Piece::Knight}, 0x0000000000000042ULL};
  this->white_bishops_ = {{Color::White, Piece::Bishop}, 0x0000000000000024ULL};
  this->white_queens_ = {{Color::White, Piece::Queen}, 0x0000000000000008ULL};
  this->white_king_ = {{Color::White, Piece::King}, 0x0000000000000010ULL};

  this->black_pawns_ = {{Color::Black, Piece::Pawn}, 0x00FF000000000000ULL};
  this->black_rooks_ = {{Color::Black, Piece::Rook}, 0x8100000000000000ULL};
  this->black_knights_ = {{Color::Black, Piece::Knight}, 0x4200000000000000ULL};
  this->black_bishops_ = {{Color::Black, Piece::Bishop}, 0x2400000000000000ULL};
  this->black_queens_ = {{Color::Black, Piece::Queen}, 0x0800000000000000ULL};
  this->black_king_ = {{Color::Black, Piece::King}, 0x1000000000000000ULL};
}

BitBoard Board::allWhitePieces() const {
  return (this->white_pawns_.second | this->white_rooks_.second |
          this->white_knights_.second | this->white_bishops_.second | this->white_queens_.second |
          this->white_king_.second);
}

BitBoard Board::allBlackPieces() const {
    return (this->black_pawns_.second | this->black_rooks_.second | this->black_knights_.second | this->black_bishops_.second | this->black_queens_.second | this->black_king_.second);
}

BitBoard Board::allPieces() const {
    return (this->allWhitePieces() | this->allBlackPieces());
}

void Board::printBitBoard(const Piece &p, const Color &c) const {
    if (p == Piece::Pawn && c == Color::White)
        printU64(this->white_pawns_.second);
    else if (p == Piece::Pawn && c == Color::Black)
        printU64(this->black_pawns_.second);
    
}

void Board::printAllWhitePieces() const {
    const BitBoard value = this->allWhitePieces();
    printU64(value);
    return;
}

void Board::printAllBlackPieces() const {
    const BitBoard value = this->allBlackPieces();
    printU64(value);
    return;
}

void Board::printAllPieces() const {
    const BitBoard value = this->allPieces();
    printU64(value);
    return;
}