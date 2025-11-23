#pragma once
#include "board.hpp"

class Game{
public:
  // member variable
  Board b;

  // constructor
  Game();

  //methods
  void game_loop();
  void start_game();
};