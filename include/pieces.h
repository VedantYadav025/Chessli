namespace Chess {
	
enum class Piece_type {
	Pawn,
	Knight,
	Bishop,
	Rook,
	Queen,
	King,
	None,
};

enum class Color_type {
	Black,
	White,
	None,
};

struct Piece {
	Piece_type m_piece;
	Color_type m_color;
};

}
