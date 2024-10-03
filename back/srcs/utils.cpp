#include <httplib.h>

#include <string>
#include <vector>

#include "request.hpp"
#include "utils.hpp"

/*
    Check if the request is valid
    @param request: the request to check
    @param res: the response to send if the request is invalid
    @return true if the request is invalid, false otherwise
*/
bool check_error_request(t_request &request,  httplib::Response &res) {
    if (request.pos < 0 || request.pos >= 361) {
        res.set_content("{"+build_json_content({"error"}, {"outOfBound"})+"}", "application/json");
        return true;
    }
    if (std::find(request.white.begin(), request.white.end(), request.pos) != request.white.end()
        || std::find(request.black.begin(), request.black.end(), request.pos) != request.black.end()
        || std::find(request.blocked.begin(), request.blocked.end(), request.pos) != request.blocked.end()) {
            res.set_content("{"+build_json_content({"error"}, {"occupied"})+"}", "application/json");
        return true;
    }
    return false;
}

/*
    Get the list of int from a string from front and convert it to a vector of int
    @param input: the string to parse
    @return the vector of int
*/
std::vector<int> parse_board_input(std::string input) {
    std::vector<int> board;
    size_t pos = 0;
    size_t end = 0;
    if (input.empty())
        return board;

    while ((end = input.find(",", pos)) != std::string::npos) {
        board.push_back(std::stoi(input.substr(pos, end - pos)));
        pos = end + 1;
    }
    board.push_back(std::stoi(input.substr(pos, end - pos)));
    return board;
}

/*
    Build a json content from a list of key and a list of value
    @param key: the list of key
    @param value: the list of value
    @return the json content in a string
*/
std::string build_json_content(std::vector<std::string> key, std::vector<std::string> value) {
    std::string out = "";
    for (size_t i = 0; i < key.size(); i++) {
        if (i == 0)
            out += ("\"" + key[i] + "\":\"" + value[i] + "\"");
        else
            out += ",\n\"" + key[i] + "\":\"" + value[i] + "\"";
    }
    return out;   
}

/*
    Parse a request to create a new request structure
    @param req: the request to parse
    @return the new request structure
*/
t_request create_new_request(const httplib::Request &req) {

    int pos = std::stoi(req.path_params.at("pos"));
    int x = (pos) % 19;
    int y = (pos) / 19;
    e_color color = req.path_params.at("color") == "white" ? WHITESTONE : BLACKSTONE;
    std::vector<int> white = parse_board_input(req.path_params.at("white"));
    std::vector<int> black = parse_board_input(req.path_params.at("black"));
    std::vector<int> blocked = parse_board_input(req.path_params.at("blocked"));
    return {pos, x, y, color, white, black, blocked, 0, 0};
}

/*
    Parse a request to create a new ia request structure
    @param req: the request to parse
    @return the new ia request structure
*/
t_request create_new_ia_request(const httplib::Request &req) {
    e_color color = req.path_params.at("color") == "white" ? WHITESTONE : BLACKSTONE;
    std::vector<int> white = parse_board_input(req.path_params.at("white"));
    std::vector<int> black = parse_board_input(req.path_params.at("black"));
    std::vector<int> blocked = parse_board_input(req.path_params.at("blocked"));
    int white_captured = std::stoi(req.path_params.at("whiteCaptured"));
    int black_captured = std::stoi(req.path_params.at("blackCaptured"));
    return {0, 0, 0, color, white, black, blocked, white_captured, black_captured};
}

int get_captured_count(t_request request, e_color color) {
    if (color == WHITESTONE)
        return request.white_captured;
    return request.black_captured;
}

/*
    Build the response of an action request
    @param added: the list of added stone
    @param removed: the list of removed stone
    @param key: the list of key for the json content
    @param value: the list of value for the json content
    @return the response in a string well json handled
*/
std::string build_action_response(std::vector<t_stone> added, std::vector<int> removed, std::vector<std::string> key, std::vector<std::string> value) {
    std::string out = "{\n" + build_json_content(key, value);
    if (!key.empty())
        out += ",\n";
    out += "\"added\":[";
    for (size_t i = 0; i < added.size(); i++) {
        if (i == 0)
            out += "{\"pos\":" + std::to_string(added[i].pos) + ",\"color\":\"" + added[i].color + "\"}";
        else
            out += ",\n{\"pos\":" + std::to_string(added[i].pos) + ",\"color\":\"" + added[i].color + "\"}";
    }
    out += "],\n\"removed\":[";
    for (size_t i = 0; i < removed.size(); i++) {
        if (i == 0)
            out += std::to_string(removed[i]);
        else
            out += ",\n" + std::to_string(removed[i]);
    }
    return out + "]\n}";
}