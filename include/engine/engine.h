#include "board/board.h"
#include "move/move.h"
#include "pieces/pieces.h"
#include "utils/utils.h"
#include "validMoveGenerator/validMoveGenerator.h"

#include <vector>

namespace Chess {

class Engine {
public:
    explicit Engine(const Board& board);    
    std::vector<Move> getLegalMoves(const Square& square) const;

private:
    BitBoard allWhiteValidAttacks() const;
    BitBoard allBlackValidAttacks() const;
    bool isKingInCheck(const Color_type& color) const;

private:
    const Board& m_board;
};

}