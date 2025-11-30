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

  b.board[r1][c1] = std::move(b.board[r0][c0]);
  b.board[r0][c0] = std::make_unique<Empty>(Color::None);
}
	

void Game::start_game() {
  game_loop();
}

} // namespace chess
