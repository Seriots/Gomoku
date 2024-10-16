#pragma once

#include <string>
#include <vector>

#include "utils.hpp"
#include "Board.hpp"

#include "structs.hpp"

bool operator==(const t_data &a, const t_data &b);


class Game {
    private:
        Board                   _board;
        t_position              _center;
        std::map<e_dna, int>    _dna;
        t_request               _request;
        std::vector<int>        _interesting_pos;
        std::vector<int>        _blocked_pos;

        void init_dna();

        bool check_sequence(int x, int y, int dx, int dy, std::vector<e_cell> cell);
        bool check_double_free_three(int x, int y, e_cell color);
        bool check_free_three(int x, int y, int ax, int ay, e_cell color);
    
        bool                is_capturable(t_position &grid_pos, e_cell color, std::vector<int> *capture_spot);
        bool                check_win_by_capture();
        bool                check_win_by_alignement(int pos, e_cell color);
        bool                check_no_winner();
        std::vector<int>    get_capture_prevent_win_pos(int pos, e_cell color);
        bool is_in_grid(int x, int y);

    public:
        Game(t_request &request);
        Game(const Game &g);
        ~Game();

        void operator= (const Game &g);

        void set(int pos, e_cell cell);
        void set(std::vector<int> pos, e_cell cell);
        void unset(int pos);
        void unset(std::vector<int> pos);
        void unset_blocked_pos();

        Board get_board() const;

        std::vector<int> get_new_blocked_pos(e_color color);
        std::vector<int> get_captured(int pos);

        void print_board();

        int simple_heuristic(e_color color, int pos);
        //std::pair<int, int> compute_best_move(e_color color, int depth, bool is_maxi, int alpha, int beta);
        std::pair<int, int> minimax(int alpha, int beta, int depth, bool is_maxi, int next_pos, std::vector<int> &board);

        std::vector<t_direction_info>   compute_dirs_info(t_position &grid_pos, e_cell &my_color, e_cell &other_color);
        t_score_info                    compute_score_information(std::vector<t_direction_info> &dir_info);
        int                             compute_score(t_score_info &score_info, int &my_captured);
        int                             complex_heuristic(e_color color, int &pos);

        int                             full_simple_heuristic(e_color color);

        std::vector<int>    get_interesting_pos();
        t_endgame_info      check_end_game(int pos);
};
