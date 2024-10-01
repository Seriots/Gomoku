#pragma once

enum e_color {
    WHITESTONE,
    BLACKSTONE
};

typedef struct s_request {
    int                 pos;
    int                 x;
    int                 y;
    e_color             color;
    std::vector<int>    white;
    std::vector<int>    black;
} t_request;


void    r_game(const httplib::Request &req, httplib::Response &res);
void    r_end(const httplib::Request &req, httplib::Response &res);
void    r_action(const httplib::Request &req, httplib::Response &res);
