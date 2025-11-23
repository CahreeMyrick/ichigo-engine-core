#include "chess/types.hpp"
#include <iostream>
#pragma once

// abstract base class 
class Piece {
public:
	// base member var
	Color color = Color::None;

	// base constructor
	Piece(Color col = Color::None) : color(col) {}

	// virtual display method
	virtual std::string display() {return "?";}

	// virtual destructor
	virtual ~Piece() = default;

	


};

// child class: Pawn
class Pawn : public Piece {
public:
	
	// constructor declaration
	Pawn(Color col);

	// display method
	std::string display() override;
};

class Empty : public Piece {
public: 
	// constructor declaration
	Empty(Color col);

	// display method
	std::string display() override;
};
