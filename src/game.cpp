#include "chess/game.hpp"
#include "chess/piece.hpp"
#include <memory>
#include <iostream>
#include <sstream>

namespace chess {

Game::Game() {b.create_board();}

void Game::game_loop() {
  std::string user_input = "";
  while (user_input != "quit") {
    b.display_board();
    std::cout << "Enter move: " << std::endl;
    std::getline(std::cin, user_input);
		if (user_input == "quit") {break;}
    std::string error_msg = "";
    move(user_input, error_msg);
    if (!error_msg.empty()) {
      std::cout << "Error: " << error_msg << std::endl;
    }
  }
}

void Game::find_kings_position(Color color, int &king_row, int &king_col){
    for (int i = 0; i < ROWS; i++) {
	    for (int j = 0; j < COLS; j++) {
	    	if (dynamic_cast<const King*>(b.board[i][j].get()) && b.board[i][j]->color == color) {
			king_row = i;
			king_col = j;
	    	}
	    }
    }

}

bool Game::in_check(Color color) {
    /*
     • Find the kings position
     • check if any piece can move to the kings position
     (can make use of their can_move() method)
    */
	
    // find the kinds position
    // search through each square in the array

	int king_row, king_col;
	find_kings_position(color, king_row, king_col);

	// check if any piece can move to the kings position
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			const auto &p =b.board[i][j];
			if (p->color != color && p->can_move(b, i, j, king_row, king_col)) {
				return true;
			}
		}
	}

	return false;	
}

bool Game::leaves_self_in_check(int r0, int c0, int r1, int c1){
  // defines references to src and dest pieces
	auto &src_piece = b.board[r0][c0];
	auto &dest_piece = b.board[r1][c1];

	// simulate move
	std::unique_ptr<Piece> captured = std::move(dest_piece);
	std::unique_ptr<Piece> from = std::move(src_piece);
  src_piece = std::make_unique<Empty>(Color::None);
	dest_piece = std::move(from);

	// check if in check
	bool check = in_check(dest_piece->color);

	// revert move
	src_piece = std::move(dest_piece);
	dest_piece = std::move(captured);

	return check;

}


void Game::move(const std::string &input, std::string &error_msg  ) {
  std::istringstream iss(input);
  int r0, c0, r1, c1;

  if (!(iss >> r0 >> c0 >> r1 >> c1)) {
    error_msg = "Invalid input format. Please enter moves as: r0 c0 r1 c1";
    return;
  }

  else {
      std::unique_ptr<Piece> &src_piece = b.board[r0][c0];
  }

  if (!b.in_bounds(r1, c1)) {
    error_msg = "Move out of bounds.";
    return;
  }

  if (!b.board[r0][c0]) {
    error_msg = "No piece at source position.";
    return;
  }

  if (!b.board[r0][c0]->can_move(b, r0, c0, r1, c1)) {
    error_msg = "Piece cannot move to the specified destination.";
    return;
  }

  
  if (leaves_self_in_check(r0, c0, r1, c1)) {
    error_msg = "Invalid move. Move would leave player in check.";
    return;
  }

  b.board[r1][c1] = std::move(b.board[r0][c0]);
  b.board[r0][c0] = std::make_unique<Empty>(Color::None);
}
	

void Game::start_game() {
  game_loop();
}

} // namespace chess
