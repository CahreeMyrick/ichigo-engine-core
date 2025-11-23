#include "chess/board.hpp"
#include <memory>
#include <iostream>


// methods
void Board::display_board() {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) { 
			std::cout << board[i][j]->display() << " ";
		}
		std::cout << std::endl;
	}
}

void Board::set_pieces(int row, Color color){
	
	// set pawns
	int pawn_row = (row==0) ? 1 : 6;
	for (int j = 0; j < COLS; j++) {
		board[pawn_row][j] = std::make_unique<Pawn>(color);
	}

	// set kngihts
	board[row][1] = std::make_unique<Knight>(color);
	board[row][6] = std::make_unique<Knight>(color);

	// set bishops
	board[row][2] = std::make_unique<Bishop>(color);
	board[row][5] = std::make_unique<Bishop>(color);

	// set rooks
	board[row][0] = std::make_unique<Rook>(color);
	board[row][7] = std::make_unique<Rook>(color);

	// set Queen
	board[row][3] = std::make_unique<Queen>(color);

	// set King
	board[row][4] = std::make_unique<King>(color);
	
	// set empty squares
	if (row == 0) {
		for (int i = 2; i < 6; i++) {
			for (int j = 0; j < COLS; j++) {
				board[i][j] = std::make_unique<Empty>(Color::None);
			}
		}
	}

}

void Board::create_board(){
	set_pieces(7, Color::White);
	set_pieces(0, Color::Black);
}

