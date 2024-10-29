#include <httplib.h>

#include <iostream>
#include <string>

#include "utils.hpp"
#include "request.hpp"
#include "includes/Board.hpp"

int main() {
	httplib::Server svr;

	srand(time(NULL));

	svr.Get("/game", r_game);

	svr.Get("/end", r_end);

    svr.Get("/action/:pos/:color/:white/:black/:blocked/:allowed/:whiteCapture/:blackCapture", r_action);
    svr.Get("/ia/:color/:white/:black/:blocked/:allowed/:whiteCapture/:blackCapture/:depth", r_ia);
    svr.Get("/iaWithDna/:color/:white/:black/:blocked/:whiteCapture/:blackCapture/:dna", r_ia_with_dna);

	svr.listen("localhost", 6325);
}
