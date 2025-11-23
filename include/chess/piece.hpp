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

class Knight : public Piece {
public:

	// constructor declaration
	Knight(Color col);

	// display method
	std::string display() override;

};

class Bishop : public Piece {
public: 
	Bishop(Color); 
	std::string display() override; 
};

class Rook   : public Piece { 
public: explicit Rook(Color);   
std::string display() override; 
};

class Queen  : public Piece { 
public: 
	Queen(Color);  
	std::string display() override;
};
class King   : public Piece { 
public:
	King(Color);   
	std::string display() override; 
};

class Empty : public Piece {
public: 
	// constructor declaration
	Empty(Color col);

	// display method
	std::string display() override;
};
