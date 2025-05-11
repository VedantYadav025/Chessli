#pragma once

#include "move.h"
#include "utils.h"

#include <array>
#include <string_view>

namespace Chess {

    enum {
		WHITE_PAWN_IDX,
		WHITE_KNIGHT_IDX,
		WHITE_BISHOP_IDX,
		WHITE_ROOK_IDX,
		WHITE_QUEEN_IDX,
		WHITE_KING_IDX,
		BLACK_PAWN_IDX,
		BLACK_KNIGHT_IDX,
		BLACK_BISHOP_IDX,
		BLACK_ROOK_IDX,
		BLACK_QUEEN_IDX,
		BLACK_KING_IDX
    };


	class Board {

		public:
			explicit Board();
			explicit Board(const std::string_view& fen_string);
			void makeMove(const Move& move);
			void printBoard() const;
			BitBoard allWhitePieces() const;
			BitBoard allBlackPieces() const;
			
		private:
			std::array<BitBoard, 12> m_bitboards;	
	};

}
