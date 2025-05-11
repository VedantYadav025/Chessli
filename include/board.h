#pragma once

#include "move.h"
#include "utils.h"

#include <array>
#include <string_view>

namespace Chess {

	class Board {

		public:
			explicit Board();
			explicit Board(const std::string_view& fen_string);
			void makeMove(const Move& move);
			BitBoard allWhitePieces() const;
			BitBoard allBlackPieces() const;
			
		private:
			std::array<BitBoard, 12> m_bitboards;	
	};

}
