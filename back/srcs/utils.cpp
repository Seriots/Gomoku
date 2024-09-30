#include <string>
#include <vector>

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