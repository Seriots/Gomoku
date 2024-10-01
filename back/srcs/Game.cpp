
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

void    Game::set(int pos, e_cell cell) {
    int x = pos % 19;
    int y = pos / 19;
    _board.set(x, y, cell);
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

bool Game::check_sequence(int x, int y, int dx, int dy, std::vector<e_cell> sequence) {
    for (int i = 1; i <= (int)sequence.size(); i++) {
        if (x + (i * dx) < 0 || x + (i * dx) >= 19
            || y + (i * dy) < 0 || y + (i * dy) >= 19
            || _board.get(x + (i * dx), y + (i * dy)).get() != sequence[i-1])
        {
            return false;
        }
    }
    return true;
}

std::vector<int> Game::get_captured(int pos) {
    std::vector<int>                captured;
    std::vector<e_cell>             sequence;
    std::vector<std::vector<int> >  directions;
    
    int x = pos % 19;
    int y = pos / 19;
    Cell baseCell = _board.get(x, y);
    if (baseCell.get() == NONE || baseCell.get() == BLOCKED)
        return captured;
    if (baseCell.get() == WHITE) {
        sequence.push_back(BLACK);
        sequence.push_back(BLACK);
        sequence.push_back(WHITE);
    } else {
        sequence.push_back(WHITE);
        sequence.push_back(WHITE);
        sequence.push_back(BLACK);
    }
    directions = {{-1, 0},{1, 0},{0, -1},{0, 1},{-1, -1},{1, 1},{1, -1},{-1, 1}};
    for (size_t i = 0; i < directions.size(); i++) {
        int dx = directions[i][0];
        int dy = directions[i][1];
        if (check_sequence(x, y, dx, dy, sequence)) {
            captured.push_back((x + dx) + (y + dy) * 19);
            captured.push_back((x + 2 * dx) + (y + 2 * dy) * 19);
        }
    }
    return captured;
}

void Game::print_board() {
    _board.print();
}