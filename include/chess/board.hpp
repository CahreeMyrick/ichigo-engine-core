#pragma once
#include "chess/types.hpp"
#include "chess/piece.hpp"
#include <memory>

class Board {
public:

	// board
	std::unique_ptr<Piece> board[ROWS][COLS];

	// default constructor
	Board() = default;

	// methods
	void display_board();	
	void set_pieces(int row, Color color);
	void create_board();
};
