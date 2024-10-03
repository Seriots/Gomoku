#pragma once

#include <string>
#include <vector>

#include "Board.hpp"

class Game {
    private:
        Board       _board;

        bool check_sequence(int x, int y, int dx, int dy, std::vector<e_cell> cell);
        bool check_double_free_three(int x, int y, e_cell color);
        bool check_free_three(int x, int y, int ax, int ay, e_cell color);

    public:
        Game();
        Game(std::vector <int> white, std::vector <int> black);
        Game(const Game &g);
        ~Game();

        void operator= (const Game &g);

        void set(int pos, e_cell cell);
        void set(std::vector<int> pos, e_cell cell);
        void unset(std::vector<int> pos);

        Board get_board() const;
        
        std::vector<int> get_new_blocked_pos(e_color color);
        std::vector<int> get_captured(int pos);

        void print_board();

        int heuristic(e_color color, int pos);

        std::pair<int, int> compute_best_move(e_color color, int depth, int is_maxi);
};