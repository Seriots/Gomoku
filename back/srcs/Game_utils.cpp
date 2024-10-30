#include "Game.hpp"

void Game::init_dna() {
    _dna[ALIGN_FIVE] = 1000000;
    _dna[FREE_FOUR] = 10000;
    _dna[FREE_THREE] = 1000;
    _dna[ANY_ALIGNEMENT] = 25;
    _dna[CAPTURE_TOTAL_2] = 4000;
    _dna[CAPTURE_TOTAL_4] = 5000;
    _dna[CAPTURE_TOTAL_6] = 6000;
    _dna[CAPTURE_TOTAL_8] = 15000;
    _dna[CAPTURE_TOTAL_10] = 100000;
    _dna[BLOCK_FREE_THREE] = 6900;
    _dna[BLOCK_FREE_FOUR] = 7900;
    _dna[BLOCK_CAPTURE] = 16000;
    _dna[BLOCK_WIN] = 89000;
    _dna[SETUP_CAPTURE] = 200;
    _dna[IS_CAPTURABLE] = -15000;
}

void Game::init_sequenceDna(std::vector<int> *dna) {
    std::map<e_valueDna, int> valuesDna;

    if (!dna) {
        this->_valuesDna[VDNA_ONE] = 1;
        this->_valuesDna[VDNA_TWON3] = 24;
        this->_valuesDna[VDNA_TWON2] = 32;
        this->_valuesDna[VDNA_TWON1] = 40;
        this->_valuesDna[VDNA_TWO] = 60;
        this->_valuesDna[VDNA_THREEN2] = 160;
        this->_valuesDna[VDNA_THREEN1] = 200;
        this->_valuesDna[VDNA_THREE] = 1400;
        this->_valuesDna[VDNA_FOURN1] = 3400;
        this->_valuesDna[VDNA_FOUR] = 15100;
        this->_valuesDna[VDNA_THREEFREE] = 22000;
        this->_valuesDna[VDNA_FIVE] = 2000000;
        this->_valuesDna[VDNA_POTENTIAL_CAPTURE] = 3400;
        this->_valuesDna[VDNA_EFFECTIVE_CAPTURE_0] = 5000;
        this->_valuesDna[VDNA_EFFECTIVE_CAPTURE_1] = 7000;
        this->_valuesDna[VDNA_EFFECTIVE_CAPTURE_2] = 10000;
        this->_valuesDna[VDNA_EFFECTIVE_CAPTURE_3] = 1000000;
    } else {
        for (size_t i = 0; i < dna->size(); i++) {
            this->_valuesDna[(e_valueDna)i] = dna->at(i);
        }
    }

    float minusFactor = -1.0;

    _sequenceDna[SDNA_NNNNM] = this->_valuesDna[VDNA_ONE];
    _sequenceDna[SDNA_NNNNY] = minusFactor * this->_valuesDna[VDNA_ONE];
    _sequenceDna[SDNA_NNNMN] = this->_valuesDna[VDNA_ONE];
    _sequenceDna[SDNA_NNNMM] = this->_valuesDna[VDNA_TWO];
    _sequenceDna[SDNA_NNNYN] = minusFactor * this->_valuesDna[VDNA_ONE];
    _sequenceDna[SDNA_NNNYY] = minusFactor * this->_valuesDna[VDNA_TWO];
    _sequenceDna[SDNA_NNMNN] = this->_valuesDna[VDNA_ONE];
    _sequenceDna[SDNA_NNMNM] = this->_valuesDna[VDNA_TWON1];
    _sequenceDna[SDNA_NNMMN] = this->_valuesDna[VDNA_TWO];
    _sequenceDna[SDNA_NNMMM] = this->_valuesDna[VDNA_THREE];
    _sequenceDna[SDNA_NNMMY] = minusFactor * this->_valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_NNYNN] = minusFactor * this->_valuesDna[VDNA_ONE];
    _sequenceDna[SDNA_NNYNY] = minusFactor * this->_valuesDna[VDNA_TWON1];
    _sequenceDna[SDNA_NNYYN] = minusFactor * this->_valuesDna[VDNA_TWO];
    _sequenceDna[SDNA_NNYYM] = this->_valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_NNYYY] = minusFactor * this->_valuesDna[VDNA_THREE];
    _sequenceDna[SDNA_NMNNN] = this->_valuesDna[VDNA_ONE];
    _sequenceDna[SDNA_NMNNM] = this->_valuesDna[VDNA_TWON2];
    _sequenceDna[SDNA_NMNMN] = this->_valuesDna[VDNA_TWON1];
    _sequenceDna[SDNA_NMNMM] = this->_valuesDna[VDNA_THREEN1];
    _sequenceDna[SDNA_NMMNN] = this->_valuesDna[VDNA_TWO];
    _sequenceDna[SDNA_NMMNM] = this->_valuesDna[VDNA_THREEN1];
    _sequenceDna[SDNA_NMMMN] = this->_valuesDna[VDNA_THREEFREE];
    _sequenceDna[SDNA_NMMMM] = this->_valuesDna[VDNA_FOUR];
    _sequenceDna[SDNA_NMMYN] = minusFactor * this->_valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_NMMYM] = minusFactor * this->_valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_NMMYY] = minusFactor * this->_valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_NMYYN] = this->_valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_NYNNN] = minusFactor * this->_valuesDna[VDNA_ONE];
    _sequenceDna[SDNA_NYNNY] = minusFactor * this->_valuesDna[VDNA_TWON2];
    _sequenceDna[SDNA_NYNYN] = minusFactor * this->_valuesDna[VDNA_TWON1];
    _sequenceDna[SDNA_NYNYY] = minusFactor * this->_valuesDna[VDNA_THREEN1];
    _sequenceDna[SDNA_NYMMN] = minusFactor * this->_valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_NYYNN] = minusFactor * this->_valuesDna[VDNA_TWO];
    _sequenceDna[SDNA_NYYNY] = minusFactor * this->_valuesDna[VDNA_THREEN1];
    _sequenceDna[SDNA_NYYMN] = this->_valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_NYYMM] = this->_valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_NYYMY] = this->_valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_NYYYN] = minusFactor * this->_valuesDna[VDNA_THREEFREE];
    _sequenceDna[SDNA_NYYYY] = minusFactor * this->_valuesDna[VDNA_FOUR];
    _sequenceDna[SDNA_MNNNN] = this->_valuesDna[VDNA_ONE];
    _sequenceDna[SDNA_MNNNM] = this->_valuesDna[VDNA_TWON3];
    _sequenceDna[SDNA_MNNMN] = this->_valuesDna[VDNA_TWON2];
    _sequenceDna[SDNA_MNNMM] = this->_valuesDna[VDNA_THREEN2];
    _sequenceDna[SDNA_MNMNN] = this->_valuesDna[VDNA_TWON1];
    _sequenceDna[SDNA_MNMNM] = this->_valuesDna[VDNA_THREEN2];
    _sequenceDna[SDNA_MNMMN] = this->_valuesDna[VDNA_THREEN1];
    _sequenceDna[SDNA_MNMMM] = this->_valuesDna[VDNA_FOURN1];
    _sequenceDna[SDNA_MNMMY] = minusFactor * this->_valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_MNYYM] = this->_valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_MMNNN] = this->_valuesDna[VDNA_TWO];
    _sequenceDna[SDNA_MMNNM] = this->_valuesDna[VDNA_THREEN2];
    _sequenceDna[SDNA_MMNMN] = this->_valuesDna[VDNA_THREEN1];
    _sequenceDna[SDNA_MMNMM] = this->_valuesDna[VDNA_FOURN1];
    _sequenceDna[SDNA_MMMNN] = this->_valuesDna[VDNA_THREE];
    _sequenceDna[SDNA_MMMNM] = this->_valuesDna[VDNA_FOURN1];
    _sequenceDna[SDNA_MMMMN] = this->_valuesDna[VDNA_FOUR];
    _sequenceDna[SDNA_MMMMM] = this->_valuesDna[VDNA_FIVE];
    _sequenceDna[SDNA_MMYYN] = this->_valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_MYMMN] = minusFactor * this->_valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_MYYNN] = this->_valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_MYYNM] = this->_valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_MYYNY] = this->_valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_YNNNN] = minusFactor * this->_valuesDna[VDNA_ONE];
    _sequenceDna[SDNA_YNNNY] = minusFactor * this->_valuesDna[VDNA_TWON3];
    _sequenceDna[SDNA_YNNYN] = minusFactor * this->_valuesDna[VDNA_TWON2];
    _sequenceDna[SDNA_YNNYY] = minusFactor * this->_valuesDna[VDNA_THREEN2];
    _sequenceDna[SDNA_YNMMY] = minusFactor * this->_valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_YNYNN] = minusFactor * this->_valuesDna[VDNA_TWON1];
    _sequenceDna[SDNA_YNYNY] = minusFactor * this->_valuesDna[VDNA_THREEN2];
    _sequenceDna[SDNA_YNYYN] = minusFactor * this->_valuesDna[VDNA_THREEN1];
    _sequenceDna[SDNA_YNYYM] = this->_valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_YNYYY] = minusFactor * this->_valuesDna[VDNA_FOURN1];
    _sequenceDna[SDNA_YMMNN] = minusFactor * this->_valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_YMMNM] = minusFactor * this->_valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_YMMNY] = minusFactor * this->_valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_YMYYN] = this->_valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_YYNNN] = minusFactor * this->_valuesDna[VDNA_TWO];
    _sequenceDna[SDNA_YYNNY] = minusFactor * this->_valuesDna[VDNA_THREEN2];
    _sequenceDna[SDNA_YYNYN] = minusFactor * this->_valuesDna[VDNA_THREEN1];
    _sequenceDna[SDNA_YYNYY] = minusFactor * this->_valuesDna[VDNA_FOURN1];
    _sequenceDna[SDNA_YYMMN] = minusFactor * this->_valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_YYYNN] = minusFactor * this->_valuesDna[VDNA_THREE];
    _sequenceDna[SDNA_YYYNY] = minusFactor * this->_valuesDna[VDNA_FOURN1];
    _sequenceDna[SDNA_YYYYN] = minusFactor * this->_valuesDna[VDNA_FOUR];
    _sequenceDna[SDNA_YYYYY] = minusFactor * this->_valuesDna[VDNA_FIVE];
}

