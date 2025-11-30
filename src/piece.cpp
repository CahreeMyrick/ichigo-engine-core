#include <iostream>
#include "chess/piece.hpp"
#include "chess/board.hpp"

namespace chess {

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


// ---- can_move implementations (pseudo-legal) ----
bool Pawn::can_move(const Board& b, int r0, int c0, int r1, int c1) const {

    // make sure destination square != src square
    if (r0 == r1 && c0 == c1) return false;

    // make sure dest square is in bounds and not occupied by a friendly piece
    if (!b.in_bounds(r1, c1) || b.is_friend(color, r1, c1)) return false;

    int dir = (color == Color::White) ? +1 : -1;
    int start_row = (color == Color::White) ? 1 : 6;

    int dr = r1 - r0;
    int dc = c1 - c0;

    if (dc == 0 && dr == dir && b.is_empty(r1, c1)) return true;

    if (dc == 0 && dr == 2*dir && r0 == start_row) {
        int midr = r0 + dir;
        if (b.is_empty(midr, c0) && b.is_empty(r1, c1)) return true;
    }

    if (std::abs(dc) == 1 && dr == dir && b.is_enemy(color, r1, c1)) return true;

    return false; // EP handled in Game
}


bool Knight::can_move(const Board& b, int r0, int c0, int r1, int c1) const {
    if (r0 == r1 && c0 == c1) return false;
    if (!b.in_bounds(r1, c1) || b.is_friend(color, r1, c1)) return false;
    int dr = std::abs(r1 - r0), dc = std::abs(c1 - c0);
    return (dr == 2 && dc == 1) || (dr == 1 && dc == 2);
}

bool Bishop::can_move(const Board& b, int r0, int c0, int r1, int c1) const {
    if (r0 == r1 && c0 == c1) return false;
    if (!b.in_bounds(r1, c1) || b.is_friend(color, r1, c1)) return false;
    int dr = std::abs(r1 - r0), dc = std::abs(c1 - c0);
    if (dr != dc) return false;
    return b.path_clear(r0, c0, r1, c1);
}

bool Rook::can_move(const Board& b, int r0, int c0, int r1, int c1) const {
    if (r0 == r1 && c0 == c1) return false;
    if (!b.in_bounds(r1, c1) || b.is_friend(color, r1, c1)) return false;
    if (r0 != r1 && c0 != c1) return false;
    return b.path_clear(r0, c0, r1, c1);
}

bool Queen::can_move(const Board& b, int r0, int c0, int r1, int c1) const {
    if (r0 == r1 && c0 == c1) return false;
    if (!b.in_bounds(r1, c1) || b.is_friend(color, r1, c1)) return false;
    int dr = std::abs(r1 - r0), dc = std::abs(c1 - c0);
    if (!(r0 == r1 || c0 == c1 || dr == dc)) return false;
    return b.path_clear(r0, c0, r1, c1);
}

bool King::can_move(const Board& b, int r0, int c0, int r1, int c1) const {
    if (r0 == r1 && c0 == c1) return false;
    if (!b.in_bounds(r1, c1) || b.is_friend(color, r1, c1)) return false;
    int dr = std::abs(r1 - r0), dc = std::abs(c1 - c0);
    return std::max(dr, dc) == 1; // castling handled in Game
}

} // namespace chess