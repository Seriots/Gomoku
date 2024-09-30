#pragma once

#include <vector>

#include "Cell.hpp"

class Board {
    private:
        Cell _board[19][19];

    public:
        Board();
        Board(std::vector <int> white, std::vector <int> black, std::vector <int> blocked);
        Board(const Board &b);
        ~Board();

        void operator= (const Board &b);

        Cell get(int x, int y) const;
};