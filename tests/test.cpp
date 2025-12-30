#include <iostream>
#include <string>
#include "chess/game.hpp"
#include "chess/types.hpp"

namespace chess {

bool test_mate(Game& game) {
    std::string mates[] = {
        "rnb1kbnr/pppp1ppp/8/4p3/6Pq/5P2/PPPPP2P/RNBQKBNR w KQkq - 1 3"
    };

    for (const std::string& fen : mates) {
        std::string error_msg;

        bool ok = game.load_fen(fen, error_msg); // <-- verify meaning
        if (!ok) {
            std::cerr << "load_fen failed: " << error_msg << "\n";
            return false;
        }

        game.b.display_board();
        bool is_mate = game.is_checkmate(Color::White);
        std::cout << "is_checkmate(White) = " << (is_mate ? "true" : "false") << "\n";
        return is_mate; // since you only have 1 fen right now
    }

    return false;
}

} // namespace chess

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " mate\n";
        return 2;
    }

    chess::Game game;

    std::string cmd = argv[1];
    if (cmd == "mate") {
        bool result = chess::test_mate(game);
        std::cout << "result = " << (result ? "true" : "false") << "\n";
        return result ? 0 : 1;
    }

    std::cerr << "Unknown command: " << cmd << "\n";
    return 2;
}
