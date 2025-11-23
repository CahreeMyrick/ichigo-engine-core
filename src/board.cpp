#include "chess/board.hpp"
#include <memory>
#include <iostream>

void Board::display_board() {
    auto colLetters = []() {
        std::cout << "    ";
        for (int c = 0; c < COLS; ++c) std::cout << "  " << char('a' + c) << " ";
        std::cout << "\n";
    };

    const char* TL = "┌"; const char* TR = "┐";
    const char* BL = "└"; const char* BR = "┘";
    const char* T  = "┬"; const char* M  = "┼"; const char* B  = "┴";
    const char* H  = "───"; const char* V = "│";

    auto top_border = [&]() {
        std::cout << "    " << TL;
        for (int c = 0; c < COLS; ++c) {
            std::cout << H << (c == COLS - 1 ? TR : T);
        }
        std::cout << "\n";
    };
    auto mid_border = [&]() {
        std::cout << "    " << "├";
        for (int c = 0; c < COLS; ++c) {
            std::cout << H << (c == COLS - 1 ? "┤" : M);
        }
        std::cout << "\n";
    };
    auto bot_border = [&]() {
        std::cout << "    " << BL;
        for (int c = 0; c < COLS; ++c) {
            std::cout << H << (c == COLS - 1 ? BR : B);
        }
        std::cout << "\n";
    };

    colLetters();
    top_border();

    for (int r = 0; r < ROWS; ++r) {
        std::cout << "  " << r << " " << V;
        for (int c = 0; c < COLS; ++c) {
            char pc = board[r][c] ? board[r][c]->display()[0] : '-';
            std::cout << " " << pc << " " << V;
        }
        std::cout << " " << r << "\n";
        if (r != ROWS - 1) mid_border();
    }

    bot_border();
    colLetters();
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
	set_pieces(0, Color::White);
	set_pieces(7, Color::Black);
}