bool Game::is_in_grid(int x, int y) {
    return (x >= 0 && x < 19 && y >= 0 && y < 19);
}


/* ************************ Algorithme ************************** */
bool Game::check_free_three(int x, int y, int ax, int ay, e_cell color) {
    int inv_color = (color == WHITE) ? BLACK : WHITE;
    std::vector<e_cell> axis_values;

    for (int i = -4; i <= 4; i++) {
        int nx = x + (i * ax);
        int ny = y + (i * ay);
        if (i == 0)
            axis_values.push_back(color);
        else if (is_in_grid(nx, ny))
            axis_values.push_back(this->_board.get(nx, ny).get());
    }
    size_t i = 1;
    while (i < axis_values.size()) {
        if (axis_values[i] == color && axis_values[i - 1] == NONE) {
            i++;
            int nb_colored = 1;
            int nb_none = 0;
            while (i < axis_values.size()) {
                if (axis_values[i] == inv_color)
                    break;
                else if (axis_values[i] == color)
                    nb_colored++;
                else {
                    if (nb_colored == 3)
                        return true;
                    nb_none++;
                }
                if (nb_none > 1 || nb_colored > 3)
                    break;
                i++;
            }
        }
        i++;
    }


    return false;
}


bool Game::check_double_free_three(int x, int y, e_cell color) {
    std::vector<std::vector<int> >  axis;

    axis = {{1, 1}, {0, 1}, {1, -1}, {1, 0}};

    int nb_three = 0;
    for (size_t i = 0; i < axis.size(); i++) {
        int ax = axis[i][0];
        int ay = axis[i][1];
        nb_three += this->check_free_three(x, y, ax, ay, color);

    }
    return (nb_three >= 2);
}

