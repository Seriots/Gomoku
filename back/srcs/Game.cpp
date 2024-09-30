
#include <string>
#include <vector>

#include "Game.hpp"
#include "Board.hpp"

Game::Game()
{
    _board = Board();
}

Game::Game(std::vector <int> white, std::vector <int> black, std::vector <int> blocked)
{
    _board = Board(white, black, blocked);
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
