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

typedef struct s_data {
    int pos;
    e_cell color;
} t_data;

typedef struct s_direction_info {
    int my_free_alignement;
    int my_real_alignement;
    int other_real_alignement;
    bool capture;
    bool setup_capture;
    bool is_capturable;
    bool block_capture;
} t_direction_info;

typedef struct s_score_info {
    int any_alignement = 0;
    int align_five = 0;
    int free_four = 0;
    int free_three = 0;
    int capture = 0;
    int block_win = 0;
    int block_free_four = 0;
    int block_free_three = 0;
    int block_capture = 0;
    int setup_capture = 0;
    int is_capturable = 0;
} t_score_info;

typedef struct s_endgame_info {
    e_color             color;
    bool                win_by_capture;
    bool                win_by_alignement;
    bool                no_winner;
    std::vector<int>    capture_prevent_win_pos;
} t_endgame_info;

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
    
        bool                check_win_by_capture();
        bool                check_win_by_alignement(int pos, e_color color);
        bool                check_no_winner();
        std::vector<int>    get_capture_prevent_win_pos();
    
    public:
        Game(t_request &request);
        Game(const Game &g);
        ~Game();

        void operator= (const Game &g);

        void set(int pos, e_cell cell);
        void set(std::vector<int> pos, e_cell cell);
        void unset(std::vector<int> pos);
        void unset_blocked_pos();

        Board get_board() const;

        std::vector<int> get_new_blocked_pos(e_color color);
        std::vector<int> get_captured(int pos);

        void print_board();

        int simple_heuristic(e_color color, int pos);
        //std::pair<int, int> compute_best_move(e_color color, int depth, bool is_maxi, int alpha, int beta);
        std::pair<int, int> minimax(int alpha, int beta, int depth, bool is_maxi, int next_pos);

        std::vector<t_direction_info>   compute_dirs_info(t_position &grid_pos, e_cell &my_color, e_cell &other_color);
        t_score_info                    compute_score_information(std::vector<t_direction_info> &dir_info);
        int                             compute_score(t_score_info &score_info, int &my_captured);
        int                             complex_heuristic(e_color color, int &pos);
        
        int                             full_simple_heuristic(e_color color);
        
        std::vector<int>    get_interesting_pos();
        std::pair<int, int> compute_best_move(e_color color, int depth, bool is_maxi, int alpha, int beta);

        t_endgame_info      check_end_game(int pos);
};
