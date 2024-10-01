#include <httplib.h>

#include "utils.hpp"
#include "request.hpp"

#include "Game.hpp"

void    r_game(const httplib::Request &req, httplib::Response &res) {
    (void)req;
    res.set_header("Access-Control-Allow-Origin", "*");
    std::string out = "{"+build_json_content({"game", "state"}, {"running", "winning"})+"}"; 
    res.set_content(out, "application/json");
}

void    r_action(const httplib::Request &req, httplib::Response &res) {
    
    t_request request;
    
    res.set_header("Access-Control-Allow-Origin", "*");

    request = create_new_request(req);

    std::cout << request.x << " " << request.y << " " << request.color << std::endl;
    if (request.pos < 0 || request.pos > 360) {
        res.set_content("{"+build_json_content({"error"}, {"outOfBound"})+"}", "application/json");
        return;
    }
    if (std::find(request.white.begin(), request.white.end(), request.pos) != request.white.end()
        || std::find(request.black.begin(), request.black.end(), request.pos) != request.black.end()
        || std::find(request.blocked.begin(), request.blocked.end(), request.pos) != request.blocked.end()) {
            res.set_content("{"+build_json_content({"error"}, {"occupied"})+"}", "application/json");
        return;
    }
    
    Game game(request.white, request.black);

    std::vector<int> blocked_list = game.get_blocked(request.color);
    std::vector<t_stone> added;
    std::vector<int> removed;
    

    added.push_back({request.pos, request.color == WHITESTONE ? "white" : "black"});
    for (size_t i = 0; i < blocked_list.size(); i++)
        added.push_back({blocked_list[i], "blocked"});
    
    //removed.push_back(rand() % 10);

    res.set_content(build_action_response(added, removed, {}, {}), "application/json");
}

void r_ia(const httplib::Request &req, httplib::Response &res) {
    t_request request;

    res.set_header("Access-Control-Allow-Origin", "*");
    
    request = create_new_ia_request(req);

    std::vector<t_stone> added;
    std::vector<int> removed;
    
    added.push_back({rand() % 361, request.color == WHITESTONE ? "white" : "black"});

    res.set_content(build_action_response(added, removed, {}, {}), "application/json");

}

void r_end(const httplib::Request &req, httplib::Response &res) {
    (void)req;
    (void)res;
    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_content("end", "text/plain");
}