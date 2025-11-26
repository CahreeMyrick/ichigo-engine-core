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
  void move(int r0, int c0, int r1, int c1);
  bool in_bounds(int r0, int c0, int r1, int c1);
  bool is_enemy();
  bool is_empty();
  bool is_friend();
};
