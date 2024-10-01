#include <httplib.h>

#include <string>
#include <vector>

#include "request.hpp"

std::string generate_cookie(size_t len = 16, std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") {
    std::string random_string;
    
    for (size_t i = 0; i < len; i++) {
        random_string += chars[rand() % chars.size()];
    }
    return random_string;
}

std::string get_game_id(std::string &cookies) {
    size_t pos = cookies.find("gameID=");

    if (pos != std::string::npos) {
        size_t end = cookies.find(";", pos);
        return cookies.substr(pos + 7, end - pos - 7);
    }
    return "";
}

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

t_request create_new_request(const httplib::Request &req) {

    int pos = std::stoi(req.path_params.at("pos"));
    int x = (pos) / 19;
    int y = (pos) % 19;
    e_color color = req.path_params.at("color") == "white" ? WHITESTONE : BLACKSTONE;
    std::vector<int> white = parse_board_input(req.path_params.at("white"));
    std::vector<int> black = parse_board_input(req.path_params.at("black"));
    std::vector<int> blocked = parse_board_input(req.path_params.at("blocked"));
    return {pos, x, y, color, white, black, blocked};
}

t_request create_new_ia_request(const httplib::Request &req) {
    e_color color = req.path_params.at("color") == "white" ? WHITESTONE : BLACKSTONE;
    std::vector<int> white = parse_board_input(req.path_params.at("white"));
    std::vector<int> black = parse_board_input(req.path_params.at("black"));
    return {0, 0, 0, color, white, black, {}};
}

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