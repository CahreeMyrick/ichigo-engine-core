#pragma once
#include "chess/types.hpp"
#include "chess/piece.hpp"
#include <memory>

namespace chess {

class Board {
public:

	// board
	std::unique_ptr<Piece> board[ROWS][COLS];

	// default constructor
	Board() = default;

	// methods
	void display_board() const;	
	void set_pieces(int row, Color color);
	void create_board();

	// helper methods for piece movement
	bool in_bounds(const int &r1, const int &c1) const;
  bool is_enemy(const Color &color, const int &r1, const int &c1) const;
  bool is_empty(const int &r1, const int &c1) const;
  bool is_friend(const Color &color, const int &r1, const int &c1) const;
	bool path_clear(int r0, int c0, int r1, int c1) const;
};

} // namespace chess
