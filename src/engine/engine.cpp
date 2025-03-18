#include "engine.h"

namespace Chess
{
	Engine::Engine(Board& board) : board_(board) {
		rook_attacks_ = initRookAttack();
		bishop_attacks_ = initBishopAttack();
	}

	BitBoard Engine::whiteKingValid(const Square& sq) const
	{
		// Ignoring checks
		BitBoard white_king = 1ULL << static_cast<int>(sq);
		BitBoard king_clip_file_h = white_king & clear_file[7];
		BitBoard king_clip_file_a = white_king & clear_file[0];
		BitBoard spot_1 = king_clip_file_h << 7;
		BitBoard spot_2 = white_king << 8;
		BitBoard spot_3 = king_clip_file_h << 9;
		BitBoard spot_4 = king_clip_file_h << 1;

		BitBoard spot_5 = king_clip_file_a >> 7;
		BitBoard spot_6 = white_king >> 8;
		BitBoard spot_7 = king_clip_file_a >> 9;
		BitBoard spot_8 = king_clip_file_a >> 1;
		return (spot_1 | spot_2 | spot_3 | spot_4 | spot_5 | spot_6 | spot_7 |
			spot_8) &
			(~this->board_.allWhitePieces());
	}

	BitBoard Engine::blackKingValid(const Square& sq) const
	{
		// Ignoring checks
		BitBoard black_king = 1ULL << static_cast<int>(sq);
		BitBoard king_clip_file_h = black_king & clear_file[7];
		BitBoard king_clip_file_a = black_king & clear_file[0];
		BitBoard spot_1 = king_clip_file_h << 7;
		BitBoard spot_2 = black_king << 8;
		BitBoard spot_3 = king_clip_file_h << 9;
		BitBoard spot_4 = king_clip_file_h << 1;

		BitBoard spot_5 = king_clip_file_a >> 7;
		BitBoard spot_6 = black_king >> 8;
		BitBoard spot_7 = king_clip_file_a >> 9;
		BitBoard spot_8 = king_clip_file_a >> 1;
		return (spot_1 | spot_2 | spot_3 | spot_4 | spot_5 | spot_6 | spot_7 |
			spot_8) &
			(~this->board_.allBlackPieces());
	}

	BitBoard Engine::whiteKnightValid(const Square& sq) const {
		/* we can ignore the rank clipping since the overflow/underflow with
		respect to rank simply vanishes. We only care about the file
		overflow/underflow which is much more work for a knight. */

		BitBoard knight_loc = 1ULL << static_cast<int>(sq);
		BitBoard spot_1_clip = clear_file[0] & clear_file[1];
		BitBoard spot_2_clip = clear_file[0];
		BitBoard spot_3_clip = clear_file[7];
		BitBoard spot_4_clip = clear_file[7] & clear_file[6];

		/* The clipping masks we just created will be used to ensure that no
		under or overflow positions are computed when calculating the
		possible moves of the knight in certain files. */

		BitBoard spot_1 = (knight_loc & spot_1_clip) << 6;
		BitBoard spot_2 = (knight_loc & spot_2_clip) << 15;
		BitBoard spot_3 = (knight_loc & spot_3_clip) << 17;
		BitBoard spot_4 = (knight_loc & spot_4_clip) << 10;

		BitBoard spot_5_clip = clear_file[7] & clear_file[6];
		BitBoard spot_6_clip = clear_file[7];
		BitBoard spot_7_clip = clear_file[0];
		BitBoard spot_8_clip = clear_file[0] & clear_file[1];

		BitBoard spot_5 = (knight_loc & spot_5_clip) >> 6;
		BitBoard spot_6 = (knight_loc & spot_6_clip) >> 15;
		BitBoard spot_7 = (knight_loc & spot_7_clip) >> 17;
		BitBoard spot_8 = (knight_loc & spot_8_clip) >> 10;

		BitBoard KnightValid =
			spot_1 | spot_2 | spot_3 | spot_4 | spot_5 | spot_6 | spot_7 | spot_8;

		/* compute only the places where the knight can move and attack. The
		caller will determine if this is a white or black night. */
		return (KnightValid & (~this->board_.allWhitePieces()));
	}

