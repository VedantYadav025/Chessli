#pragma once

#include "Board.h"
#include <array>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <utility>

Board::Board()
    : white_can_castle_kingside(true), white_can_castle_queenside(true),
      black_can_castle_kingside(true), black_can_castle_queenside(true) {
  // Initialize bitboards for the standard chess starting position
  this->white_pawns_ = {Color::White, Piece::Pawn, 0x000000000000FF00ULL};
  this->white_rooks_ = {Color::White, Piece::Rook, 0x0000000000000081ULL};
  this->white_knights_ = {Color::White, Piece::Knight, 0x0000000000000042ULL};
  this->white_bishops_ = {Color::White, Piece::Bishop, 0x0000000000000024ULL};
  this->white_king_ = {Color::White, Piece::Queen, 0x0000000000000008ULL};
  this->white_queens_ = {Color::White, Piece::King, 0x0000000000000010ULL};

  this->black_pawns_ = {Color::Black, Piece::Pawn, 0x00FF000000000000ULL};
  this->black_rooks_ = {Color::Black, Piece::Rook, 0x8100000000000000ULL};
  this->black_knights_ = {Color::Black, Piece::Knight, 0x4200000000000000ULL};
  this->black_bishops_ = {Color::Black, Piece::Bishop, 0x2400000000000000ULL};
  this->black_king_ = {Color::Black, Piece::Queen, 0x0800000000000000ULL};
  this->black_queens_ = {Color::Black, Piece::King, 0x1000000000000000ULL};


  std::vector<std::uint16_t> indexes;
  std::pair<std::uint16_t, std::uint16_t> pair_idx;

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      this->board_array_[i][j] = std::make_pair(Piece::None, Color::None);
    }
  }

  auto populateBoardArray = [&](const PieceInfo &piece_info, Piece piece,
                                Color color) {
    indexes = indexOfSquaresOccupied(piece_info);
    for (const std::uint16_t &idx : indexes) {
      pair_idx = indexOfSquare(static_cast<Square>(idx));
      this->board_array_[pair_idx.first][pair_idx.second] =
          std::make_pair(piece, color);
    }
  };

  populateBoardArray(this->white_pawns_, Piece::Pawn, Color::White);
  populateBoardArray(this->white_rooks_, Piece::Rook, Color::White);
  populateBoardArray(this->white_knights_, Piece::Knight, Color::White);
  populateBoardArray(this->white_bishops_, Piece::Bishop, Color::White);
  populateBoardArray(this->white_queens_, Piece::Queen, Color::White);
  populateBoardArray(this->white_king_, Piece::King, Color::White);

  populateBoardArray(this->black_pawns_, Piece::Pawn, Color::Black);
  populateBoardArray(this->black_rooks_, Piece::Rook, Color::Black);
  populateBoardArray(this->black_knights_, Piece::Knight, Color::Black);
  populateBoardArray(this->black_bishops_, Piece::Bishop, Color::Black);
  populateBoardArray(this->black_queens_, Piece::Queen, Color::Black);
  populateBoardArray(this->black_king_, Piece::King, Color::Black);
}

void Board::printBoard(const Color& point_of_view) const {
  switch (point_of_view) {
    case Color::Black:
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          std::cout << fenLetter(this->board_array_[i][j]) << ' ';
        }
        std::cout << '\n';
      }
    case Color::White:
      for (int i = 7; i >= 0; i--) {
        for (int j = 7; j >= 0; j--) {
          std::cout << fenLetter(this->board_array_[i][j]) << ' ';
        }
        std::cout << '\n';
      }
    case Color::None:
      std::cout << "Invalid Color\n";
  }
}

