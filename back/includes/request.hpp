#pragma once
#include <httplib.h>
#include "structs.hpp"


void    r_game(const httplib::Request &req, httplib::Response &res);
void    r_end(const httplib::Request &req, httplib::Response &res);
void    r_action(const httplib::Request &req, httplib::Response &res);
void    r_ia(const httplib::Request &req, httplib::Response &res);
void    r_ia_with_dna(const httplib::Request &req, httplib::Response &res);
void    r_swapChoice(const httplib::Request &req, httplib::Response &res);