std::vector<int> Game::get_new_blocked_pos(e_color color) {
    std::vector<int> blocked;
    std::vector<int> blocked_not_captured;

    for (int place = 0; place < 361; place++) {
        int x = place % 19;
        int y = place / 19;
        if (_board.get(x, y).get() == NONE && this->check_double_free_three(x, y, color == WHITESTONE ? WHITE : BLACK)) {
            blocked.push_back(place);
        }
    }

    for (size_t i = 0; i < blocked.size(); i++) {
        if (this->get_captured(blocked[i], color).size() == 0)
            blocked_not_captured.push_back(blocked[i]);
    }

    return blocked_not_captured;
}

bool Game::check_sequence(int x, int y, int dx, int dy, std::vector<e_cell> sequence) {
    for (int i = 1; i <= (int)sequence.size(); i++) {
        int nx = x + (i * dx);
        int ny = y + (i * dy);
        if (!is_in_grid(nx, ny) || _board.get(nx, ny).get() != sequence[i-1])
            return false;
    }
    return true;
}

std::vector<int> Game::get_captured(int pos, e_color color) {
    std::vector<int>                captured;
    std::vector<e_cell>             sequence;
    std::vector<std::vector<int> >  directions;

    int x = pos % 19;
    int y = pos / 19;
    if (color == WHITESTONE) {
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
        if (this->check_sequence(x, y, dx, dy, sequence)) {
            captured.push_back((x + dx) + (y + dy) * 19);
            captured.push_back((x + 2 * dx) + (y + 2 * dy) * 19);
        }
    }

    return captured;
}