// Clearing the board (mainly for testing purposes)
void Board::clearBoard() {
  this->white_can_castle_kingside = true;
  this->white_can_castle_queenside = true;
  this->black_can_castle_kingside = true;
  this->black_can_castle_queenside = true;

  this->white_pawns_.bitboard_ = 0ULL;
  this->white_rooks_.bitboard_ = 0ULL;
  this->white_knights_.bitboard_ = 0ULL;
  this->white_bishops_.bitboard_ = 0ULL;
  this->white_queens_.bitboard_ = 0ULL;
  this->white_king_.bitboard_ = 0ULL;

  this->black_pawns_.bitboard_ = 0ULL;
  this->black_rooks_.bitboard_ = 0ULL;
  this->black_knights_.bitboard_ = 0ULL;
  this->black_bishops_.bitboard_ = 0ULL;
  this->black_queens_.bitboard_ = 0ULL;
  this->black_king_.bitboard_ = 0ULL;
}

// I am right now not too worried about whether that Square is already occupied
// by any Piece. I am just making this function to test my validMoves()
// functions. Will definetly complete this when needed Maybe not allow users to
// put piece on already occupied squares Will make a vacantSquare() function
void Board::setPieceOnSquare(const Piece &p, const Color &c, const Square &sq) {
  this->getPieceInfo(p, c).bitboard_ = bitboardOfSquare(sq);
}

// I think it's very needed to make a map

// Usefull BitBoards
BitBoard Board::allWhitePieces() const {
  return (this->white_pawns_.bitboard_ | this->white_rooks_.bitboard_ |
          this->white_knights_.bitboard_ | this->white_bishops_.bitboard_ |
          this->white_queens_.bitboard_ | this->white_king_.bitboard_);
}

BitBoard Board::allBlackPieces() const {
  return (this->black_pawns_.bitboard_ | this->black_rooks_.bitboard_ |
          this->black_knights_.bitboard_ | this->black_bishops_.bitboard_ |
          this->black_queens_.bitboard_ | this->black_king_.bitboard_);
}

BitBoard Board::allPieces() const {
  return (this->allWhitePieces() | this->allBlackPieces());
}

