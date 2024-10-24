#pragma once

#include <vector>

#include "Cell.hpp"

class Board {
    private:
        Cell _board[19][19];
        int _center;

    public:
        Board();
        Board(std::vector <int> white, std::vector <int> black);
        Board(const Board &b);
        ~Board();

        void operator= (const Board &b);

        
        void compute_board_center();

        t_position get_center() const;
        int get_center_pos() const;
        Cell get(int x, int y) const;
        Cell get(int pos) const;
        void set(int x, int y, e_cell cell);
        void set(int pos, e_cell cell);

        bool isFull();
        void print();
};