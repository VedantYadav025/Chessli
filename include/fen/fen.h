#pragma once

#include "pieces/pieces.h"
#include <array>
#include <string_view>

std::array<Chess::Piece, 64>
parseFenString(const std::string_view& fen_string);
