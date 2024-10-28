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

    std::cout << "Before white check end" << std::endl;
    t_endgame_info endgame_info = game.check_end_game(request.pos);
    std::cout << "After white check end" << std::endl;

    res.set_content(build_action_response(added, removed, endgame_info, {}, {}), "application/json"); // everything is send in a nicely formated json
}

void display_board(std::vector<int> &board, Game &game) {

    std::vector<int> interesting_pos = game.getter_interesting_pos();

    for (int y = 0; y < 19; y++) {
        for (int x = 0; x < 19; x++) {
            float displayColor;

            std::vector<int>::iterator it = std::find(interesting_pos.begin(), interesting_pos.end(), x + y * 19);

            if (it == interesting_pos.end())
                displayColor = 0;
            else
                displayColor = 1.0 - ((float)(it - interesting_pos.begin()) / (float)interesting_pos.size());
            if (displayColor > 0.99)
                std::cout << "\033[0;35m"; // magenta
            else if (displayColor > 0.9)
                std::cout << "\033[0;31m"; // red
            else if (displayColor > 0.8)
                std::cout << "\033[0;33m"; // yellow
            else if (displayColor > 0.7)
                std::cout << "\033[0;32m"; // green
            else if (displayColor > 0.35)
                std::cout << "\033[0;34m"; // blue
            else
                std::cout << "\033[0;36m"; // cyan

            if (board[x + y * 19] != -1)
                std::cout << std::setw(5) << std::setfill(' ') << board[x + y * 19] << " ";
            else if (game.get_board().get(x, y).get() == WHITE)
                std::cout << "ooooo ";
            else if (game.get_board().get(x, y).get() == BLACK)
                std::cout << "***** ";
            else if (game.get_board().get(x, y).get() == BLOCKED)
                std::cout << "xxxxx ";
            else
                std::cout << "----- ";
            std::cout << "\033[0m";
        }
        std::cout << std::endl;
    }
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
    game.init_interesting_pos(request.color);

    // create board
    std::vector<int> board1, board2, board3;
    for (int i = 0; i < 19*19; i++)
        board2.push_back(-1);

    game.set_depth(4);
    std::vector<int> threshold_by_layer = generate_thresholds(game.get_depth(), 5000, 10, 2);
    game.set_threshold(threshold_by_layer);

    // display board
    //for (int y = 0; y < 19; y++) {
    //    for (int x = 0; x < 19; x++) {
    //        if (board[x + y * 19] != -1)
    //            std::cout << std::setw(4) << std::setfill('0') << board[x + y * 19] << " ";
    //        else
    //            std::cout << "---- ";
    //    }
    //    std::cout << std::endl;
    //}


    std::cout << "Time: " << time << std::endl << std::endl;
    auto start_time = std::chrono::high_resolution_clock::now();
    int pos = game.negamax(INT_MIN, INT_MAX, game.get_depth(), 1, -1, board2, std::chrono::steady_clock::now(), request.white_capture, request.black_capture).first;
    auto end_time = std::chrono::high_resolution_clock::now();

    /* logs */
    for (size_t i = 0; i < threshold_by_layer.size(); i++)
        std::cout << "depth " << i + 1  << ": " << threshold_by_layer[i] << std::endl;
    game.set_threshold(threshold_by_layer);
    
    std::cout << "Negamax: " << pos << " - " << pos % 19 << " " << pos / 19 << std::endl;
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << "Time: " << time << std::endl << std::endl;
    display_board(board2, game);

    game.set(pos, color_to_cell(request.color));

    removed = game.get_captured(pos);

    game.unset(removed);

    blocked_list = game.get_new_blocked_pos(request.color == WHITESTONE ? BLACKSTONE : WHITESTONE);

    added.push_back({pos, request.color == WHITESTONE ? "white" : "black"});
    for (size_t i = 0; i < blocked_list.size(); i++)
        added.push_back({blocked_list[i], "blocked"});

    t_endgame_info endgame_info = game.check_end_game(pos, removed.size(), request.color);

    res.set_content(build_action_response(added, removed, endgame_info, {"time", "depthSearch"}, {std::to_string(time), std::to_string(1)}), "application/json");
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
