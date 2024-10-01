#include <httplib.h>

#include <iostream>
#include <string>

#include "utils.hpp"
#include "request.hpp"

int main() {
	httplib::Server svr;

	srand((unsigned)time(0));

	svr.Get("/game", r_game);

	svr.Get("/end", r_end);

    svr.Get("/action/:pos/:color/:white/:black/:blocked", r_action);
    svr.Get("/ia/:color/:white/:black", r_ia);

	svr.listen("localhost", 6325);
}