	BitBoard Engine::blackKnightValid(const Square& sq) const
	{
		/* we can ignore the rank clipping since the overflow/underflow with
		respect to rank simply vanishes. We only care about the file
		overflow/underflow which is much more work for a knight. */

		// BitBoard knight_loc = this->board_.getBitBoard(Piece::Knight,
		// Color::Black);
		BitBoard knight_loc = 1ULL << static_cast<int>(sq);
		BitBoard spot_1_clip = clear_file[0] & clear_file[1];
		BitBoard spot_2_clip = clear_file[0];
		BitBoard spot_3_clip = clear_file[7];
		BitBoard spot_4_clip = clear_file[7] & clear_file[6];

		/* The clipping masks we just created will be used to ensure that no
		under or overflow positions are computed when calculating the
		possible moves of the knight in certain files. */

		BitBoard spot_1 = (knight_loc & spot_1_clip) << 6;
		BitBoard spot_2 = (knight_loc & spot_2_clip) << 15;
		BitBoard spot_3 = (knight_loc & spot_3_clip) << 17;
		BitBoard spot_4 = (knight_loc & spot_4_clip) << 10;

		BitBoard spot_5_clip = clearFile(7) & clearFile(6);
		BitBoard spot_6_clip = clearFile(7);
		BitBoard spot_7_clip = clearFile(0);
		BitBoard spot_8_clip = clearFile(0) & clearFile(1);

		BitBoard spot_5 = (knight_loc & spot_5_clip) >> 6;
		BitBoard spot_6 = (knight_loc & spot_6_clip) >> 15;
		BitBoard spot_7 = (knight_loc & spot_7_clip) >> 17;
		BitBoard spot_8 = (knight_loc & spot_8_clip) >> 10;

		BitBoard KnightValid =
			spot_1 | spot_2 | spot_3 | spot_4 | spot_5 | spot_6 | spot_7 | spot_8;

		/* compute only the places where the knight can move and attack. The
		caller will determine if this is a white or black night. */
		return (KnightValid & (~this->board_.allBlackPieces()));
	}

	BitBoard Engine::whitePawnValid(const Square& sq) const
	{
		BitBoard white_pawn_one_step, white_pawn_two_steps, white_pawn_valid_moves,
			white_pawn_left_attack, white_pawn_right_attack, white_pawn_attacks,
			white_pawn_valid_attacks, WhitePawnValid;

		BitBoard white_pawn_loc = 1ULL << static_cast<int>(sq);
		/* check the single space infront of the white pawn */
		white_pawn_one_step =
			(white_pawn_loc << 8) & (~this->board_.allPieces());

		/* for all moves that came from rank 2 (home row) and passed the above
		filter, thereby being on rank 3, check and see if I can move forward
		one more */
		white_pawn_two_steps = ((white_pawn_one_step & mask_rank[2]) << 8) &
			(~this->board_.allPieces());

		/* the union of the movements dictate the possible moves forward
		available */
		white_pawn_valid_moves = white_pawn_one_step | white_pawn_two_steps;

		/* next we calculate the pawn attacks */

		/* check the left side of the pawn, minding the underflow File A */
		white_pawn_left_attack = (white_pawn_loc & clear_file[0]) << 7;

		/* then check the right side of the pawn, minding the overflow File H */
		white_pawn_right_attack = (white_pawn_loc & clear_file[7]) << 9;

		/* the union of the left and right attacks together make up all the
		possible attacks */
		white_pawn_attacks = white_pawn_left_attack | white_pawn_right_attack;

		/* Calculate where I can _actually_ attack something */
		white_pawn_valid_attacks =
			white_pawn_attacks & (this->board_.allBlackPieces());

		/* then we combine the two situations in which a white pawn can legally
		attack/move. */
		WhitePawnValid = white_pawn_valid_moves | white_pawn_valid_attacks;

		return WhitePawnValid;
	}

