#include "board.h"

namespace Chess
{
	Board::Board() : side_to_move_(Color::White), right_to_castle_({ true, true, true, true }) {
		// Initialize White pieces
		this->bitboards_[WHITE_KING_IDX] = WHITE_KING_INIT;

		this->bitboards_[WHITE_QUEEN_IDX] = WHITE_QUEEN_INIT;

		this->bitboards_[WHITE_ROOK_IDX] = WHITE_ROOK_INIT;

		this->bitboards_[WHITE_BISHOP_IDX] = WHITE_BISHOP_INIT;

		this->bitboards_[WHITE_KNIGHT_IDX] = WHITE_KNIGHT_INIT;

		this->bitboards_[WHITE_PAWN_IDX] = WHITE_PAWN_INIT;

		// Initialize Black pieces
		this->bitboards_[BLACK_KING_IDX] = BLACK_KING_INIT;

		this->bitboards_[BLACK_QUEEN_IDX] = BLACK_QUEEN_INIT;

		this->bitboards_[BLACK_ROOK_IDX] = BLACK_ROOK_INIT;

		this->bitboards_[BLACK_BISHOP_IDX] = BLACK_BISHOP_INIT;

		this->bitboards_[BLACK_KNIGHT_IDX] = BLACK_KNIGHT_INIT;

		this->bitboards_[BLACK_PAWN_IDX] = BLACK_PAWN_INIT;

		this->board_map_ = makeInitialBoardMap();
	}

	Board::Board(const std::string_view& fen_string)
		: board_map_(parseFEN(fen_string)),
		right_to_castle_(castlingRights(fen_string))
	{

		this->bitboards_[WHITE_PAWN_IDX] = bitboardOfOccupiedSquares(squaresOfPiece(board_map_, WHITE_PAWN_IDX));
		this->bitboards_[WHITE_KNIGHT_IDX] = bitboardOfOccupiedSquares(squaresOfPiece(board_map_, WHITE_KNIGHT_IDX));
		this->bitboards_[WHITE_BISHOP_IDX] = bitboardOfOccupiedSquares(squaresOfPiece(board_map_, WHITE_BISHOP_IDX));
		this->bitboards_[WHITE_ROOK_IDX] = bitboardOfOccupiedSquares(squaresOfPiece(board_map_, WHITE_ROOK_IDX));
		this->bitboards_[WHITE_QUEEN_IDX] = bitboardOfOccupiedSquares(squaresOfPiece(board_map_, WHITE_QUEEN_IDX));
		this->bitboards_[WHITE_KING_IDX] = bitboardOfOccupiedSquares(squaresOfPiece(board_map_, WHITE_KING_IDX));

		this->bitboards_[BLACK_PAWN_IDX] = bitboardOfOccupiedSquares(squaresOfPiece(board_map_, BLACK_PAWN_IDX));
		this->bitboards_[BLACK_KNIGHT_IDX] = bitboardOfOccupiedSquares(squaresOfPiece(board_map_, BLACK_KNIGHT_IDX));
		this->bitboards_[BLACK_BISHOP_IDX] = bitboardOfOccupiedSquares(squaresOfPiece(board_map_, BLACK_BISHOP_IDX));
		this->bitboards_[BLACK_ROOK_IDX] = bitboardOfOccupiedSquares(squaresOfPiece(board_map_, BLACK_ROOK_IDX));
		this->bitboards_[BLACK_QUEEN_IDX] = bitboardOfOccupiedSquares(squaresOfPiece(board_map_, BLACK_QUEEN_IDX));
		this->bitboards_[BLACK_KING_IDX] = bitboardOfOccupiedSquares(squaresOfPiece(board_map_, BLACK_KING_IDX));


		std::size_t space_idx = fen_string.find(' ');
		if (fen_string[space_idx + 1] == 'w')
			this->side_to_move_ = Color::White;
		else
			this->side_to_move_ = Color::Black;
	}
	void Board::printBoard() const
	{
		char piece_rep;
		for (int i = static_cast<int>(Square::a8); i >= static_cast<int>(Square::a1);
			i -= 8) {
			std::cout << (i / 8) + 1 << "  ";
			for (int j = 0; j < 8; j++) {
				// piece_rep = this->board_map_[static_cast<Square>(i + j)];
				// piece_rep = this->board_map_.find(static_cast<Square>(i + j))->second;
				auto it = this->board_map_.find(static_cast<Square>(i + j));
				if (it != this->board_map_.end())
					piece_rep = it->second;
				else
					piece_rep = '\0';
				if (piece_rep == '\0')
					std::cout << '*' << ' ';
				else
					std::cout << piece_rep << ' ';
			}
			std::cout << '\n';
		}
		std::cout << "\n   a b c d e f g h\n";
	}
	void Board::makeMove(const Move& move)
	{
		Square from_square = move.from_square;
		Square to_square = move.to_square;
		int idx1 = this->indexOfPieceOccupyingSquare(
			from_square);  // idx of the bitboard which occupies the square
		if (idx1 == -1)
			throw std::invalid_argument(
				"Invalid move, no piece placed on from_square\n");
		//this->bitboards_[idx1].unsetBit(
			//static_cast<int>(from_square));  // removing from current position
		unsetBit(this->bitboards_[idx1], from_square);

		int idx2 = this->indexOfPieceOccupyingSquare(to_square);
		if (idx2 != -1)
		{
			//this->bitboards_[idx2].unsetBit(static_cast<int>(to_square));
			unsetBit(this->bitboards_[idx2], to_square);
		}

		//this->bitboards_[idx1].setBit(
			//static_cast<int>(to_square));  // placing on current position
		setBit(this->bitboards_[idx1], to_square);

		// Editing the map
		this->board_map_[from_square] = '\0';
		this->board_map_[to_square] = pieceToLetter(idx1);

		if (this->side_to_move_ == Color::Black)
			this->side_to_move_ = Color::White;
		else if (this->side_to_move_ == Color::White)
			this->side_to_move_ = Color::Black;
	}

