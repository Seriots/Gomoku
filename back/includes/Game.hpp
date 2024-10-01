#pragma once

#include <string>
#include <vector>

#include "Board.hpp"

class Game {
    private:
        Board       _board;
    public:
        Game();
        Game(std::vector <int> white, std::vector <int> black);
        Game(const Game &g);
        ~Game();

        void operator= (const Game &g);

        Board get_board() const;
        std::vector<int> get_blocked(e_color color);
};