	BitBoard Engine::blackPawnValid(const Square& sq) const
	{
		BitBoard black_pawn_one_step, black_pawn_two_steps, black_pawn_valid_moves,
			black_pawn_left_attack, black_pawn_right_attack, black_pawn_attacks,
			black_pawn_valid_attacks, BlackPawnValid;

		BitBoard black_pawn_loc = 1ULL << static_cast<int>(sq);
		/* check the single space in front of the black pawn */
		black_pawn_one_step =
			(black_pawn_loc >> 8) & (~this->board_.allPieces());

		/* for all moves that came from rank 7 (home row) and passed the above
		filter, thereby being on rank 6, check and see if I can move forward
		one more */
		black_pawn_two_steps = ((black_pawn_one_step & mask_rank[5]) >> 8) &
			(~this->board_.allPieces());

		/* the union of the movements dictate the possible moves forward
		available */
		black_pawn_valid_moves = black_pawn_one_step | black_pawn_two_steps;

		/* next we calculate the pawn attacks */

		/* check the left side of the pawn, minding the underflow File A */
		black_pawn_left_attack = (black_pawn_loc & clear_file[0]) >> 9;

		/* then check the right side of the pawn, minding the overflow File H */
		black_pawn_right_attack = (black_pawn_loc & clear_file[7]) >> 7;

		/* the union of the left and right attacks together make up all the
		possible attacks */
		black_pawn_attacks = black_pawn_left_attack | black_pawn_right_attack;

		/* Calculate where I can _actually_ attack something */
		black_pawn_valid_attacks =
			black_pawn_attacks & (this->board_.allWhitePieces());

		/* then we combine the two situations in which a black pawn can legally
		attack/move. */
		BlackPawnValid = black_pawn_valid_moves | black_pawn_valid_attacks;

		return BlackPawnValid;
	}

	BitBoard Engine::whiteRookValid(const Square& sq) const
	{
		BitBoard occupancy = this->board_.allPieces();
		unsetBit(occupancy, sq);
		occupancy &= rook_mask[static_cast<int>(sq)];
		occupancy *= rook_magics[static_cast<int>(sq)];
		occupancy >>= 64 - rook_relevant_bits[static_cast<int>(sq)];
		
		//static const std::vector<std::vector<BitBoard, 4096>, 64> rook_attacks = initRookAttack();
		//static const std::vector<std::vector<BitBoard>> rook_attacks = initRookAttack();
		return this->rook_attacks_[static_cast<int>(sq)][occupancy] & (~this->board_.allWhitePieces());
	}

	BitBoard Engine::blackRookValid(const Square& sq) const
	{
		BitBoard occupancy = this->board_.allPieces();
		unsetBit(occupancy, sq);
		occupancy &= rook_mask[static_cast<int>(sq)];
		occupancy *= rook_magics[static_cast<int>(sq)];
		occupancy >>= 64 - rook_relevant_bits[static_cast<int>(sq)];

		//static const std::vector<std::vector<BitBoard, 4096>, 64> rook_attacks = initRookAttack();
		//static const std::vector<std::vector<BitBoard>> rook_attacks = initRookAttack();
		return this->rook_attacks_[static_cast<int>(sq)][occupancy] & (~this->board_.allBlackPieces());

	}
	BitBoard Engine::whiteBishopValid(const Square& sq) const
	{
		BitBoard occupancy = this->board_.allPieces();
		unsetBit(occupancy, sq);
		occupancy &= bishop_mask[static_cast<int>(sq)];
		occupancy *= bishop_magics[static_cast<int>(sq)];
		occupancy >>= 64 - bishop_relevant_bits[static_cast<int>(sq)];

		return this->bishop_attacks_[static_cast<int>(sq)][occupancy] & (~this->board_.allWhitePieces());
	}

	BitBoard Engine::blackBishopValid(const Square& sq) const
	{
		BitBoard occupancy = this->board_.allPieces();
		unsetBit(occupancy, sq);
		occupancy &= bishop_mask[static_cast<int>(sq)];
		occupancy *= bishop_magics[static_cast<int>(sq)];
		occupancy >>= 64 - bishop_relevant_bits[static_cast<int>(sq)];

		return this->bishop_attacks_[static_cast<int>(sq)][occupancy] & (~this->board_.allBlackPieces());
	}

	BitBoard Engine::whiteQueenValid(const Square& sq) const
	{
		return ((this->whiteRookValid(sq)) | (this->whiteBishopValid(sq)));
	}

	BitBoard Engine::blackQueenValid(const Square& sq) const
	{
		return ((this->blackRookValid(sq)) | (this->blackQueenValid(sq)));
	}

}