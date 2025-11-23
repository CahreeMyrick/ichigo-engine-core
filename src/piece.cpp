#include <iostream>
#include "chess/piece.hpp"

// constructor definitions
Pawn::Pawn(Color col) : Piece(col) {}
Empty::Empty(Color col) : Piece(col) {}


// displays
std::string Pawn::display() {if (color==Color::White) {return "P";} else {return "p";}}
std::string Empty::display() {return "-";}
