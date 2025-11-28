#include "chess/game.hpp"
#include "chess/piece.hpp"
#include <memory>
#include <iostream>
#include <sstream>


Game::Game() {b.create_board();}

void Game::game_loop() {
  std::string user_input = "";
  while (user_input != "quit") {
    b.display_board();
    std::cout << "Enter move: " << std::endl;
    std::getline(std::cin, user_input);
		if (user_input == "quit") {break;}
    move(user_input[0]-'0', user_input[1]-'0', user_input[3]-'0', user_input[4]-'0');
  }
}

bool Game::in_bounds(int r0, int c0, int r1, int c1) {
	return true;
}

bool Game::is_enemy() {
	return true;
}

bool Game::is_friend() {
	return false;
}

bool Game::is_empty() {
	return true;
}


void Game::move(int r0, int c0, int r1, int c1) {
	
	// pawn instance
	/*
	 If the source piece is a pawn, then we must:
	 	• check if the pawn can move to the destinatin square
		• move the pawn from the source square to the destination square
		(afterward, the source square should be of type Piece::Empty, 
		and the destination square should be of type Piece::Pawn)
	 */
	// Pawn* p = dynamic_cast<Pawn*>(b.board[r0][c0].get())
	if (Pawn* p = dynamic_cast<Pawn*>(b.board[r0][c0].get())) {

		if (in_bounds(r0, c0, r1, c1) == false) {std::cout << "Out of bounds. Choose a new move.";}

		if (is_friend()) {std::cout << "Invalid move. Choose a new move.";}
		
		else {

			// move the piece
			//b.board[r1][c1] = std::make_unique<Pawn>(Color::White);

			// make src square type Piece::empty;
			b.board[r1][c1].reset();
			b.board[r1][c1] = std::move(b.board[r0][c0]);
			b.board[r0][c0].reset();
			b.board[r0][c0] = std::make_unique<Empty>(Color::None);

		}

	}

	else {std::cout << "Not Implemented.";}
}

void Game::start_game() {
  game_loop();

}

