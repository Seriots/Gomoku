#pragma once

#include <vector>

#include "Cell.hpp"

class Board {
    private:
        Cell _board[19][19];

    public:
        Board();
        Board(std::vector <int> white, std::vector <int> black);
        Board(const Board &b);
        ~Board();

        void operator= (const Board &b);

        Cell get(int x, int y) const;
        void set(int x, int y, e_cell cell);

        void print();
};