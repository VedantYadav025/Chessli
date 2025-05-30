#pragma once

#include "../square/square.h"
#include <ostream>

namespace Chess {

struct Move
{
  Square m_from, m_to;
};

void printMove(const Move& move);


}
