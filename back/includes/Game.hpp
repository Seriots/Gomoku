#pragma once

#include <string>
#include <vector>

#include "Board.hpp"

class Game {
    private:
        Board       _board;

        bool check_sequence(int x, int y, int dx, int dy, std::vector<e_cell> cell);

    public:
        Game();
        Game(std::vector <int> white, std::vector <int> black);
        Game(const Game &g);
        ~Game();

        void operator= (const Game &g);

        void set(int pos, e_cell cell);

        Board get_board() const;
        
        std::vector<int> get_blocked(e_color color);
        std::vector<int> get_captured(int pos);

        void print_board();
};