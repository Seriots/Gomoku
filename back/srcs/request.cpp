#include <httplib.h>
#include <time.h>

#include "utils.hpp"
#include "request.hpp"

#include "Game.hpp"

/*
    Basic test request, does nothing nice
*/
void    r_game(const httplib::Request &req, httplib::Response &res) {
    (void)req;
    res.set_header("Access-Control-Allow-Origin", "*");

    Game game;
    
    int score = game.board_complex_heuristic(BLACKSTONE);
    std::cout << score << std::endl;
    res.set_content("{"+ std::to_string(score) + "}", "application/json");
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

    t_request               request;        // the request structure
    std::vector<t_stone>    added;          // the list of added stones returned
    std::vector<int>        removed;        // the list of removed stones returned
    std::vector<int>        blocked_list;   // the list of blocked positions returned

    res.set_header("Access-Control-Allow-Origin", "*"); // prevent CORS errors

    request = create_new_request(req);

    if (check_error_request(request, res)) // check if the request is valid pos on NONE pos and prevent out of bound pos
        return;

    Game game(request); // instantiate game object with the request

    // game.set(request.blocked, BLOCKED);

    game.set(request.pos, request.color == WHITESTONE ? WHITE : BLACK);
    // game.print_board();

    removed = game.get_captured(request.pos);
    game.unset(removed);

    blocked_list = game.get_new_blocked_pos(request.color == WHITESTONE ? BLACKSTONE : WHITESTONE);

    added.push_back({request.pos, request.color == WHITESTONE ? "white" : "black"});
    for (size_t i = 0; i < blocked_list.size(); i++)
        added.push_back({blocked_list[i], "blocked"});

    t_endgame_info endgame_info = game.check_end_game(request.pos);

    res.set_content(build_action_response(added, removed, endgame_info), "application/json"); // everything is send in a nicely formated json
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
    std::vector<int>        blocked_list;

    res.set_header("Access-Control-Allow-Origin", "*"); // prevent CORS problems

    request = create_new_ia_request(req);

    Game game(request); // instantiate game object with the request

    game.get_new_blocked_pos(request.color == WHITESTONE ? BLACKSTONE : WHITESTONE);
    auto start_time = std::chrono::high_resolution_clock::now();

    // create board
    std::vector<int> board;
    for (int i = 0; i < 19*19; i++)
        board.push_back(-1);

    int pos = game.minimax(INT_MIN, INT_MAX, 1, true, -1, board).first;

    // display board
    for (int y = 0; y < 19; y++) {
        for (int x = 0; x < 19; x++) {
            if (board[x + y * 19] != -1)
                std::cout << std::setw(4) << std::setfill('0') << board[x + y * 19] << " ";
            else
                std::cout << "---- ";
        }
        std::cout << std::endl;
    }
    auto end_time = std::chrono::high_resolution_clock::now();

    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << std::endl << std::endl;

    // game.set(request.blocked, BLOCKED);


    game.set(pos, request.color == WHITESTONE ? WHITE : BLACK);

    removed = game.get_captured(pos);

    game.unset(removed);

    blocked_list = game.get_new_blocked_pos(request.color == WHITESTONE ? BLACKSTONE : WHITESTONE);

    added.push_back({pos, request.color == WHITESTONE ? "white" : "black"});
    for (size_t i = 0; i < blocked_list.size(); i++)
        added.push_back({blocked_list[i], "blocked"});

    t_endgame_info endgame_info = game.check_end_game(pos);

    res.set_content(build_action_response(added, removed, endgame_info), "application/json");
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
