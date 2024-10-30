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

bool Board::is_in_grid(int x, int y) const {
    return (x >= 0 && x < 19 && y >= 0 && y < 19);
}

t_direction_info Board::compute_direction_side(t_position &grid_pos, int dx, int dy, e_cell my, e_cell other) const {
    t_direction_info di = {0, 0, 0, false, false, false, false, false, NONE, false};
    
    bool found_none = false;

    e_cell  start = other;

    for (int i = 1; i < 5; i++) {
        int x = grid_pos.x + i * dx;
        int y = grid_pos.y + i * dy;

        if (!is_in_grid(x, y))
            break;

        e_cell cell = this->get(x, y).get();
        if (found_none) {
            if (cell == my)
                di.my_free_alignement++;
            else
                break;
        }
        if (cell == my)
        {
            di.my_free_alignement++;
            if (di.my_real_alignement == 0 && di.other_real_alignement == 0) {
                di.start = my;
                start = my;
            }
            if (start == my)
                di.my_real_alignement++;
            else if (start == other) {
                if (di.other_real_alignement == 2)
                    di.capture = true;
                break;
            }
        }
        else if (cell == other)
        {
            di.locked = true;
            if (di.my_real_alignement == 0 && di.other_real_alignement == 0) {
                di.start = other;
                start = other;
            }
            if (start == other)
                di.other_real_alignement++;
            else if (start == my) {
                if (di.my_real_alignement == 2)
                    di.block_capture = true;
                else if (di.my_real_alignement == 1)
                    di.is_capturable_O = true;
                break;
            }
        }
        else
        {
            if (di.my_real_alignement == 0 && di.other_real_alignement == 0)
                di.start = NONE;
            if (di.other_real_alignement == 2)
                di.setup_capture = true;
            if (di.my_real_alignement == 1)
                di.is_capturable_N = true;
            found_none = true;
        }
    }
    di.my_real_alignement++;
    return di;
}

int Board::compute_score_info(t_score_info score_info, t_captureCount capture, e_cell my) const {
    int score = 0;
    score += score_info.any_alignement * 25;
    score += score_info.free_three * 1000;
    score += score_info.free_four * 20000;
    score += score_info.capture * 150000 * (1 + (my == WHITE ? capture.white : capture.black));
    score += score_info.align_five * 1000000;
    score += score_info.block_capture * 140000 *  (1 + (my == WHITE ? capture.black : capture.white));
    score += score_info.is_capturable * -60000;
    score += score_info.setup_capture * 15000;
    score += score_info.block_win * 10850000;
    score += score_info.block_free_four * 200000;
    score += score_info.block_free_three * 10000;
    return score;

}

int Board::get_score_position(e_color color, int pos, t_captureCount capture) const {
        int         score;
        t_score_info score_info; 
        t_position  grid_pos;
        
        e_cell      my = color == WHITESTONE ? WHITE : BLACK;
        e_cell      other = (my == WHITE) ? BLACK : WHITE;
        
        grid_pos = {pos % 19, pos / 19};
        score = 20 - get_linear_distance(grid_pos, this->get_center());

        std::vector<std::vector<int> >  directions;

        directions = {{-1, 0},{0, -1}, {-1, -1},{1, -1}};
        for (std::vector<int> direction : directions) {
            int dx = direction[0];
            int dy = direction[1];
            t_direction_info diF = compute_direction_side(grid_pos, dx, dy, my, other);
            t_direction_info diB = compute_direction_side(grid_pos, -dx, -dy, my, other);
            score_info = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

            score_info.any_alignement += diF.my_free_alignement + diB.my_free_alignement;

            int my_real_alignement = diF.my_real_alignement + diB.my_real_alignement - (diF.locked || diB.locked ? 1 : 0);
            score_info.align_five += my_real_alignement >= 5;
            score_info.free_four += my_real_alignement == 4;
            score_info.free_three += my_real_alignement == 3;

            
            int other_real_alignement = diF.other_real_alignement + diB.other_real_alignement;
            score_info.block_win += other_real_alignement >= 4;
            score_info.block_free_four += other_real_alignement == 3;
            score_info.block_free_three += other_real_alignement == 2;
            score_info.block_capture += diF.block_capture + diB.block_capture;
            score_info.setup_capture += diF.setup_capture + diB.setup_capture;
            
            if ((diF.is_capturable_O && diB.start == NONE) || (diF.is_capturable_N && diB.start == other))
                score_info.is_capturable++;
            if ((diB.is_capturable_O && diF.start == NONE) || (diB.is_capturable_N && diF.start == other))
                score_info.is_capturable++;
            
            score_info.capture += diF.capture + diB.capture;

            score += compute_score_info(score_info, capture, my);
        }
        
        return score;
}

