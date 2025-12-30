#include "chess/game.hpp"
#include "chess/piece.hpp"
#include <memory>
#include <iostream>
#include <sstream>

namespace chess {

Game::Game() {b.create_board();}

std::string Game::get_color(Color col) {
  if (col==Color::White) {return "White";}
  else if (col==Color::Black) {return "Black";}
  else {return "None";}
}

Color Game::other_color(Color col) {
  if (col == Color::White) {return Color::Black;}
  else {return Color::Black;}
}

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

void Game::change_turn() {(turn == Color::White ? turn = Color::Black : turn = Color::White);}

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
			if (p != nullptr && p->color != color && p->can_move(b, i, j, king_row, king_col)) {
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

bool Game::is_checkmate(Color col) {
  /*
  Criteria for checkmate:
  - King is in check
  - King has no valid moves
  - The attacking piece cannot taken
  - The check cannot be blocked
  */
  
  if (in_check(col) && !has_any_legal_move(col)) {return true;}

  return false;
}

void Game::move(const std::string &input, std::string &error_msg  ) {
  std::istringstream iss(input);
  int r0, c0, r1, c1;

  if (!(iss >> r0 >> c0 >> r1 >> c1)) {
    error_msg = "Invalid input format. Please enter moves as: r0 c0 r1 c1";
    return;
  }

  if (b.board[r0][c0]->color != turn) {
    error_msg = "Not your turn.";
    return;
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

  if (is_checkmate(other_color(turn))) {
    std::string winning_color = get_color(turn);
    std::cout << "Game Over. " << winning_color << "wins! \n";
    end_game();
  }

  change_turn();
}


bool Game::has_any_legal_move(Color col) {
    for (int r0=0;r0<ROWS;++r0)
        for (int c0=0;c0<COLS;++c0) {
            Piece* p = b.board[r0][c0].get();
            if (!p || p->color!=col) continue;

            for (int r1=0;r1<ROWS;++r1)
                for (int c1=0;c1<COLS;++c1) {
                    if (r0==r1 && c0==c1 || b.is_friend(p->color, r1, c1)) continue;

                    /*
                    // Special: castling
                    if (dynamic_cast<King*>(p) && r0==r1 && std::abs(c1-c0)==2) {
                        if (c1>c0 ? can_castle_king_side(col) : can_castle_queen_side(col))
                            return true;
                        continue;
                    }

                    // En passant possibility
                    if (dynamic_cast<Pawn*>(p) && std::abs(c1-c0)==1) {
                        int dir = (col==Color::White)?+1:-1;
                        if (r1==r0+dir && b.is_empty(r1,c1) && ep.valid
                            && ep.target_r==r1 && ep.target_c==c1 && ep.pawnColor!=col) {
                            if (!leaves_self_in_check(r0,c0,r1,c1, std::make_pair(ep.captured_r,ep.captured_c)))
                                return true;
                            continue;
                        }
                    }*/

                    // Normal pseudo-legal then legality check
                    if (p->can_move(b,r0,c0,r1,c1)) {
                        if (!leaves_self_in_check(r0,c0,r1,c1))
                            return true;
                    }
                }
        }
    return false;
}

bool Game::load_fen(const std::string& fen, std::string& errmsg) {
    // FEN: <pieces> <side> <castling> <ep> <halfmove> <fullmove>
    std::istringstream ss(fen);
    std::string boardpart, stm, castle, epstr, half, full;
    if (!(ss >> boardpart >> stm >> castle >> epstr >> half >> full)) {
        errmsg = "Bad FEN: missing fields"; return false;
    }

    b.clear();

    // --- piece placement ---
    int r = 7, c = 0;
    for (char ch : boardpart) {
        if (ch == '/') { r--; c = 0; continue; }
        if (std::isdigit(static_cast<unsigned char>(ch))) { c += (ch - '0'); continue; }
        if (c > 7 || r < 0) { errmsg = "Bad FEN: placement overflow"; return false; }

        std::unique_ptr<Piece> up;
        Color col = std::isupper(static_cast<unsigned char>(ch)) ? Color::White : Color::Black;
        char pc = std::tolower(static_cast<unsigned char>(ch));
        switch (pc) {
            case 'p': up = std::make_unique<Pawn>(col);   break;
            case 'n': up = std::make_unique<Knight>(col); break;
            case 'b': up = std::make_unique<Bishop>(col); break;
            case 'r': up = std::make_unique<Rook>(col);   break;
            case 'q': up = std::make_unique<Queen>(col);  break;
            case 'k': up = std::make_unique<King>(col);   break;
            default: errmsg = "Bad FEN: bad piece"; return false;
        }
        b.board[r][c++] = std::move(up);
    }

    if (stm == "w") turn = Color::White;
    else if (stm == "b") turn = Color::Black;
    else { errmsg = "Bad FEN: side to move"; return false; }

    /*
    // --- castling rights: default to "moved" (no castling), then enable only if pieces present
    auto setMoved = [&](int rr, int cc, bool moved){
        if (b.board[rr][cc]) b.board[rr][cc]->hasMoved = moved;
    };

    auto kingAt = [&](int rr, int cc){
        return b.board[rr][cc] && dynamic_cast<King*>(b.board[rr][cc].get());
    };
    auto rookAt = [&](int rr, int cc){
        return b.board[rr][cc] && dynamic_cast<Rook*>(b.board[rr][cc].get());
    };

    // Disable all by default
    setMoved(0,4,true); setMoved(0,7,true); setMoved(0,0,true);
    setMoved(7,4,true); setMoved(7,7,true); setMoved(7,0,true);

    // Enable only the specific pieces if rights exist AND pieces are present
    for (char cch : castle) {
        switch (cch) {
            case 'K': if (kingAt(0,4) && rookAt(0,7)) { setMoved(0,4,false); setMoved(0,7,false); } break;
            case 'Q': if (kingAt(0,4) && rookAt(0,0)) { setMoved(0,4,false); setMoved(0,0,false); } break;
            case 'k': if (kingAt(7,4) && rookAt(7,7)) { setMoved(7,4,false); setMoved(7,7,false); } break;
            case 'q': if (kingAt(7,4) && rookAt(7,0)) { setMoved(7,4,false); setMoved(7,0,false); } break;
            case '-': /* nothing  break;*/
            // default: /* ignore unknown chars */ break; */
       // }
   // }

    // --- en passant target square (square the capturing pawn would move TO)
   /* ep.valid = false;
    if (epstr != "-" && epstr.size() == 2) {
        int file = epstr[0] - 'a';
        int rank = epstr[1] - '1';
        if (file >= 0 && file < 8 && rank >= 0 && rank < 8) {
            ep.valid     = true;
            ep.target_r  = rank;
            ep.target_c  = file;
            ep.captured_r = (turn == Color::White ? rank - 1 : rank + 1); // square of pawn that double-stepped
            ep.captured_c = file;
            ep.pawnColor  = other(turn); // color that double-stepped last move
        }
    } */
    
    return true;
}

void Game::start_game() {
  game_loop();
}

void Game::end_game() {

  
}


} // namespace chess
