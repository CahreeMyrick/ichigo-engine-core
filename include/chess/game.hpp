#pragma once
#include "board.hpp"

namespace chess {
class Game{
public:
  // member variable
  Board b;
  Color turn = Color::White;

  // constructor
  Game();

  //methods
  void game_loop();
  void start_game();
  void end_game();
  void move(const std::string &input, std::string &error_msg);
  bool leaves_self_in_check(int r0, int c0, int r1, int c1);
  bool in_check(Color color);
  void find_kings_position(Color color, int &king_row, int &king_col);  
  void change_turn();
  bool is_checkmate(Color col);
  std::string get_color(Color col);
  Color other_color(Color col);
  bool has_any_legal_move(Color col);
  void make_move();
  void undo_move();
  bool load_fen(const std::string& fen, std::string& errmsg);

};
} // namespace chess