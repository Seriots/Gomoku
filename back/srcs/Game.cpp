
#include <string>
#include <vector>

#include "request.hpp"

#include "Game.hpp"
#include "Board.hpp"

Game::Game()
{
    _board = Board();
}

Game::Game(std::vector <int> white, std::vector <int> black)
{
    _board = Board(white, black);
}

Game::Game(const Game &g) {
    _board = g.get_board();
}

Game::~Game() { }

void Game::operator= (const Game &g) {
    _board = g.get_board();
}

Board Game::get_board() const {
    return _board;
}

std::vector<int> Game::get_blocked(e_color color) {
    (void)color;
    std::vector<int> blocked;
    //for (int y = 0; y < 19; y++) {
    //    for (int x = 0; x < 19; x++) {
    //        if (_board.get(x, y).get_color() == color) {
    //            if (x > 0 && _board.get(x - 1, y).get_color() == EMPTY)
    //                blocked.push_back((x - 1) * 19 + y);
    //            if (x < 18 && _board.get(x + 1, y).get_color() == EMPTY)
    //                blocked.push_back((x + 1) * 19 + y);
    //            if (y > 0 && _board.get(x, y - 1).get_color() == EMPTY)
    //                blocked.push_back(x * 19 + y - 1);
    //            if (y < 18 && _board.get(x, y + 1).get_color() == EMPTY)
    //                blocked.push_back(x * 19 + y + 1);
    //        }
    //    }
    //}
    //blocked.push_back(rand() % 361);
    //blocked.push_back(rand() % 361);
    //blocked.push_back(rand() % 361);
    //blocked.push_back(rand() % 361);
    //blocked.push_back(rand() % 361);
    return blocked;
}
