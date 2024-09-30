#include <httplib.h>

#include "utils.hpp"

#include "Game.hpp"

void    r_game(const httplib::Request &req, httplib::Response &res) {
    (void)req;
    (void)res;
    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_content("game", "text/plain");
}

void    r_action(const httplib::Request &req, httplib::Response &res) {
    int pos = std::stoi(req.path_params.at("pos"));
    int x = (pos) / 19;
    int y = (pos) % 19;
    std::string color = req.path_params.at("color");
    std::vector<int> white = parse_board_input(req.path_params.at("white"));
    std::vector<int> black = parse_board_input(req.path_params.at("black"));
    std::vector<int> blocked = parse_board_input(req.path_params.at("blocked"));

    std::cout << x << " " << y << " " << color << std::endl;
    if (pos < 0 || pos > 361 || (color != "b" && color != "w")) {
        res.set_content("error", "text/plain");
        return;
    }
    if (std::find(white.begin(), white.end(), pos) != white.end()
        || std::find(black.begin(), black.end(), pos) != black.end()
        || std::find(blocked.begin(), blocked.end(), pos) != blocked.end()) {
            res.set_content("error", "text/plain");
        return;
    }
    
    res.set_header("Access-Control-Allow-Origin", "*");

    if (color == "w") {
        res.set_content("white", "text/plain");
    } else {
        res.set_content("black", "text/plain");
    }
}

void r_end(const httplib::Request &req, httplib::Response &res) {
    (void)req;
    (void)res;
    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_content("end", "text/plain");
}