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
        std::map<e_sequenceDna, int>    _sequenceDna;
        std::map<e_valueDna, int>       _valuesDna;
        int                             _depth;
        std::vector<int>                _threshold;

        void                            init_test_board();
    public:
        /* ******* Game core ******* */
        std::unordered_map<size_t, int> _transposition_table;
        Game();
        Game(t_request &request);
        Game(t_request &request, std::vector<int> &dna);
        Game(const Game &g);
        ~Game();

        void operator=(const Game &g);
        void set(int pos, e_cell cell);
        void set(std::vector<int> pos, e_cell cell);
        void unset(int pos);
        void unset(std::vector<int> pos);
        Board get_board() const;
        std::vector<int> getter_interesting_pos() const;
        void init_interesting_pos(e_color color, std::vector<int> allowed_pos);
        void set_depth(int depth);
        void set_threshold(std::vector<int> threshold);
        int get_depth() const;


        /* ******* Game utils ******* */
        void                            init_dna();
        void                            init_sequenceDna(std::vector<int> *dna = NULL);
        bool                            is_in_grid(int x, int y);
        bool                            check_free_three(int x, int y, int ax, int ay, e_cell color);
        bool                            check_double_free_three(int x, int y, e_cell color);
        bool                            check_sequence(int x, int y, int dx, int dy, std::vector<e_cell> cell);
        std::vector<int>                get_new_blocked_pos(e_color color);
        std::vector<int>                get_captured(int pos, e_color color);
        std::vector<int>                get_interesting_pos();
        void                            sort_interesting_pos(e_color const &color, std::vector<int> &vec, t_captureCount &capture);
        void                            print_board();
        std::map<e_cell, std::vector<int> > get_all_positions_stone();
        bool                                is_something_near(int x, int y);
        e_color                             swap_choice(int const &white_capture, int const &black_capture);





        /* ******* Game end ******* */
        bool                            check_win_by_capture(size_t captured, e_color color);
        bool                            check_win_by_alignement(int pos, e_cell color);
        bool                            is_capturable(t_position &grid_pos, e_cell color, std::vector<int> *capture_spot);
        std::vector<int>                get_capture_prevent_win_pos(int pos, e_cell color);
        bool                            check_no_winner();
        t_endgame_info                  check_end_game(int pos, size_t captured, e_color color);

        /* ******* Game heuristic ******* */
        //t_score_info                    compute_dirs_info(t_position &grid_pos, e_cell &my_color, e_cell &other_color);
        std::vector<t_direction_info>   compute_dirs_info(t_position &grid_pos, e_cell &my_color, e_cell &other_color);
        t_score_info                    compute_score_information(std::vector<t_direction_info> &dir_info);
        int                             compute_score(t_score_info &score_info, int &my_captured);
        int                             add_capture_score(int current_capture);
        int                             simple_heuristic(e_color color, int pos);
        int                             complex_heuristic(e_color color, int &pos);
        int                             score_heuristic(e_color color, int pos, t_captureCount capture) const;
        int                             full_simple_heuristic(e_color color);
        int                             board_complex_heuristic(e_color color, int new_white_capture, int new_black_capture);
        /* ******* Game minimax ******* */
        void                            display_negamax_board(std::vector<int> &board);
        int                             fdNegamax(t_negamaxInformation info, t_captureCount capture);
        int                             negamax(t_negamaxInformation info, t_captureCount capture, int currPos);

        bool                            is_already_computed(size_t board_hash) const;
};
