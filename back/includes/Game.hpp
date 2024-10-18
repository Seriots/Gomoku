#pragma once

#include <string>
#include <vector>

#include "utils.hpp"
#include "Board.hpp"

#include "structs.hpp"

class Game {
    private:
        Board                           _board;
        t_position                      _center;
        std::map<e_dna, int>            _dna;
        t_request                       _request;
        std::vector<int>                _interesting_pos;
        std::vector<int>                _blocked_pos;
        std::map<e_sequenceDna, int>    _sequenceDna;

        void                            init_test_board();
    public:
        /* ******* Game core ******* */
        Game();
        Game(t_request &request);
        Game(const Game &g);
        ~Game();

        void operator=(const Game &g);
        void set(int pos, e_cell cell);
        void set(std::vector<int> pos, e_cell cell);
        void unset(int pos);
        void unset(std::vector<int> pos);
        void unset_blocked_pos();
        Board get_board() const;


        /* ******* Game utils ******* */
        void                            init_dna();
        void                            init_sequenceDna();
        bool                            is_in_grid(int x, int y);
        bool                            check_free_three(int x, int y, int ax, int ay, e_cell color);
        bool                            check_double_free_three(int x, int y, e_cell color);
        bool                            check_sequence(int x, int y, int dx, int dy, std::vector<e_cell> cell);
        std::vector<int>                get_new_blocked_pos(e_color color);
        std::vector<int>                get_captured(int pos);
        std::vector<int>                get_interesting_pos();
        void                            sort_interesting_pos(e_color const &color);
        void                            print_board();
        std::map<e_cell, std::vector<int> > get_all_positions_stone();


        /* ******* Game end ******* */
        bool                            check_win_by_capture();
        bool                            check_win_by_alignement(int pos, e_cell color);
        bool                            is_capturable(t_position &grid_pos, e_cell color, std::vector<int> *capture_spot);
        std::vector<int>                get_capture_prevent_win_pos(int pos, e_cell color);
        bool                            check_no_winner();
        t_endgame_info                  check_end_game(int pos);

        /* ******* Game heuristic ******* */
        std::vector<t_direction_info>   compute_dirs_info(t_position &grid_pos, e_cell &my_color, e_cell &other_color);
        t_score_info                    compute_score_information(std::vector<t_direction_info> &dir_info);
        int                             compute_score(t_score_info &score_info, int &my_captured);
        int                             simple_heuristic(e_color color, int pos);
        int                             complex_heuristic(e_color color, int &pos);
        int                             full_simple_heuristic(e_color color);
        int                             board_complex_heuristic(e_color color);
        /* ******* Game minimax ******* */
        std::pair<int, int>             minimax(int alpha, int beta, int depth, bool is_maxi, int next_pos, std::vector<int> &board);
};
