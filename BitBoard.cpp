#include "BitBoard.h"
#include <bitset>

BitBoard::BitBoard(Piece& piece, Color& color)
    : piece_(piece), color_(color) {

    // Initialize bitboard based on the piece type and color
    if (color == Color::White) {
        switch (piece) {
        case Piece::Pawn:
            bitboard_ = 0x000000000000FF00; // White pawns on rank 2
            break;
        case Piece::Knight:
            bitboard_ = 0x0000000000000042; // White knights on b1 and g1
            break;
        case Piece::Bishop:
            bitboard_ = 0x0000000000000024; // White bishops on c1 and f1
            break;
        case Piece::Rook:
            bitboard_ = 0x0000000000000081; // White rooks on a1 and h1
            break;
        case Piece::Queen:
            bitboard_ = 0x0000000000000008; // White queen on d1
            break;
        case Piece::King:
            bitboard_ = 0x0000000000000010; // White king on e1
            break;
        default:
            break;
        }
    }
    else if (color == Color::Black) {
        switch (piece) {
        case Piece::Pawn:
            bitboard_ = 0x00FF000000000000; // Black pawns on rank 7
            break;
        case Piece::Knight:
            bitboard_ = 0x4200000000000000; // Black knights on b8 and g8
            break;
        case Piece::Bishop:
            bitboard_ = 0x2400000000000000; // Black bishops on c8 and f8
            break;
        case Piece::Rook:
            bitboard_ = 0x8100000000000000; // Black rooks on a8 and h8
            break;
        case Piece::Queen:
            bitboard_ = 0x0800000000000000; // Black queen on d8
            break;
        case Piece::King:
            bitboard_ = 0x1000000000000000; // Black king on e8
            break;
        default:
            break;
        }
    }
}

void BitBoard::printBitBoard() const {
    const std::uint64_t value = this->bitboard_;
    for (int i = 56; i >= 0; i -= 8) {
        for (int j = 7; j >= 0; j--) {
            std::cout << ((value >> (i + j)) & 1);
        }
        std::cout << '\n';
    }
}