
#include <string>
#include <vector>

#include "request.hpp"
#include "utils.hpp"

#include "Game.hpp"
#include "Board.hpp"


/* ************************ Constructors/Destructor ************************** */

Game::Game() {
    _board = Board();
    _center = _board.get_center();
    this->init_dna();
    this->init_sequenceDna();
    this->init_test_board();
}

Game::Game(t_request &request)
{
    _request = request;
    _board = Board(request.white, request.black);
    _interesting_pos = this->get_interesting_pos();
    _center = _board.get_center();
    this->init_dna();
    this->init_sequenceDna();
}

Game::Game(const Game &g) {
    _board = g.get_board();
    _dna = g._dna;
    _sequenceDna = g._sequenceDna;
    _request = g._request;
    _center = g.get_board().get_center();
    _interesting_pos = g._interesting_pos;
    _blocked_pos = g._blocked_pos;
}

Game::~Game() { }

void Game::operator=(const Game &g) {
    _board = g.get_board();
    _dna = g._dna;
    _request = g._request;
    _center = g.get_board().get_center();
    _interesting_pos = g._interesting_pos;
    _blocked_pos = g._blocked_pos;
}


/* ************************ Data Manipulation ************************** */
void    Game::set(int pos, e_cell cell) {
    int x = pos % 19;
    int y = pos / 19;
    _board.set(x, y, cell);
}

void Game::set(std::vector<int> pos, e_cell cell) {
    for (size_t i = 0; i < pos.size(); i++) {
        int x = pos[i] % 19;
        int y = pos[i] / 19;
        _board.set(x, y, cell);
    }
}

void Game::unset(int pos) {
    int x = pos % 19;
    int y = pos / 19;
    _board.set(x, y, NONE);
}

void Game::unset(std::vector<int> pos) {
    for (size_t i = 0; i < pos.size(); i++) {
        int x = pos[i] % 19;
        int y = pos[i] / 19;
        _board.set(x, y, NONE);
    }
}

void Game::unset_blocked_pos() {
    for (size_t i = 0; i < _blocked_pos.size(); i++) {
        int x = _blocked_pos[i] % 19;
        int y = _blocked_pos[i] / 19;
        _board.set(x, y, NONE);
    }
    _blocked_pos.clear();
}

Board Game::get_board() const {
    return _board;
}

