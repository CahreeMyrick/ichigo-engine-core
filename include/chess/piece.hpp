#include "chess/types.hpp"
#include <iostream>

// abstract base class 
class Piece {
public:
	// base member var
	Color color = Color::None;

	// base constructor
	Piece(Color col = Color::None) : color(col) {}

	// pure virtual display method
	virtual std::string display() = 0;

	


};

// child class: Pawn
class Pawn : public Piece {
public:
	
	// constructor declaration
	Pawn(Color col);

	// display method
	std::string display() override;
};
