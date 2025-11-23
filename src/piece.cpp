#include <iostream>
#include "chess/piece.hpp"

// constructor definitions
Pawn::Pawn(Color col) : Piece(col) {}

std::string Pawn::display() {if (color==Color::White) {return "P";} else {return "p";}}
