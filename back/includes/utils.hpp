#pragma once

#include <httplib.h>

#include <string>
#include <vector>

#include "request.hpp"

std::string generate_cookie(size_t len = 16, std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");

std::string get_game_id(std::string &cookies);

std::vector<int> parse_board_input(std::string input);
std::string build_json_content(std::vector<std::string> key, std::vector<std::string> value);

t_request create_new_request(const httplib::Request &req);