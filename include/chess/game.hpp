#pragma once
#include "board.hpp"

namespace chess {
class Game{
public:
  // member variable
  Board b;

  // constructor
  Game();

  //methods
  void game_loop();
  void start_game();
  void move(const std::string &input, std::string &error_msg);
  bool leaves_self_in_check(int r0, int c0, int r1, int c1);
  bool in_check(Color color);
  void find_kings_position(Color color, int &king_row, int &king_col);  
};
} // namespace chess