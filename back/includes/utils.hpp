#pragma once

#include <string>
#include <vector>

std::string generate_cookie(size_t len = 16, std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");

std::string get_game_id(std::string &cookies);

std::vector<int> parse_board_input(std::string input);
