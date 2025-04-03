#pragma once
#include "engine/engine.h"
#include "board.h"

#include <cstdint>
#include <string_view>
namespace Chess {

	enum class State : std::uint16_t {
		GOING_ON, WHITE_WON, BLACK_WON, DRAW,
	};

	class Game {
	public:
		Game();
	        Game(const std::string_view& fen_string);
		void makeMove(const Move& move);
		void printBoard() const;
		Engine getEngine() const;
		std::string getFEN() const;
		//void setGameByFEN(const std::string_view& fen_string);
		std::vector<Move> allLegalMoves(const Square& square) const;
	        void printAllLegalMoves(const Square& sq) const;
	private:
		Board board_;
		Engine engine_;
		State game_state_;
	};
}
