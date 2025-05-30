#include "move/move.h"

#include <iostream>

void
Chess::printMove(const Move& move)
{
   
    int file_from = static_cast<int>(move.m_from) % 8;
    int file_to = static_cast<int>(move.m_to) % 8;

    int rank_from = static_cast<int>(move.m_from) / 8.0;
    int rank_to = static_cast<int>(move.m_to) / 8.0;

    std::cout << (char('a' + file_from)) << (rank_from + 1) << ' ' << (char('a' + file_to)) << (rank_to + 1) << '\n';
}