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
    game.init_interesting_pos();



    game.get_new_blocked_pos(request.color == WHITESTONE ? BLACKSTONE : WHITESTONE);

    // create board
    std::vector<int> board1, board2;
    for (int i = 0; i < 19*19; i++) {
        board1.push_back(-1);
        board2.push_back(-1);
    }

    game._transposition_table.clear();
    auto start_time_1 = std::chrono::high_resolution_clock::now();
    int pos1 = game.minimax(INT_MIN, INT_MAX, 5, true, -1, board1).first;
    auto end_time_1 = std::chrono::high_resolution_clock::now();

    game._transposition_table.clear();
    auto start_time_2 = std::chrono::high_resolution_clock::now();
    int pos2 = game.negascout(INT_MIN, INT_MAX, 5, true, -1, board2).first;
    auto end_time_2 = std::chrono::high_resolution_clock::now();

    std::cout << "Minimax: " << pos1 << std::endl;
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time_1 - start_time_1).count() << std::endl << std::endl;
    // display board 1
    for (int y = 0; y < 19; y++) {
        for (int x = 0; x < 19; x++) {
            if (board1[x + y * 19] != -1)
                std::cout << std::setw(4) << std::setfill(' ') << board1[x + y * 19] << " ";
            else
                std::cout << "---- ";
        }
        std::cout << std::endl;
    }

    std::cout << "Negascout: " << pos2 << std::endl;
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time_2 - start_time_2).count() << std::endl << std::endl;
    // display board 2
    for (int y = 0; y < 19; y++) {
        for (int x = 0; x < 19; x++) {
            if (board2[x + y * 19] != -1)
                std::cout << std::setw(4) << std::setfill(' ') << board2[x + y * 19] << " ";
            else
                std::cout << "---- ";
        }
        std::cout << std::endl;
    }

    // game.set(request.blocked, BLOCKED);


    game.set(pos2, request.color == WHITESTONE ? WHITE : BLACK);

    removed = game.get_captured(pos2);

    game.unset(removed);

    blocked_list = game.get_new_blocked_pos(request.color == WHITESTONE ? BLACKSTONE : WHITESTONE);

    added.push_back({pos2, request.color == WHITESTONE ? "white" : "black"});
    for (size_t i = 0; i < blocked_list.size(); i++)
        added.push_back({blocked_list[i], "blocked"});

    t_endgame_info endgame_info = game.check_end_game(pos2);

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
