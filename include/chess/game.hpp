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
  
};
} // namespace chess