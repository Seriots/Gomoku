#pragma once
#include <httplib.h>
enum e_color {
    WHITESTONE,
    BLACKSTONE
};

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


void    r_game(const httplib::Request &req, httplib::Response &res);
void    r_end(const httplib::Request &req, httplib::Response &res);
void    r_action(const httplib::Request &req, httplib::Response &res);
void    r_ia(const httplib::Request &req, httplib::Response &res);
