#include "validMoveGenerator/validMoveGenerator.h"
#include <iostream>
#include "board/board.h"
#include "pieces/pieces.h"
#include "utils/utils.h"

namespace Chess {

// public functions

validMoveGenerator::validMoveGenerator(const Board& board) : m_board(board) {}

BitBoard validMoveGenerator::bitboardOfValidMoves(const Square& square) const {
  Piece piece_at_square = m_board.getPieceAtSquare(square);
  switch (piece_at_square.m_piece) {
    case (Piece_type::King):
      return ((piece_at_square.m_color == Color_type::White)
                  ? this->kingValidBitBoard(square) &
                        ~m_board.allWhitePiecesBitBoard()
                  : this->kingValidBitBoard(square) &
                        ~m_board.allBlackPiecesBitBoard());
    case (Piece_type::Knight):
      return ((piece_at_square.m_color == Color_type::White)
                  ? this->knightValidBitBoard(square) &
                        ~m_board.allWhitePiecesBitBoard()
                  : this->knightValidBitBoard(square) &
                        ~m_board.allBlackPiecesBitBoard());
    case (Piece_type::Pawn):
      return ((piece_at_square.m_color == Color_type::White)
                  ? this->whitePawnValid(square) 
                  : this->blackPawnValid(square));
  }
}

void validMoveGenerator::printBoard() const {
  m_board.printBoard();
  return;
}

// private functions

BitBoard validMoveGenerator::kingValidBitBoard(const Square& square) const {
  BitBoard king_loc = 1ULL << static_cast<int>(square);
  BitBoard king_clip_file_h = king_loc & clear_file[7];
  BitBoard king_clip_file_a = king_loc & clear_file[0];

  BitBoard spot_1 = king_clip_file_h << 7;
  BitBoard spot_2 = king_loc << 8;
  BitBoard spot_3 = king_clip_file_h << 9;
  BitBoard spot_4 = king_clip_file_h << 1;

  BitBoard spot_5 = king_clip_file_h >> 7;
  BitBoard spot_6 = king_loc >> 8;
  BitBoard spot_7 = king_clip_file_a >> 9;
  BitBoard spot_8 = king_clip_file_a >> 1;

  BitBoard king_moves =
      spot_1 | spot_2 | spot_3 | spot_4 | spot_5 | spot_6 | spot_7 | spot_8;
  return king_moves;
}

BitBoard validMoveGenerator::knightValidBitBoard(const Square& square) const {
  BitBoard knight_loc = 1ULL << static_cast<int>(square);

  BitBoard spot_1_clip = clear_file[0] & clear_file[1];
  BitBoard spot_2_clip = clear_file[0];
  BitBoard spot_3_clip = clear_file[7];
  BitBoard spot_4_clip = clear_file[7] & clear_file[6];

  BitBoard spot_5_clip = clear_file[7] & clear_file[6];
  BitBoard spot_6_clip = clear_file[7];
  BitBoard spot_7_clip = clear_file[0];
  BitBoard spot_8_clip = clear_file[0] & clear_file[1];

  BitBoard spot_1 = (knight_loc & spot_1_clip) << 6;
  BitBoard spot_2 = (knight_loc & spot_2_clip) << 15;
  BitBoard spot_3 = (knight_loc & spot_3_clip) << 17;
  BitBoard spot_4 = (knight_loc & spot_4_clip) << 10;

  BitBoard spot_5 = (knight_loc & spot_5_clip) >> 6;
  BitBoard spot_6 = (knight_loc & spot_6_clip) >> 15;
  BitBoard spot_7 = (knight_loc & spot_7_clip) >> 17;
  BitBoard spot_8 = (knight_loc & spot_8_clip) >> 10;

  return spot_1 | spot_2 | spot_3 | spot_4 | spot_5 | spot_6 | spot_7 | spot_8;
}

BitBoard validMoveGenerator::whitePawnValid(const Square& square) const {
  BitBoard white_pawn_loc = 1ULL << static_cast<int>(square);

  /* check the single space infront of the white pawn */
  BitBoard white_pawn_one_step =
      (white_pawn_loc << 8) & ~m_board.allPiecesBitBoard();

  /* for all moves that came from rank 2 (home row) and passed the above
   *    filter, thereby being on rank 3, check and see if I can move forward
   *        one more */
  BitBoard white_pawn_two_steps = ((white_pawn_one_step & mask_rank[2]) << 8) &
                                  ~m_board.allPiecesBitBoard();


  /* the union of the movements dictate the possible moves forward
   *    available */
  BitBoard white_pawn_valid_moves = white_pawn_one_step | white_pawn_two_steps;

  /* next we calculate the pawn attacks */

  /* check the left side of the pawn, minding the underflow File A */
  BitBoard white_pawn_left_attack = (white_pawn_loc & clear_file[0]) << 7;

  /* then check the right side of the pawn, minding the overflow File H */
  BitBoard white_pawn_right_attack = (white_pawn_loc & clear_file[7]) << 9;

  /* the union of the left and right attacks together make up all the
   *    possible attacks */
  BitBoard white_pawn_attacks =
      white_pawn_left_attack | white_pawn_right_attack;

  // printBitBoard(white_pawn_attacks);

  /* Calculate where I can _actually_ attack something */
  BitBoard white_pawn_valid_attacks =
      white_pawn_attacks & m_board.allBlackPiecesBitBoard();

  printBitBoard(m_board.allBlackPiecesBitBoard());
  // printBitBoard(white_pawn_valid_attacks);

  /* then we combine the two situations in which a white pawn can legally
   *    attack/move. */
  BitBoard WhitePawnValid = white_pawn_valid_moves | white_pawn_valid_attacks;

  return WhitePawnValid;
}

BitBoard validMoveGenerator::blackPawnValid(const Square& square) const {
  BitBoard black_pawn_loc = 1ULL << static_cast<int>(square);

  /* check the single space infront of the black pawn */
  BitBoard black_pawn_one_step =
      (black_pawn_loc >> 8) & ~m_board.allPiecesBitBoard();

  /* for all moves that came from rank 7 (home row) and passed the above
   *    filter, thereby being on rank 6, check and see if I can move forward
   *        one more */
  BitBoard black_pawn_two_steps = ((black_pawn_one_step & mask_rank[5]) >> 8) &
                                  ~m_board.allPiecesBitBoard();

  /* the union of the movements dictate the possible moves forward
   *    available */
  BitBoard black_pawn_valid_moves = black_pawn_one_step | black_pawn_two_steps;

  /* next we calculate the pawn attacks */

  /* check the left side of the pawn, minding the underflow File A */
  BitBoard black_pawn_left_attack = (black_pawn_loc & clear_file[0]) >> 9;

  /* then check the right side of the pawn, minding the overflow File H */
  BitBoard black_pawn_right_attack = (black_pawn_loc & clear_file[7]) >> 7;

  /* the union of the left and right attacks together make up all the
   *    possible attacks */
  BitBoard black_pawn_attacks =
      black_pawn_left_attack | black_pawn_right_attack;

  /* Calculate where I can _actually_ attack something */
  BitBoard black_pawn_valid_attacks =
      black_pawn_attacks & m_board.allWhitePiecesBitBoard();

  /* then we combine the two situations in which a white pawn can legally
   *    attack/move. */
  BitBoard BlackPawnValid = black_pawn_valid_moves | black_pawn_valid_attacks;

  return BlackPawnValid;
}

}  // namespace Chess

