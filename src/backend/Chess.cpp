// Chess.cpp : Defines the entry point for the application.
//
#include "Board.h"
#include <iostream>

int main() {
  Board chess_board;
  chess_board.printBoard(Color::White);
  return 0;
}
