#include <vector>
#include <algorithm>
#include <iostream>
#include <tgmath.h>

#include "utils.hpp"
#include "Board.hpp"
#include "Cell.hpp"

Board::Board() {
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            _board[i][j] = Cell();
        }
    }
}

Board::Board(std::vector <int> white, std::vector <int> black) {
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            if(std::find(white.begin(), white.end(), i * 19 + j) != white.end()) {
                _board[i][j] = Cell(WHITE);
            } else if(std::find(black.begin(), black.end(), i * 19 + j) != black.end()) {
                _board[i][j] = Cell(BLACK);
            } else {
                _board[i][j] = Cell();
            }
        }
    }
    compute_board_center();
}

Board::Board(const Board &b) {
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            _board[i][j] = b.get(j, i);
        }
    }
    _center = b.get_center_pos();
}

Board::~Board() { }

void Board::operator= (const Board &b) {
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            _board[i][j] = b.get(j, i);
        }
    }
    _center = b.get_center_pos();
}

void Board::compute_board_center() {
    int x_cumul = 0;
    int y_cumul = 0;
    int counter = 0;
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            if (_board[i][j].get() != NONE) {
                x_cumul += j;
                y_cumul += i;
                counter++;
            }
        }
    }
    if (counter == 0) {
        _center = 9 + 9 * 19;
    } else {
        _center = round((float)x_cumul / (float)counter) + round((float)y_cumul / (float)counter) * 19;
    }
}

Cell Board::get(int x, int y) const {
    return _board[y][x];
}

Cell Board::get(int pos) const {
    int x = pos % 19;
    int y = pos / 19;
    return _board[y][x];
}

t_position Board::get_center() const {
    return {_center % 19, _center / 19};
}

int Board::get_center_pos() const {
    return _center;
}


void Board::set(int x, int y, e_cell cell) {
    _board[y][x].set(cell);
}

void Board::set(int pos, e_cell cell) {
    _board[pos / 19][pos % 19].set(cell);
}


void Board::print() {
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            std::cout << _board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

size_t Board::get_hash_board() const {
    size_t hash = 0;
    size_t prime = 31;

    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            e_cell color = this->get(j, i).get();
            int v = (color == WHITE) ? 1 : (color == BLACK) ? 2 : 0;
            hash = hash * prime + (v * (i + 1) * (j + 1));
        }
    }
    return hash;
}

bool Board::isFull() {
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            if (_board[i][j].get() == NONE)
                return false;
        }
    }
    return true;
}
