#include <vector>
#include <algorithm>

#include "Board.hpp"
#include "Cell.hpp"

Board::Board() {
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            _board[i][j] = Cell();
        }
    }
}

Board::Board(std::vector <int> white, std::vector <int> black, std::vector <int> blocked) {
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            if(std::find(white.begin(), white.end(), i * 19 + j) != white.end()) {
                _board[i][j] = Cell(WHITE);
            } else if(std::find(black.begin(), black.end(), i * 19 + j) != black.end()) {
                _board[i][j] = Cell(BLACK);
            } else if(std::find(blocked.begin(), blocked.end(), i * 19 + j) != blocked.end()) {
                _board[i][j] = Cell(BLOCKED);
            } else {
                _board[i][j] = Cell();
            }
        }
    }
}

Board::Board(const Board &b) {
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            _board[i][j] = b.get(i, j);
        }
    }
}

Board::~Board() { }

void Board::operator= (const Board &b) {
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            _board[i][j] = b.get(i, j);
        }
    }
}

Cell Board::get(int x, int y) const {
    return _board[x][y];
}