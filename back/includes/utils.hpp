#pragma once

#include <httplib.h>

#include <string>
#include <vector>

#include "Cell.hpp"
#include "request.hpp"

#include "structs.hpp"



bool                check_error_request(t_request &request,  httplib::Response &res);

std::vector<int>    parse_board_input(std::string input);

std::string         build_json_content(std::vector<std::string> key, std::vector<std::string> value);
std::string         build_action_response(std::vector<t_stone> added, std::vector<int> removed, t_endgame_info &endgame_info, std::vector<std::string> keys, std::vector<std::string> values);
t_request           create_new_request(const httplib::Request &req);
t_request           create_new_ia_request(const httplib::Request &req);
std::vector<int>    get_request_dna(const httplib::Request &req);
int                 get_captured_count_by_color(t_request request, e_color color);

int get_linear_distance(t_position const a, t_position const b);
std::vector<int> generate_thresholds(int max_depth, int max_calculations, int max_thresholds, int min_thresholds);
e_cell color_to_cell(e_color color);

