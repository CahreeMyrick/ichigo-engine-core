#include <iostream>
#include "chess/piece.hpp"

// constructor definitions
Pawn::Pawn(Color col) : Piece(col) {}
Knight::Knight(Color col) : Piece(col) {}
Bishop::Bishop(Color col) : Piece(col) {}
Rook::Rook(Color col) : Piece(col) {}
Queen::Queen(Color col) : Piece(col) {}
King::King(Color col) : Piece(col) {}
Empty::Empty(Color col) : Piece(col) {}

// displays
std::string Pawn::display() {if (color==Color::White) {return "P";} else {return "p";}}
std::string Knight::display() {if (color==Color::White) {return "N";} else {return "n";}}
std::string Bishop::display() {if (color==Color::White) {return "B";} else {return "b";}}
std::string Rook::display() {if (color==Color::White) {return "R";} else {return "r";}}
std::string Queen::display() {if (color==Color::White) {return "Q";} else {return "q";}}
std::string King::display() {if (color==Color::White) {return "K";} else {return "k";}}
std::string Empty::display() {return "-";}

