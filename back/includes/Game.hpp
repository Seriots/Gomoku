#pragma once

#include <string>
#include <vector>

#include "Board.hpp"

enum e_dna {
    ALIGN_FIVE,
    FREE_FOUR,
    FREE_THREE,
    ANY_ALIGNEMENT,
    CAPTURE_TOTAL_2,
    CAPTURE_TOTAL_4,
    CAPTURE_TOTAL_6,
    CAPTURE_TOTAL_8,
    CAPTURE_TOTAL_10,
    BLOCK_FREE_THREE,
    BLOCK_FREE_FOUR,
    BLOCK_CAPTURE,
    BLOCK_WIN,
    SETUP_CAPTURE,
    IS_CAPTURABLE
};


class Game {
    private:
        Board                   _board;
        std::map<e_dna, int>    _dna;
        t_request               _request;
        std::vector<int>        _interesting_pos;
        std::vector<int>        _blocked_pos;


        void init_dna();

        bool check_sequence(int x, int y, int dx, int dy, std::vector<e_cell> cell);
        bool check_double_free_three(int x, int y, e_cell color);
        bool check_free_three(int x, int y, int ax, int ay, e_cell color);
        void unset_blocked_pos();
    
    public:
        Game(t_request &request);
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
        std::vector<int> get_interesting_pos();
        std::pair<int, int> compute_best_move(e_color color, int depth, int is_maxi, int alpha, int beta);
};