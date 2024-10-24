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


enum e_valueDna {
    VDNA_ONE,
    VDNA_TWON3,
    VDNA_TWON2,
    VDNA_TWON1,
    VDNA_TWO,
    VDNA_THREEN2,
    VDNA_THREEN1,
    VDNA_THREE,
    VDNA_FOURN1,
    VDNA_FOUR,
    VDNA_THREEFREE,
    VDNA_FIVE,
    VDNA_POTENTIAL_CAPTURE,
    VDNA_EFFECTIVE_CAPTURE_0,
    VDNA_EFFECTIVE_CAPTURE_1,
    VDNA_EFFECTIVE_CAPTURE_2,
    VDNA_EFFECTIVE_CAPTURE_3,
};

enum e_sequenceDna {
    SDNA_NNNNN, // 0
    SDNA_NNNNM, // +1
    SDNA_NNNNY, // -1
    SDNA_NNNMN, // +1
    SDNA_NNNMM, // +2
    SDNA_NNNMY,
    SDNA_NNNYN, // -1
    SDNA_NNNYM,
    SDNA_NNNYY, // -2
    SDNA_NNMNN, // +1
    SDNA_NNMNM, // +2e
    SDNA_NNMNY,
    SDNA_NNMMN, // +2
    SDNA_NNMMM, // +3
    SDNA_NNMMY, // -c
    SDNA_NNMYN, 
    SDNA_NNMYM,
    SDNA_NNMYY,
    SDNA_NNYNN, // -1
    SDNA_NNYNM,
    SDNA_NNYNY, // -2e
    SDNA_NNYMN,
    SDNA_NNYMM,
    SDNA_NNYMY,
    SDNA_NNYYN, // -2
    SDNA_NNYYM, // +c
    SDNA_NNYYY, // -3
    SDNA_NMNNN, // +1
    SDNA_NMNNM, // +2e
    SDNA_NMNNY, 
    SDNA_NMNMN, // +2e
    SDNA_NMNMM, // +3e
    SDNA_NMNMY,
    SDNA_NMNYN,
    SDNA_NMNYM,
    SDNA_NMNYY,
    SDNA_NMMNN, // +2
    SDNA_NMMNM, // +3e
    SDNA_NMMNY, 
    SDNA_NMMMN, // +3
    SDNA_NMMMM, // +4
    SDNA_NMMMY,
    SDNA_NMMYN, // -c
    SDNA_NMMYM, // -c
    SDNA_NMMYY, // -c
    SDNA_NMYNN, 
    SDNA_NMYNM,
    SDNA_NMYNY,
    SDNA_NMYMN,
    SDNA_NMYMM,
    SDNA_NMYMY,
    SDNA_NMYYN, // c
    SDNA_NMYYM,
    SDNA_NMYYY,
    SDNA_NYNNN, // -1
    SDNA_NYNNM, 
    SDNA_NYNNY, // -2e
    SDNA_NYNMN, 
    SDNA_NYNMM,
    SDNA_NYNMY, 
    SDNA_NYNYN, // -2e
    SDNA_NYNYM,
    SDNA_NYNYY, // -3e
    SDNA_NYMNN, 
    SDNA_NYMNM,
    SDNA_NYMNY,
    SDNA_NYMMN, // -c
    SDNA_NYMMM,
    SDNA_NYMMY, 
    SDNA_NYMYN,
    SDNA_NYMYM,
    SDNA_NYMYY,
    SDNA_NYYNN, // -2
    SDNA_NYYNM, 
    SDNA_NYYNY, // -3e
    SDNA_NYYMN, // c
    SDNA_NYYMM, // c
    SDNA_NYYMY, // c
    SDNA_NYYYN, // -3
    SDNA_NYYYM,
    SDNA_NYYYY, // -4
    SDNA_MNNNN, // +1
    SDNA_MNNNM, // +2e+
    SDNA_MNNNY,
    SDNA_MNNMN, // +2e
    SDNA_MNNMM, // +3e
    SDNA_MNNMY,
    SDNA_MNNYN,
    SDNA_MNNYM,
    SDNA_MNNYY,
    SDNA_MNMNN, // +2e
    SDNA_MNMNM, // +3e
    SDNA_MNMNY,
    SDNA_MNMMN, // +3e
    SDNA_MNMMM, // +4e
    SDNA_MNMMY, // -c
    SDNA_MNMYN,
    SDNA_MNMYM,
    SDNA_MNMYY,
    SDNA_MNYNN,
    SDNA_MNYNM,
    SDNA_MNYNY,
    SDNA_MNYMN,
    SDNA_MNYMM,
    SDNA_MNYMY,
    SDNA_MNYYN,
    SDNA_MNYYM, // +c
    SDNA_MNYYY,
    SDNA_MMNNN, // +2
    SDNA_MMNNM, // +3e
    SDNA_MMNNY,
    SDNA_MMNMN, // +3e
    SDNA_MMNMM, // +4e
    SDNA_MMNMY, 
    SDNA_MMNYN,
    SDNA_MMNYM,
    SDNA_MMNYY,
    SDNA_MMMNN, // +3
    SDNA_MMMNM, // +4e
    SDNA_MMMNY, 
    SDNA_MMMMN, // +4
    SDNA_MMMMM, // +5
    SDNA_MMMMY,
    SDNA_MMMYN,
    SDNA_MMMYM,
    SDNA_MMMYY,
    SDNA_MMYNN,
    SDNA_MMYNM,
    SDNA_MMYNY,
    SDNA_MMYMN,
    SDNA_MMYMM,
    SDNA_MMYMY,
    SDNA_MMYYN, // +c
    SDNA_MMYYM,
    SDNA_MMYYY,
    SDNA_MYNNN,
    SDNA_MYNNM,
    SDNA_MYNNY,
    SDNA_MYNMN,
    SDNA_MYNMM,
    SDNA_MYNMY,
    SDNA_MYNYN,
    SDNA_MYNYM,
    SDNA_MYNYY,
    SDNA_MYMNN,
    SDNA_MYMNM,
    SDNA_MYMNY,
    SDNA_MYMMN, // -c
    SDNA_MYMMM,
    SDNA_MYMMY,
    SDNA_MYMYN,
    SDNA_MYMYM,
    SDNA_MYMYY,
    SDNA_MYYNN, // +c
    SDNA_MYYNM, // +c
    SDNA_MYYNY, // +c
    SDNA_MYYMN,
    SDNA_MYYMM,
    SDNA_MYYMY,
    SDNA_MYYYN,
    SDNA_MYYYM,
    SDNA_MYYYY,
    SDNA_YNNNN, // -1
    SDNA_YNNNM,
    SDNA_YNNNY, // -2e+
    SDNA_YNNMN,
    SDNA_YNNMM,
    SDNA_YNNMY,
    SDNA_YNNYN, // -2e
    SDNA_YNNYM,
    SDNA_YNNYY, // -3e
    SDNA_YNMNN,
    SDNA_YNMNM,
    SDNA_YNMNY,
    SDNA_YNMMN,
    SDNA_YNMMM,
    SDNA_YNMMY, // -c
    SDNA_YNMYN, 
    SDNA_YNMYM,
    SDNA_YNMYY,
    SDNA_YNYNN, // -2e
    SDNA_YNYNM,
    SDNA_YNYNY, // -3e
    SDNA_YNYMN,
    SDNA_YNYMM,
    SDNA_YNYMY,
    SDNA_YNYYN, // -3e
    SDNA_YNYYM, // +c
    SDNA_YNYYY, // -4e
    SDNA_YMNNN,
    SDNA_YMNNM,
    SDNA_YMNNY,
    SDNA_YMNMN,
    SDNA_YMNMM,
    SDNA_YMNMY,
    SDNA_YMNYN,
    SDNA_YMNYM,
    SDNA_YMNYY,
    SDNA_YMMNN, // -c
    SDNA_YMMNM, // -c
    SDNA_YMMNY, // -c
    SDNA_YMMMN,
    SDNA_YMMMM,
    SDNA_YMMMY,
    SDNA_YMMYN,
    SDNA_YMMYM,
    SDNA_YMMYY,
    SDNA_YMYNN,
    SDNA_YMYNM,
    SDNA_YMYNY,
    SDNA_YMYMN,
    SDNA_YMYMM,
    SDNA_YMYMY,
    SDNA_YMYYN, // c
    SDNA_YMYYM,
    SDNA_YMYYY,
    SDNA_YYNNN, // -2
    SDNA_YYNNM,
    SDNA_YYNNY, // -3e
    SDNA_YYNMN,
    SDNA_YYNMM,
    SDNA_YYNMY,
    SDNA_YYNYN, // -3e
    SDNA_YYNYM,
    SDNA_YYNYY, // -4e
    SDNA_YYMNN,
    SDNA_YYMNM,
    SDNA_YYMNY,
    SDNA_YYMMN, // -c
    SDNA_YYMMM,
    SDNA_YYMMY,
    SDNA_YYMYN,
    SDNA_YYMYM,
    SDNA_YYMYY,
    SDNA_YYYNN, // -3
    SDNA_YYYNM,
    SDNA_YYYNY, // -4e
    SDNA_YYYMN,
    SDNA_YYYMM,
    SDNA_YYYMY,
    SDNA_YYYYN, // -4
    SDNA_YYYYM,
    SDNA_YYYYY, // -5 == 3 * 3 * 3 * 3 * 3 -1 = 242
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
    int any_alignement;
    int align_five;
    int free_four;
    int free_three;
    int capture;
    int block_win;
    int block_free_four;
    int block_free_three;
    int block_capture;
    int setup_capture;
    int is_capturable;
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
    std::vector<int>    allowed;
    int                 white_captured;
    int                 black_captured;
}   t_request;