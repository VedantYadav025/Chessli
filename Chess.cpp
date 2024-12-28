// Chess.cpp : Defines the entry point for the application.
//
#include "Chess.h"
#include "Board.h"

int main() {
	std::string square_name;
	std::cin >> square_name;
	printU64(bitboardOfSquare(stringToSquare(square_name)));
	return 0;
}