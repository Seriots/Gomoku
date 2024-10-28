
#include <string>
#include <vector>

#include "request.hpp"
#include "utils.hpp"

#include "Game.hpp"
#include "Board.hpp"


/* ************************ Constructors/Destructor ************************** */

Game::Game() {
    _board = Board();
    _interesting_pos = {};
    _center = _board.get_center();
    this->init_dna();
    this->init_sequenceDna();
    this->init_test_board();
}

Game::Game(t_request &request)
{
    _request = request;
    _interesting_pos = {};
    _board = Board(request.white, request.black);
    print_board();
    _center = _board.get_center();
    this->init_dna();
    this->init_sequenceDna();
}

Game::Game(t_request &request, std::vector<int> &dna)
{
    _request = request;
    _board = Board(request.white, request.black);
    _interesting_pos = this->get_interesting_pos();
    _center = _board.get_center();
    this->init_dna();
    this->init_sequenceDna(&dna);
}

Game::Game(const Game &g) {
    _board = g.get_board();
    _dna = g._dna;
    _sequenceDna = g._sequenceDna;
    _request = g._request;
    _center = g.get_board().get_center();
    _interesting_pos = g._interesting_pos;
}

Game::~Game() { }

void Game::operator=(const Game &g) {
    _board = g.get_board();
    _dna = g._dna;
    _request = g._request;
    _center = g.get_board().get_center();
    _interesting_pos = g._interesting_pos;
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

void Game::set_threshold(std::vector<int> threshold) {
    _threshold = threshold;
}

void Game::set_depth(int depth) {
    _depth = depth;
}

int Game::get_depth() const {
    return _depth;
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

Board Game::get_board() const {
    return _board;
}

std::vector<int> Game::getter_interesting_pos() const {
    return _interesting_pos;
}

void Game::init_interesting_pos(e_color color, std::vector<int> allowed_pos) {
    if (allowed_pos.size() != 0)
    {
        this->_interesting_pos = allowed_pos;
        return ;
    }
    this->_interesting_pos = this->get_interesting_pos();

    std::vector<int> blocked_pos = get_new_blocked_pos(color);
    for (size_t i = 0; i < blocked_pos.size(); i++) {
        std::vector<int>::iterator it = std::find(this->_interesting_pos.begin(), this->_interesting_pos.end(), blocked_pos[i]);
        if (it != this->_interesting_pos.end())
            this->_interesting_pos.erase(it);
    }
    this->sort_interesting_pos(color, this->_interesting_pos);
}