bool Game::is_something_near(int x, int y) {
    std::vector<std::vector<int> > directions = {{-1, 0},{1, 0},{0, -1},{0, 1},{-1, -1},{1, 1},{1, -1},{-1, 1}};

    for (size_t i = 0; i < directions.size(); i++) {
        int dx = directions[i][0];
        int dy = directions[i][1];
        if (is_in_grid(x + dx, y + dy) && _board.get(x + dx, y + dy).get() != NONE)
            return true;
    }

    return false;
}

std::vector<int> Game::get_interesting_pos() {
    std::vector<int> interesting_pos;

    for (int pos = 0; pos < 361; pos++) {
        if (pos != NONE && pos != BLOCKED) {
            int x = pos % 19;
            int y = pos / 19;
            if (this->get_board().get(x, y).get() == NONE && is_something_near(x, y)) {
                interesting_pos.push_back(pos);
            }
        }
    }

    if (interesting_pos.size() == 0)
        interesting_pos.push_back(180);

    return interesting_pos;
}

void Game::sort_interesting_pos(e_color const &color, std::vector<int> &vec, t_captureCount &capture) {
    std::map<int, int>  score_on_pos;
    std::vector<int>    captured;

    for (size_t i = 0; i < vec.size(); i++) {
        score_on_pos[vec[i]] = this->_board.get_score_position(color, vec[i], capture);
    }
    std::sort(vec.begin(), vec.end(), [&score_on_pos](int a, int b) {
        return score_on_pos[a] > score_on_pos[b];
    });
}

void Game::print_board() {
    _board.print();
}

std::map<e_cell, std::vector<int> > Game::get_all_positions_stone() {
    std::map<e_cell, std::vector<int> > positions;
    // set a vector for Black and White stones
    positions[WHITE] = std::vector<int>();
    positions[BLACK] = std::vector<int>();

    for (int i = 0; i < 361; i++) {
        if (_board.get(i).get() == WHITE)
            positions[WHITE].push_back(i);
        else if (_board.get(i).get() == BLACK)
            positions[BLACK].push_back(i);
    }

    return positions;
}


/* ************************ TEST ************************** */

void Game::init_test_board() {
    this->_board.set(8, 8, WHITE);
    this->_board.set(9, 9, WHITE);
    this->_board.set(10, 10, WHITE);
}
