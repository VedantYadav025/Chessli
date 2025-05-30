#include "validMoveGenerator/validMoveGenerator.h"
#include "board/board.h"
#include "magic/magic.h"
#include "pieces/pieces.h"
#include "square/square.h"
#include "utils/utils.h"
#include <stdexcept>

namespace Chess {

// public functions

validMoveGenerator::validMoveGenerator(const Board& board)
  : m_board(board)
{
}

BitBoard
validMoveGenerator::bitboardOfValidMoves(const Square& square) const
{
  switch (auto [m_piece, m_color] = m_board.getPieceAtSquare(square); m_piece) {
    case (Piece_type::King):
      return ((m_color == Color_type::White)
                ? this->kingValidBitBoard(square) &
                    ~m_board.allWhitePiecesBitBoard()
                : this->kingValidBitBoard(square) &
                    ~m_board.allBlackPiecesBitBoard());
    case (Piece_type::Knight):
      return ((m_color == Color_type::White)
                ? this->knightValidBitBoard(square) &
                    ~m_board.allWhitePiecesBitBoard()
                : this->knightValidBitBoard(square) &
                    ~m_board.allBlackPiecesBitBoard());
    case (Piece_type::Pawn):
      return ((m_color == Color_type::White)
                ? this->whitePawnValidBitBoard(square)
                : this->blackPawnValidBitBoard(square));
    case (Piece_type::Rook):
      return ((m_color == Color_type::White)
                ? this->rookValidBitBoard(square) &
                    ~m_board.allWhitePiecesBitBoard()
                : this->rookValidBitBoard(square) &
                    ~m_board.allBlackPiecesBitBoard());
    case (Piece_type::Bishop):
      return ((m_color == Color_type::White)
                ? this->bishopValidBitBoard(square) &
                    ~m_board.allWhitePiecesBitBoard()
                : this->bishopValidBitBoard(square) &
                    ~m_board.allBlackPiecesBitBoard());

    case (Piece_type::Queen):
      return ((m_color == Color_type::White)
                ? this->queenValidBitBoard(square) &
                    ~m_board.allWhitePiecesBitBoard()
                : this->queenValidBitBoard(square) &
                    ~m_board.allBlackPiecesBitBoard());
    default:;
  }
  throw std::invalid_argument("Not a valid piece at this square");
}

void
validMoveGenerator::printBoard() const
{
  m_board.printBoard();
}

// private functions

BitBoard
validMoveGenerator::kingValidBitBoard(const Square& square)
{
  const BitBoard king_loc = 1ULL << static_cast<int>(square);
  const BitBoard king_clip_file_h = king_loc & clear_file[7];
  const BitBoard king_clip_file_a = king_loc & clear_file[0];

  const BitBoard spot_1 = king_clip_file_h << 7;
  const BitBoard spot_2 = king_loc << 8;
  const BitBoard spot_3 = king_clip_file_h << 9;
  const BitBoard spot_4 = king_clip_file_h << 1;

  const BitBoard spot_5 = king_clip_file_h >> 7;
  const BitBoard spot_6 = king_loc >> 8;
  const BitBoard spot_7 = king_clip_file_a >> 9;
  const BitBoard spot_8 = king_clip_file_a >> 1;

  const BitBoard king_moves =
    spot_1 | spot_2 | spot_3 | spot_4 | spot_5 | spot_6 | spot_7 | spot_8;
  return king_moves;
}

BitBoard
validMoveGenerator::knightValidBitBoard(const Square& square)
{
  const BitBoard knight_loc = 1ULL << static_cast<int>(square);

  constexpr BitBoard spot_1_clip = clear_file[0] & clear_file[1];
  constexpr BitBoard spot_2_clip = clear_file[0];
  constexpr BitBoard spot_3_clip = clear_file[7];
  constexpr BitBoard spot_4_clip = clear_file[7] & clear_file[6];

  constexpr BitBoard spot_5_clip = clear_file[7] & clear_file[6];
  constexpr BitBoard spot_6_clip = clear_file[7];
  constexpr BitBoard spot_7_clip = clear_file[0];
  constexpr BitBoard spot_8_clip = clear_file[0] & clear_file[1];

  const BitBoard spot_1 = (knight_loc & spot_1_clip) << 6;
  const BitBoard spot_2 = (knight_loc & spot_2_clip) << 15;
  const BitBoard spot_3 = (knight_loc & spot_3_clip) << 17;
  const BitBoard spot_4 = (knight_loc & spot_4_clip) << 10;

  const BitBoard spot_5 = (knight_loc & spot_5_clip) >> 6;
  const BitBoard spot_6 = (knight_loc & spot_6_clip) >> 15;
  const BitBoard spot_7 = (knight_loc & spot_7_clip) >> 17;
  const BitBoard spot_8 = (knight_loc & spot_8_clip) >> 10;

  return spot_1 | spot_2 | spot_3 | spot_4 | spot_5 | spot_6 | spot_7 | spot_8;
}

BitBoard
validMoveGenerator::whitePawnValidBitBoard(const Square& sq) const
{
  const BitBoard white_pawn_loc = 1ULL << static_cast<int>(sq);

  /* check the single space infront of the white pawn */
  const BitBoard white_pawn_one_step =
    (white_pawn_loc << 8) & ~m_board.allPiecesBitBoard();

  /* for all moves that came from rank 2 (home row) and passed the above
   *    filter, thereby being on rank 3, check and see if I can move forward
   *        one more */
  const BitBoard white_pawn_two_steps =
    ((white_pawn_one_step & mask_rank[2]) << 8) & ~m_board.allPiecesBitBoard();

  /* the union of the movements dictate the possible moves forward
   *    available */
  const BitBoard white_pawn_valid_moves =
    white_pawn_one_step | white_pawn_two_steps;

  /* next we calculate the pawn attacks */

  /* check the left side of the pawn, minding the underflow File A */
  const BitBoard white_pawn_left_attack = (white_pawn_loc & clear_file[0]) << 7;

  /* then check the right side of the pawn, minding the overflow File H */
  const BitBoard white_pawn_right_attack = (white_pawn_loc & clear_file[7])
                                           << 9;

  /* the union of the left and right attacks together make up all the
   *    possible attacks */
  const BitBoard white_pawn_attacks =
    white_pawn_left_attack | white_pawn_right_attack;

  // printBitBoard(white_pawn_attacks);

  /* Calculate where I can _actually_ attack something */
  const BitBoard white_pawn_valid_attacks =
    white_pawn_attacks & m_board.allBlackPiecesBitBoard();

  // printBitBoard(m_board.allBlackPiecesBitBoard());
  // printBitBoard(white_pawn_valid_attacks);

  /* then we combine the two situations in which a white pawn can legally
   *    attack/move. */
  const BitBoard WhitePawnValid =
    white_pawn_valid_moves | white_pawn_valid_attacks;

  return WhitePawnValid;
}

BitBoard
validMoveGenerator::blackPawnValidBitBoard(const Square& sq) const
{
  const BitBoard black_pawn_loc = 1ULL << static_cast<int>(sq);

  /* check the single space in front of the black pawn */
  const BitBoard black_pawn_one_step =
    (black_pawn_loc >> 8) & ~m_board.allPiecesBitBoard();

  /* for all moves that came from rank 7 (home row) and passed the above
   *    filter, thereby being on rank 6, check and see if I can move forward
   *        one more */
  const BitBoard black_pawn_two_steps =
    ((black_pawn_one_step & mask_rank[5]) >> 8) & ~m_board.allPiecesBitBoard();

  /* the union of the movements dictate the possible moves forward
   *    available */
  const BitBoard black_pawn_valid_moves =
    black_pawn_one_step | black_pawn_two_steps;

  /* next we calculate the pawn attacks */

  /* check the left side of the pawn, minding the underflow File A */
  const BitBoard black_pawn_left_attack = (black_pawn_loc & clear_file[0]) >> 9;

  /* then check the right side of the pawn, minding the overflow File H */
  const BitBoard black_pawn_right_attack =
    (black_pawn_loc & clear_file[7]) >> 7;

  /* the union of the left and right attacks together make up all the
   *    possible attacks */
  const BitBoard black_pawn_attacks =
    black_pawn_left_attack | black_pawn_right_attack;

  /* Calculate where I can _actually_ attack something */
  const BitBoard black_pawn_valid_attacks =
    black_pawn_attacks & m_board.allWhitePiecesBitBoard();

  /* then we combine the two situations in which a white pawn can legally
   *    attack/move. */
  const BitBoard BlackPawnValid =
    black_pawn_valid_moves | black_pawn_valid_attacks;

  return BlackPawnValid;
}

BitBoard
validMoveGenerator::rookValidBitBoard(const Square& square) const
{
  BitBoard occupancy = m_board.allPiecesBitBoard();
  unsetBit(occupancy, static_cast<int>(square));
  occupancy &= Magic::rook_masks[static_cast<int>(square)];
  occupancy *= Magic::rook_magics[static_cast<int>(square)];
  occupancy >>= 64 - Magic::rook_relevant_bits[static_cast<int>(square)];

  // printBitBoard(Magic::rook_relevant_bits[static_cast<int>(square)]);
  return Magic::rook_attacks[static_cast<int>(square)][occupancy];
}

BitBoard
validMoveGenerator::bishopValidBitBoard(const Square& square) const
{
  BitBoard occupancy = m_board.allPiecesBitBoard();
  unsetBit(occupancy, static_cast<int>(square));

  occupancy &= Magic::bishop_masks[static_cast<int>(square)];
  occupancy *= Magic::bishop_magics[static_cast<int>(square)];
  occupancy >>= 64 - Magic::bishop_relevant_bits[static_cast<int>(square)];
  // printBitBoard(Magic::rook_relevant_bits[static_cast<int>(square)]);
  // printBitBoard(Magic::bishop_attacks[static_cast<int>(square)][occupancy]);

  // printBitBoard(Magic::rook_relevant_bits[static_cast<int>(square)]);
  return Magic::bishop_attacks[static_cast<int>(square)][occupancy];
}

BitBoard
validMoveGenerator::queenValidBitBoard(const Square& square) const
{
  return this->rookValidBitBoard(square) | this->bishopValidBitBoard(square);
}

} // namespace Chess
