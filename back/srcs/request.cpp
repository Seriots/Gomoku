#include <httplib.h>

#include "utils.hpp"
#include "request.hpp"

#include "Game.hpp"

void    r_game(const httplib::Request &req, httplib::Response &res) {
    (void)req;
    res.set_header("Access-Control-Allow-Origin", "*");
    std::string out = build_json_content({"game", "state"}, {"running", "winning"}); 
    res.set_content(out, "application/json");
}

void    r_action(const httplib::Request &req, httplib::Response &res) {
    
    t_request request;
    
    res.set_header("Access-Control-Allow-Origin", "*");

    request = create_new_request(req);

    std::cout << request.x << " " << request.y << " " << request.color << std::endl;
    if (request.pos < 0 || request.pos > 360) {
        res.set_content(build_json_content({"error"}, {"outOfBound"}), "application/json");
        return;
    }
    if (std::find(request.white.begin(), request.white.end(), request.pos) != request.white.end()
        || std::find(request.black.begin(), request.black.end(), request.pos) != request.black.end()) {
            res.set_content(build_json_content({"error"}, {"occupied"}), "application/json");
        return;
    }
    

    if (request.color == WHITESTONE) {
        res.set_content("white", "application/json");
    } else {
        res.set_content("black", "application/json");
    }
}

void r_end(const httplib::Request &req, httplib::Response &res) {
    (void)req;
    (void)res;
    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_content("end", "text/plain");
}