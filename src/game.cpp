#include "game.h"

namespace Chess {
	Game::Game() : board_(), engine_(board_), game_state_(State::GOING_ON) {
		;
	}

	Game::Game(const std::string_view& fen_string) : board_(fen_string), engine_(board_), game_state_(State::GOING_ON) {
		;
	}

	void Game::makeMove(const Move& move) {
		this->board_.makeMove(move);
	}

	void Game::printBoard() const {
		this->board_.printBoard();
	}
	Engine Game::getEngine() const {
		return this->engine_;
	}
	std::string Game::getFEN() const {
		return this->board_.getFEN();
	}

}