#pragma once

#include <vector>
#include <string>

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

enum e_cell {
    WHITE,
    BLACK,
    BLOCKED,
    NONE,
};

enum e_color {
    WHITESTONE,
    BLACKSTONE
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


typedef struct s_position {
    int x;
    int y;
} t_position;

typedef struct s_stone {
    int         pos;
    std::string color;
}   t_stone;

typedef struct s_request {
    int                 pos;
    int                 x;
    int                 y;
    e_color             color;
    std::vector<int>    white;
    std::vector<int>    black;
    std::vector<int>    blocked;
    int                 white_captured;
    int                 black_captured;
}   t_request;