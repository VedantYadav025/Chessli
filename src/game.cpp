#include "game.h"
#include <iostream>

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

	std::vector<Move> Game::allLegalMoves(const Square& sq) const
	{
		std::pair<Piece, Color> piece_info = this->board_.getPiece(sq);
		std::vector<Move> legal_moves;
		BitBoard legal_move_bitboard = this->engine_.legalMoves(piece_info.first, piece_info.second, sq);
		std::vector<Square> set_bits;
		for (int i = 0; i < 64; i++) {
		    if ((legal_move_bitboard & (1ULL << i)) != 0)
			set_bits.push_back(static_cast<Square>(i));
		}
		for (const auto& x: set_bits)
		    legal_moves.push_back({sq, x});
		return legal_moves;
	}

	void Game::printAllLegalMoves(const Square& sq) const
	{
		std::vector<Move> legal_moves = this->allLegalMoves(sq);
		for (const auto& move: legal_moves)
		    std::cout << move;
		return;
	}

    
}
