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

    int score = game.board_complex_heuristic(BLACKSTONE, 0, 0);
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

    t_endgame_info endgame_info = game.check_end_game(request.pos, removed.size(), request.color);

    res.set_content(build_action_response(added, removed, endgame_info, {}, {}), "application/json"); // everything is send in a nicely formated json
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
    game.init_interesting_pos(request.color, request.allowed);

    // create board

    game.set_depth(6);
    std::vector<int> threshold_by_layer = generate_thresholds(game.get_depth(), 60000, 10, 3);
    game.set_threshold(threshold_by_layer);


    auto start_time = std::chrono::high_resolution_clock::now();
    
    int pos = game.fdNegamax({INT_MIN, INT_MAX, game.get_depth(), 1}, (t_captureCount){request.white_capture, request.black_capture});


    auto end_time = std::chrono::high_resolution_clock::now();

    
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << "Time: " << time << std::endl << std::endl;
    

    game.set(pos, color_to_cell(request.color));

    removed = game.get_captured(pos);

    game.unset(removed);

    blocked_list = game.get_new_blocked_pos(request.color == WHITESTONE ? BLACKSTONE : WHITESTONE);

    added.push_back({pos, request.color == WHITESTONE ? "white" : "black"});
    for (size_t i = 0; i < blocked_list.size(); i++)
        added.push_back({blocked_list[i], "blocked"});

    t_endgame_info endgame_info = game.check_end_game(pos, removed.size(), request.color);

    res.set_content(build_action_response(added, removed, endgame_info, {"time", "depthSearch"}, {std::to_string(time), std::to_string(game.get_depth())}), "application/json");
}

void r_ia_with_dna(const httplib::Request &req, httplib::Response &res) {
    t_request               request;
    std::vector<t_stone>    added;
    std::vector<int>        removed;
    std::vector<int>        blocked_list;
    std::vector<int>        dna;
    t_endgame_info          endgame_info;


    res.set_header("Access-Control-Allow-Origin", "*"); // prevent CORS problems

    request = create_new_ia_request(req);

    dna = get_request_dna(req);

    Game game(request, dna); // instantiate game object with the request

    if (request.color == WHITESTONE) {
        if (dna[2] > 45 && dna[2] < 50 && request.black.size() % 4 == 0) {
            int pos = 360;
            while (std::find(request.white.begin(), request.white.end(), pos) != request.white.end() ||
                   std::find(request.black.begin(), request.black.end(), pos) != request.black.end()) {
                pos--;
            }
            added.push_back({pos, "white"});
        } else if (dna[1] > 25 && dna[1] < 30) {
            int pos = 0;
            while (std::find(request.white.begin(), request.white.end(), pos) != request.white.end() ||
                   std::find(request.black.begin(), request.black.end(), pos) != request.black.end()) {
                pos++;
            }
            added.push_back({pos, "white"});
        } else {
            while (true) {
                int pos = rand() % 361;
                if (std::find(request.white.begin(), request.white.end(), pos) == request.white.end() &&
                    std::find(request.black.begin(), request.black.end(), pos) == request.black.end()) {
                    added.push_back({pos, "black"});
                    break;
                }
            }
        }
    } else {
        if (dna[2] > 45 && dna[2] < 50 && request.white.size() % 4 == 0) {
            int pos = 0;
            while (std::find(request.white.begin(), request.white.end(), pos) != request.white.end() ||
                   std::find(request.black.begin(), request.black.end(), pos) != request.black.end()) {
                pos++;
            }
            added.push_back({pos, "black"});
        } else if (dna[1] > 25 && dna[1] < 30) {
            int pos = 360;
            while (std::find(request.white.begin(), request.white.end(), pos) != request.white.end() ||
                   std::find(request.black.begin(), request.black.end(), pos) != request.black.end()) {
                pos--;
            }
            added.push_back({pos, "black"});
        } else {
            while (true) {
                int pos = rand() % 361;
                if (std::find(request.white.begin(), request.white.end(), pos) == request.white.end() &&
                    std::find(request.black.begin(), request.black.end(), pos) == request.black.end()) {
                    added.push_back({pos, "black"});
                    break;
                }
            }
        }
    }

    game.set(added[0].pos, request.color == WHITESTONE ? WHITE : BLACK);

    endgame_info = game.check_end_game(added[0].pos, removed.size(), request.color);

    removed.push_back(1);
    removed.push_back(2);
    added.push_back({5, "black"});

    res.set_content(build_action_response(added, removed, endgame_info, {}, {}), "application/json");
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
