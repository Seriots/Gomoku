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
    std::string out = "{\n";
    for (size_t i = 0; i < key.size(); i++) {
        if (i == 0)
            out += ("\"" + key[i] + "\":\"" + value[i] + "\"");
        else
            out += ",\n\"" + key[i] + "\":\"" + value[i] + "\"";
    }
    return out + "\n}";   
}

t_request create_new_request(const httplib::Request &req) {

    int pos = std::stoi(req.path_params.at("pos"));
    int x = (pos) / 19;
    int y = (pos) % 19;
    e_color color = req.path_params.at("color") == "white" ? WHITESTONE : BLACKSTONE;
    std::vector<int> white = parse_board_input(req.path_params.at("white"));
    std::vector<int> black = parse_board_input(req.path_params.at("black"));
    return {pos, x, y, color, white, black};
}