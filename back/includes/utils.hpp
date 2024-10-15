#pragma once

#include <httplib.h>

#include <string>
#include <vector>

#include "request.hpp"

bool check_error_request(t_request &request,  httplib::Response &res);

std::vector<int> parse_board_input(std::string input);

std::string build_json_content(std::vector<std::string> key, std::vector<std::string> value);
std::string build_action_response(std::vector<t_stone> added, std::vector<int> removed, std::vector<std::string> key, std::vector<std::string> value);

t_request create_new_request(const httplib::Request &req);
t_request create_new_ia_request(const httplib::Request &req);
int get_captured_count_by_color(t_request request, e_color color);