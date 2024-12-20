#include <httplib.h>

#include <iostream>
#include <string>

#include "utils.hpp"
#include "request.hpp"
#include "includes/Board.hpp"

int main() {
	httplib::Server svr;

	srand(time(NULL));

    svr.Get("/api/action/:pos/:color/:white/:black/:blocked/:allowed/:whiteCapture/:blackCapture/:openingRule/:currentTurn", r_action);
    svr.Get("/api/ia/:color/:white/:black/:blocked/:allowed/:whiteCapture/:blackCapture/:depth/:openingRule/:currentTurn", r_ia);
    svr.Get("/api/swapChoice/:color/:white/:black/:blocked/:allowed/:whiteCapture/:blackCapture/:depth/:openingRule/:currentTurn", r_swapChoice);
    svr.Get("/iaWithDna/:color/:white/:black/:blocked/:whiteCapture/:blackCapture/:dna", r_ia_with_dna);

	svr.listen("localhost", 6325);
}
