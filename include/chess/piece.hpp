#include "chess/types.hpp"
#include <iostream>
#pragma once

namespace chess {

class Board; // forward declaration

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

	// virtual can_move method
	virtual bool can_move(const Board& b, int r0, int c0, int r1, int c1) const {return false; }

};

// child class: Pawn
class Pawn : public Piece {
public:
	
	// constructor declaration
	Pawn(Color col);

	// display method
	std::string display() override;

	// can_move method
	bool can_move(const Board& b, int r0, int c0, int r1, int c1) const override;
};

class Knight : public Piece {
public:

	// constructor declaration
	Knight(Color col);

	// display method
	std::string display() override;

	// can_move method
	bool can_move(const Board& b, int r0, int c0, int r1, int c1) const override;

};

class Bishop : public Piece {
public: 
	Bishop(Color); 
	std::string display() override; 
	bool can_move(const Board& b, int r0, int c0, int r1, int c1) const override;
};

class Rook   : public Piece { 
public:
	Rook(Color);   
	std::string display() override; 
	bool can_move(const Board& b, int r0, int c0, int r1, int c1) const override;
};

class Queen  : public Piece { 
public: 
	Queen(Color);  
	std::string display() override;
	bool can_move(const Board& b, int r0, int c0, int r1, int c1) const override;
};

class King   : public Piece { 
public:
	King(Color);   
	std::string display() override;
	bool can_move(const Board& b, int r0, int c0, int r1, int c1) const override; 
};

class Empty : public Piece {
public: 
	// constructor declaration
	Empty(Color col);

	// display method
	std::string display() override;
};

} // namespace chess