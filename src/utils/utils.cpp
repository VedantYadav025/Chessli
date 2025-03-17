#include "utils.h"

namespace Chess
{
	std::uint64_t get_rook_mask(const Square& sq)
	{
		int rank = static_cast<int>(sq) / 8;
		int file = static_cast<int>(sq) % 8;

		std::uint64_t rook = 0ULL;
		return rook;
	}

	std::unordered_map<Square, char> parseFEN(const std::string_view& fen_string)
	{
		std::string expanded_fen;
		std::unordered_map<Square, char> mp;
		for (const char& ch : fen_string) {
			if (ch == ' ')
				break;
			if (ch != '/') {
				if (std::isdigit(ch) && (ch >= '1' && ch <= '8')) {
					for (int i = 0; i < ch - '0'; i++) {
						expanded_fen.push_back('#');
					}
				}
				else {
					expanded_fen.push_back(ch);
				}
			}
		}
		for (int i = 56; i >= 0; i -= 8) {
			for (int j = 0; j < 8; j++) {
				mp[static_cast<Square>(i + j)] = expanded_fen[56 - i + j];
			}
		}
		return mp;
	}

	std::vector<Square> squaresOfPiece(const std::unordered_map<Square, char>& board_map, const std::uint64_t& piece_idx)
	{
		std::vector<Square> squares;
		for (auto it = board_map.begin(); it != board_map.end(); it++) {
			if (it->second == pieceToLetter(piece_idx))
				squares.push_back(it->first);
		}
		return squares;
	}


	std::array<bool, 4> castlingRights(const std::string_view& fen_string)
	{
		bool white_king_side, white_queen_side, black_king_side, black_queen_side;
		//std::array<bool, 4> ans = { false, false, false, false };
		std::size_t space_idx = fen_string.find(" ");
		white_king_side = ((fen_string.find_last_of("K") != std::string::npos) && (fen_string.find_last_of("K") > space_idx));
		white_queen_side = ((fen_string.find_last_of("Q") != std::string::npos) && (fen_string.find_last_of("Q") > space_idx));
		black_king_side = ((fen_string.find_last_of("k") != std::string::npos) && (fen_string.find_last_of("k") > space_idx));
		black_queen_side = ((fen_string.find_last_of("q") != std::string::npos) && (fen_string.find_last_of("q") > space_idx));

		return { white_king_side, white_queen_side, black_king_side, black_queen_side };

	}

}