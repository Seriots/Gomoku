#include <vector>
#include <algorithm>
#include <iostream>

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
}

Board::Board(const Board &b) {
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            _board[i][j] = b.get(j, i);
        }
    }
}

Board::~Board() { }

void Board::operator= (const Board &b) {
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            _board[i][j] = b.get(j, i);
        }
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

void Board::set(int x, int y, e_cell cell) {
    _board[y][x].set(cell);
}

void Board::print() {
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            std::cout << _board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}