// Printing BitBoard in Chess-board format
void Board::printBitBoard(const Piece &p, const Color &c) const {
  if (p == Piece::Pawn && c == Color::White)
    printU64(this->white_pawns_.bitboard_);
  else if (p == Piece::Pawn && c == Color::Black)
    printU64(this->black_pawns_.bitboard_);
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

PieceInfo &Board::getPieceInfo(const Piece &p, const Color &c) {
  if (c == Color::White) {
    switch (p) {
    case Piece::Pawn:
      return this->white_pawns_;
    case Piece::Rook:
      return this->white_rooks_;
    case Piece::Knight:
      return this->white_knights_;
    case Piece::Bishop:
      return this->white_bishops_;
    case Piece::Queen:
      return this->white_queens_;
    case Piece::King:
      return this->white_king_;
    default:
      throw std::invalid_argument("Invalid piece");
    }
  } else if (c == Color::Black) {
    switch (p) {
    case Piece::Pawn:
      return this->black_pawns_;
    case Piece::Rook:
      return this->black_rooks_;
    case Piece::Knight:
      return this->black_knights_;
    case Piece::Bishop:
      return this->black_bishops_;
    case Piece::Queen:
      return this->black_queens_;
    case Piece::King:
      return this->black_king_;
    default:
      throw std::invalid_argument("Invalid piece");
    }
  } else {
    throw std::invalid_argument("Invalid color");
  }
}

// BitBoards representing Valid moves for each (Piece, Color)
// (https://pages.cs.wisc.edu/~psilord/blog/data/chess-pages/nonsliding.html)

// KingMoves(bit: i) --> (i >> 1, i << 1, i >> 8, i << 8, i >> 7, i >> 9, i <<
// 7, i << 9) (if in center) Issues arise when King is in File A and File H A:
// 1, 7 and 8 are out of bounds H: 3, 4 and 5 are out of bounds in spot_1,
// spot_2 and spot_8, AND with clearFile(A) as no these spots do not exist of
// King placed in A-file Similary, for H, clearFile(H) for spot 3, 4 and 5

BitBoard Board::whiteKingValid(const Square &sq) const {
  BitBoard king_bitboard = bitboardOfSquare(sq);
  BitBoard spot_1 = (king_bitboard & clearFile(0)) << 7; // Upper-left
  BitBoard spot_2 = king_bitboard << 8;                  // Upper
  BitBoard spot_3 = (king_bitboard & clearFile(7)) << 9; // Upper-right
  BitBoard spot_4 = (king_bitboard & clearFile(7)) << 1; // Right

  BitBoard spot_5 = (king_bitboard & clearFile(7)) >> 7; // Down-Right
  BitBoard spot_6 = king_bitboard >> 8;                  // Down
  BitBoard spot_7 = (king_bitboard & clearFile(0)) >> 9; // Down-Left
  BitBoard spot_8 = (king_bitboard & clearFile(0)) >> 1; // Left
  return (spot_1 | spot_2 | spot_3 | spot_4 | spot_5 | spot_6 | spot_7 |
          spot_8) &
         (~this->allWhitePieces());
}

BitBoard Board::blackKingValid(const Square &sq) const {
  BitBoard king_bitboard = bitboardOfSquare(sq);
  BitBoard spot_1 = (king_bitboard & clearFile(0)) << 7; // Upper-left
  BitBoard spot_2 = king_bitboard << 8;                  // Upper
  BitBoard spot_3 = (king_bitboard & clearFile(7)) << 9; // Upper-right
  BitBoard spot_4 = (king_bitboard & clearFile(7)) << 1; // Right

  BitBoard spot_5 = (king_bitboard & clearFile(7)) >> 7; // Down-Right
  BitBoard spot_6 = king_bitboard >> 8;                  // Down
  BitBoard spot_7 = (king_bitboard & clearFile(0)) >> 9; // Down-Left
  BitBoard spot_8 = (king_bitboard & clearFile(0)) >> 1; // Left
  return (spot_1 | spot_2 | spot_3 | spot_4 | spot_5 | spot_6 | spot_7 |
          spot_8) &
         (~this->allBlackPieces());
}

BitBoard Board::whiteKnightValid(const Square &sq) const {
  BitBoard knight_bitboard = bitboardOfSquare(sq);
  BitBoard spot_1 = (knight_bitboard & clearFile(0) & clearFile(1)) >> 6;
  BitBoard spot_2 = (knight_bitboard & clearFile(0)) << 15;
  BitBoard spot_3 = (knight_bitboard & clearFile(7)) << 17;
  BitBoard spot_4 = (knight_bitboard & clearFile(6) & clearFile(7)) << 10;

  BitBoard spot_5 = (knight_bitboard & clearFile(6) & clearFile(7)) >> 6;
  BitBoard spot_6 = (knight_bitboard & clearFile(7)) >> 15;
  BitBoard spot_7 = (knight_bitboard & clearFile(0)) >> 17;
  BitBoard spot_8 = (knight_bitboard & clearFile(0) & clearFile(1)) >> 10;

  return (spot_1 | spot_2 | spot_3 | spot_4 | spot_5 | spot_6 | spot_7 |
          spot_8) &
         ~this->allWhitePieces();
}

BitBoard Board::blackKnightValid(const Square &sq) const {
  BitBoard knight_bitboard = bitboardOfSquare(sq);
  BitBoard spot_1 = (knight_bitboard & clearFile(0) & clearFile(1)) >> 6;
  BitBoard spot_2 = (knight_bitboard & clearFile(0)) << 15;
  BitBoard spot_3 = (knight_bitboard & clearFile(7)) << 17;
  BitBoard spot_4 = (knight_bitboard & clearFile(6) & clearFile(7)) << 10;

  BitBoard spot_5 = (knight_bitboard & clearFile(6) & clearFile(7)) >> 6;
  BitBoard spot_6 = (knight_bitboard & clearFile(7)) >> 15;
  BitBoard spot_7 = (knight_bitboard & clearFile(0)) >> 17;
  BitBoard spot_8 = (knight_bitboard & clearFile(0) & clearFile(1)) >> 10;

  return (spot_1 | spot_2 | spot_3 | spot_4 | spot_5 | spot_6 | spot_7 |
          spot_8) &
         ~this->allBlackPieces();
}

// So, Pawns are intersting. They will exclusively be in one direction (for each
// color) and will have 2 moves, if rank == 2, shift by 1 and 2, otherwise,
// shift by 1 , these are as long as there is NO PIECE of any color in the
// square (in case of rank == 2, we have to see whether some piece is in way of
// the Pawn.)

BitBoard Board::whitePawnValid(const Square &sq) const {
  BitBoard pawn_bitboard = bitboardOfSquare(sq);
  std::int16_t rank_of_pawn = rank(sq);
  BitBoard state_1, state_2, state_3, state_4;
  if (rank_of_pawn == 2) {
    state_1 = (pawn_bitboard << 8) & (~this->allPieces());
    state_2 = ((pawn_bitboard & clearFile(0)) << 7) & this->allBlackPieces();
    state_3 = ((pawn_bitboard & clearFile(7)) << 9) & this->allBlackPieces();
    if (state_1 == 0)
      state_4 = 0;
    else
      state_4 = (pawn_bitboard << 16) & ~this->allPieces();
  } else if (rank_of_pawn != 7) {
    state_1 = (pawn_bitboard << 8) & (~this->allPieces());
    state_2 = ((pawn_bitboard & clearFile(0)) << 7) & this->allBlackPieces();
    state_3 = ((pawn_bitboard & clearFile(7)) << 9) & this->allBlackPieces();
  } else {
    ;
  }
  return state_1 | state_2 | state_3 | state_4;
}

BitBoard Board::blackPawnValid(const Square &sq) const {
  BitBoard pawn_bitboard = bitboardOfSquare(sq);
  std::int16_t rank_of_pawn = rank(sq);
  BitBoard state_1, state_2, state_3, state_4;
  if (rank_of_pawn == 7) {
    state_1 = (pawn_bitboard >> 8) & (~this->allPieces());
    state_2 = ((pawn_bitboard & clearFile(7)) >> 7) & this->allWhitePieces();
    state_3 = ((pawn_bitboard & clearFile(0)) >> 9) & this->allWhitePieces();
    if (state_1 == 0)
      state_4 = 0;
    else
      state_4 = (pawn_bitboard >> 16) & ~this->allPieces();
  } else if (rank_of_pawn != 0) {
    state_1 = (pawn_bitboard >> 8) & (~this->allPieces());
    state_2 = ((pawn_bitboard & clearFile(7)) >> 7) & this->allWhitePieces();
    state_3 = ((pawn_bitboard & clearFile(0)) >> 9) & this->allWhitePieces();
  } else {
    ;
  }
  return state_1 | state_2 | state_3 | state_4;
}

/*
  We will pretend that rook can capture all blockers,
  and remove friendly blockers later from that list.

  For that, we generate the list of squares on which
  blockers will be able to affect the moves of the rook.
*/

BitBoard Board::whiteRookValid(const Square &sq) const {
  std::int16_t rank_rook = rank(sq);
  std::int16_t file_rook = file(sq);
  BitBoard rook_attack_rays =
      (maskRank(rank_rook) | maskFile(file_rook)) & ~bitboardOfSquare(sq);
  // std::cout << blockers << std::endl;
  BitBoard blockers = clearBit(rook_attack_rays, 8 * rank_rook) &
                      clearBit(rook_attack_rays, 8 * (rank_rook + 1) - 1) &
                      clearBit(rook_attack_rays, file_rook) &
                      clearBit(rook_attack_rays, 56 + file_rook);
  return blockers;
}

BitBoard Board::whiteBishopValid(const Square &sq) const {
  std::int16_t rank_bishop = rank(sq);
  std::int16_t file_bishop = file(sq);
  return 0;
}

BitBoard Board::blackBishopValid(const Square &sq) const {
  std::int16_t rank_bishop = rank(sq);
  std::int16_t file_bishop = file(sq);
  return 0;
}
