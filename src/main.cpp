#include "chess/piece.hpp"

int main() {

	// create piece obj for tetsing
	Pawn p(Color::White);

	if (p.color == Color::White) {
		std::cout << "true\n";
	}

	std::cout << p.display() << std::endl;

	return 0;
}
