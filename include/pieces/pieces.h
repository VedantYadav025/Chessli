// Created by Vedant Yadav on 12th May 2025.
// This file is part of the Chess project.

#pragma once
#include <stdexcept>

namespace Chess {

enum class Piece_type
{
  Pawn,
  Knight,
  Bishop,
  Rook,
  Queen,
  King,
  None,
};

enum class Color_type
{
  Black,
  White,
  None,
};

struct Piece
{
  Piece_type m_piece;
  Color_type m_color;
};

constexpr char
pieceToChar(const Piece& piece)
{
  switch (piece.m_piece) {
    case Piece_type::Pawn:
      return piece.m_color == Color_type::White ? 'P' : 'p';
    case Piece_type::Knight:
      return piece.m_color == Color_type::White ? 'N' : 'n';
    case Piece_type::Bishop:
      return piece.m_color == Color_type::White ? 'B' : 'b';
    case Piece_type::Rook:
      return piece.m_color == Color_type::White ? 'R' : 'r';
    case Piece_type::Queen:
      return piece.m_color == Color_type::White ? 'Q' : 'q';
    case Piece_type::King:
      return piece.m_color == Color_type::White ? 'K' : 'k';
    case Piece_type::None:
      return '.';
  }
  throw std::invalid_argument("Invalid piece type");
}

} // namespace Chess
