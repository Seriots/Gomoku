#include <httplib.h>

#include "utils.hpp"
#include "request.hpp"

#include "Game.hpp"

/*
    Basic test request, does nothing nice 
*/
void    r_game(const httplib::Request &req, httplib::Response &res) {
    (void)req;
    res.set_header("Access-Control-Allow-Origin", "*");
    std::string out = "{"+build_json_content({"game", "state"}, {"running", "winning"})+"}"; 
    res.set_content(out, "application/json");
}

/*
    Request to try to place a stone on the board
    The request must contain the following parameters:
    - pos: the position where the stone should be placed
    - color: the color of the stone
    - white: the list of white stones on the board
    - black: the list of black stones on the board
    - blocked: the list of blocked positions on the board
*/
void    r_action(const httplib::Request &req, httplib::Response &res) {
    
    t_request               request;
    Game                    game;
    std::vector<t_stone>    added;
    std::vector<int>        removed;
    std::vector<int>        blocked_list;
    
    res.set_header("Access-Control-Allow-Origin", "*");

    request = create_new_request(req);

    if (check_error_request(request, res))
        return;
    
    game = Game(request.white, request.black);
    
    game.set(request.pos, request.color == WHITESTONE ? WHITE : BLACK);
    game.print_board();

    removed = game.get_captured(request.pos);

    // check if you captured something

    added.push_back({request.pos, request.color == WHITESTONE ? "white" : "black"});
    for (size_t i = 0; i < blocked_list.size(); i++)
        added.push_back({blocked_list[i], "blocked"});
    
    //removed.push_back(rand() % 10);
    blocked_list = game.get_blocked(request.color);
    
    //everything is send in a nicely formated json
    res.set_content(build_action_response(added, removed, {}, {}), "application/json");
}

/*
    Request to try to place a stone on the board
    The request must contain the following parameters:
    - color: the color of the stone
    - white: the list of white stones on the board
    - black: the list of black stones on the board
*/
void r_ia(const httplib::Request &req, httplib::Response &res) {
    t_request               request;
    std::vector<t_stone>    added;
    std::vector<int>        removed;

    res.set_header("Access-Control-Allow-Origin", "*");
    
    request = create_new_ia_request(req);

    int pos = rand() % 361;
    while (std::find(request.white.begin(), request.white.end(), pos) != request.white.end()
        || std::find(request.black.begin(), request.black.end(), pos) != request.black.end()) {
        pos = rand() % 361;
    }

    added.push_back({pos, request.color == WHITESTONE ? "white" : "black"});

    res.set_content(build_action_response(added, removed, {}, {}), "application/json");
}

/*
    Request to end the game
*/
void r_end(const httplib::Request &req, httplib::Response &res) {
    (void)req;
    (void)res;
    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_content("end", "text/plain");
}