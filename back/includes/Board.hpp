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

        bool is_in_grid(int x, int y) const;

        bool isFull();
        void print();
        size_t get_hash_board() const;
        int compute_score_info(t_score_info score_info, t_captureCount capture, e_cell my) const;
        int get_score_position(e_color color, int pos, t_captureCount capture) const;
        t_direction_info compute_direction_side(t_position &grid_pos, int dx, int dy, e_cell my, e_cell other) const;

};