	BitBoard Board::allWhitePieces() const
	{
		BitBoard  bitboard = this->bitboards_[WHITE_KING_IDX] |
			this->bitboards_[WHITE_BISHOP_IDX] |
			this->bitboards_[WHITE_KNIGHT_IDX] |
			this->bitboards_[WHITE_ROOK_IDX] |
			this->bitboards_[WHITE_QUEEN_IDX] |
			this->bitboards_[WHITE_PAWN_IDX];
		return bitboard;
	}

	BitBoard Board::allBlackPieces() const
	{
		BitBoard bitboard = this->bitboards_[BLACK_KING_IDX] |
			this->bitboards_[BLACK_QUEEN_IDX] |
			this->bitboards_[BLACK_KNIGHT_IDX] |
			this->bitboards_[BLACK_ROOK_IDX] |
			this->bitboards_[BLACK_PAWN_IDX] |
			this->bitboards_[BLACK_BISHOP_IDX];
		return bitboard;
	}

	BitBoard Board::allPieces() const
	{
		return this->allBlackPieces() | this->allWhitePieces();
	}
	std::string Board::getFEN() const
	{
		std::string fen;
		char piece_rep;
		int empty_squares = 0;
		for (int i = 56; i >= 0; i -= 8) {
			for (int j = 0; j < 8; j++) {
				auto it = this->board_map_.find(static_cast<Square>(i + j));
				if (it != this->board_map_.end())
					piece_rep = it->second;
				else
					piece_rep = '\0';

				if (piece_rep != '\0') {
					if (empty_squares != 0) {
						fen.push_back(empty_squares + '0');
						empty_squares = 0;
					}
					fen.push_back(piece_rep);
				}
				else {
					empty_squares++;
				}
			}
			if (empty_squares != 0) fen.push_back(empty_squares + '0');
			if (i != 0) fen.push_back('/');
			empty_squares = 0;
		}
		fen.push_back(' ');
		if (side_to_move_ == Color::White)
			fen.push_back('w');
		else if (side_to_move_ == Color::Black)
			fen.push_back('b');

		return fen;
	}

	int Board::indexOfPieceOccupyingSquare(const Square& sq) const
	{
		for (int i = 0; i < 12; i++) {
			if ((this->bitboards_[i] & (1ULL << static_cast<int>(sq))) != 0)
				return i;
		}
		return -1;  // no piece is occupying that Square	
	}

}