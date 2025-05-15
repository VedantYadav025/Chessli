#include "../board/board.h"
#include "square/square.h"
#include "utils/utils.h"

namespace Chess {
	
class validMoveGenerator {
			
	public:
			validMoveGenerator(const Board& board);
			BitBoard bitboardOfValidMoves(const Square& square) const;
			void printBoard() const;

	private:
		const Board& m_board;

	// direction sensitive piece move functions
	private:
		BitBoard whitePawnValid(const Square& sq) const;
		BitBoard blackPawnValid(const Square& sq) const;


	// direction agnostic piece move funcitons
	private:
		BitBoard kingValidBitBoard(const Square& square) const;	
		BitBoard knightValidBitBoard(const Square& square) const;
		BitBoard rookValidBitBoard(const Square& square) const;
		BitBoard bishopValidBitBoard(const Square& square) const;
		BitBoard queenValidBitBoard(const Square& square) const;
};

}
