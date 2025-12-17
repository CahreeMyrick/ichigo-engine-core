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

	// pure virtual clone method for copying pieces
	virtual std::unique_ptr<Piece> clone() const = 0;

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

	// clone method
	std::unique_ptr<Piece> clone() const override {
		return std::make_unique<Pawn>(*this);
	}
};

class Knight : public Piece {
public:

	// constructor declaration
	Knight(Color col);

	// display method
	std::string display() override;

	// can_move method
	bool can_move(const Board& b, int r0, int c0, int r1, int c1) const override;

	// clone method
	std::unique_ptr<Piece> clone() const override {
		return std::make_unique<Knight>(*this);
	}
};

class Bishop : public Piece {
public: 
	Bishop(Color col); 
	std::string display() override; 
	bool can_move(const Board& b, int r0, int c0, int r1, int c1) const override;

	// clone method
	std::unique_ptr<Piece> clone() const override {
		return std::make_unique<Bishop>(*this);
	}
};

class Rook   : public Piece { 
public:
	Rook(Color col);   
	std::string display() override; 
	bool can_move(const Board& b, int r0, int c0, int r1, int c1) const override;

	// clone method
	std::unique_ptr<Piece> clone() const override {
		return std::make_unique<Rook>(*this);
	}
};

class Queen  : public Piece { 
public: 
	Queen(Color col);  
	std::string display() override;
	bool can_move(const Board& b, int r0, int c0, int r1, int c1) const override;

	// clone method
	std::unique_ptr<Piece> clone() const override {
		return std::make_unique<Queen>(*this);
	}
};

class King   : public Piece { 
public:
	King(Color col);   
	std::string display() override;
	bool can_move(const Board& b, int r0, int c0, int r1, int c1) const override; 

	// clone method
	std::unique_ptr<Piece> clone() const override {
		return std::make_unique<King>(*this);
	}
};

class Empty : public Piece {
public: 
	// constructor declaration
	Empty(Color col);

	// display method
	std::string display() override;

	bool can_move(const Board& b, int r0, int c0, int r1, int c1) const override {return false; }

	// clone method
	std::unique_ptr<Piece> clone() const override {
		return std::make_unique<Empty>(*this);
	}
};

} // namespace chess