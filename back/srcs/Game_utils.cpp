#include "Game.hpp"

void Game::init_dna() {
    _dna[ALIGN_FIVE] = 100000;
    _dna[FREE_FOUR] = 10000;
    _dna[FREE_THREE] = 1000;
    _dna[ANY_ALIGNEMENT] = 25;
    _dna[CAPTURE_TOTAL_2] = 400;
    _dna[CAPTURE_TOTAL_4] = 800;
    _dna[CAPTURE_TOTAL_6] = 2500;
    _dna[CAPTURE_TOTAL_8] = 5000;
    _dna[CAPTURE_TOTAL_10] = 100000;
    _dna[BLOCK_FREE_THREE] = 6900;
    _dna[BLOCK_FREE_FOUR] = 7900;
    _dna[BLOCK_CAPTURE] = 6000;
    _dna[BLOCK_WIN] = 89000;
    _dna[SETUP_CAPTURE] = 200;
    _dna[IS_CAPTURABLE] = -3000;
}

void Game::init_sequenceDna() {
    std::map<e_valueDna, int> valuesDna;

    valuesDna[VDNA_NONE] = 0;
    valuesDna[VDNA_ONE] = 1;
    valuesDna[VDNA_TWON3] = 24;
    valuesDna[VDNA_TWON2] = 32;
    valuesDna[VDNA_TWON1] = 40;
    valuesDna[VDNA_TWO] = 60;
    valuesDna[VDNA_THREEN2] = 160;
    valuesDna[VDNA_THREEN1] = 200;
    valuesDna[VDNA_THREE] = 1400;
    valuesDna[VDNA_FOURN1] = 3400;
    valuesDna[VDNA_FOUR] = 15100;
    valuesDna[VDNA_THREEFREE] = 20000;
    valuesDna[VDNA_FIVE] = 1000000;
    valuesDna[VDNA_POTENTIAL_CAPTURE] = 3500;
    valuesDna[VDNA_EFFECTIVE_CAPTURE_0] = 5000;
    valuesDna[VDNA_EFFECTIVE_CAPTURE_1] = 10000;
    valuesDna[VDNA_EFFECTIVE_CAPTURE_2] = 20000;
    valuesDna[VDNA_EFFECTIVE_CAPTURE_3] = 2000000;

    float minusFactor = -1.0;

    _sequenceDna[SDNA_NNNNN] = valuesDna[VDNA_NONE];
    _sequenceDna[SDNA_NNNNM] = valuesDna[VDNA_ONE];
    _sequenceDna[SDNA_NNNNY] = minusFactor * valuesDna[VDNA_ONE];
    _sequenceDna[SDNA_NNNMN] = valuesDna[VDNA_ONE];
    _sequenceDna[SDNA_NNNMM] = valuesDna[VDNA_TWO];
    _sequenceDna[SDNA_NNNYN] = minusFactor * valuesDna[VDNA_ONE];
    _sequenceDna[SDNA_NNNYY] = minusFactor * valuesDna[VDNA_TWO];
    _sequenceDna[SDNA_NNMNN] = valuesDna[VDNA_ONE];
    _sequenceDna[SDNA_NNMNM] = valuesDna[VDNA_TWON1];
    _sequenceDna[SDNA_NNMMN] = valuesDna[VDNA_TWO];
    _sequenceDna[SDNA_NNMMM] = valuesDna[VDNA_THREE];
    _sequenceDna[SDNA_NNMMY] = minusFactor * valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_NNYNN] = minusFactor * valuesDna[VDNA_ONE];
    _sequenceDna[SDNA_NNYNY] = minusFactor * valuesDna[VDNA_TWON1];
    _sequenceDna[SDNA_NNYYN] = minusFactor * valuesDna[VDNA_TWO];
    _sequenceDna[SDNA_NNYYM] = valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_NNYYY] = minusFactor * valuesDna[VDNA_THREE];
    _sequenceDna[SDNA_NMNNN] = valuesDna[VDNA_ONE];
    _sequenceDna[SDNA_NMNNM] = valuesDna[VDNA_TWON2];
    _sequenceDna[SDNA_NMNMN] = valuesDna[VDNA_TWON1];
    _sequenceDna[SDNA_NMNMM] = valuesDna[VDNA_THREEN1];
    _sequenceDna[SDNA_NMMNN] = valuesDna[VDNA_TWO];
    _sequenceDna[SDNA_NMMNM] = valuesDna[VDNA_THREEN1];
    _sequenceDna[SDNA_NMMMN] = valuesDna[VDNA_THREEFREE];
    _sequenceDna[SDNA_NMMMM] = valuesDna[VDNA_FOUR];
    _sequenceDna[SDNA_NMMYN] = minusFactor * valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_NMMYM] = minusFactor * valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_NMMYY] = minusFactor * valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_NMYYN] = valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_NYNNN] = minusFactor * valuesDna[VDNA_ONE];
    _sequenceDna[SDNA_NYNNY] = minusFactor * valuesDna[VDNA_TWON2];
    _sequenceDna[SDNA_NYNYN] = minusFactor * valuesDna[VDNA_TWON1];
    _sequenceDna[SDNA_NYNYY] = minusFactor * valuesDna[VDNA_THREEN1];
    _sequenceDna[SDNA_NYMMN] = minusFactor * valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_NYYNN] = minusFactor * valuesDna[VDNA_TWO];
    _sequenceDna[SDNA_NYYNY] = minusFactor * valuesDna[VDNA_THREEN1];
    _sequenceDna[SDNA_NYYMN] = valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_NYYMM] = valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_NYYMY] = valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_NYYYN] = minusFactor * valuesDna[VDNA_THREEFREE];
    _sequenceDna[SDNA_NYYYY] = minusFactor * valuesDna[VDNA_FOUR];
    _sequenceDna[SDNA_MNNNN] = valuesDna[VDNA_ONE];
    _sequenceDna[SDNA_MNNNM] = valuesDna[VDNA_TWON3];
    _sequenceDna[SDNA_MNNMN] = valuesDna[VDNA_TWON2];
    _sequenceDna[SDNA_MNNMM] = valuesDna[VDNA_THREEN2];
    _sequenceDna[SDNA_MNMNN] = valuesDna[VDNA_TWON1];
    _sequenceDna[SDNA_MNMNM] = valuesDna[VDNA_THREEN2];
    _sequenceDna[SDNA_MNMMN] = valuesDna[VDNA_THREEN1];
    _sequenceDna[SDNA_MNMMM] = valuesDna[VDNA_FOURN1];
    _sequenceDna[SDNA_MNMMY] = minusFactor * valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_MNYYM] = valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_MMNNN] = valuesDna[VDNA_TWO];
    _sequenceDna[SDNA_MMNNM] = valuesDna[VDNA_THREEN2];
    _sequenceDna[SDNA_MMNMN] = valuesDna[VDNA_THREEN1];
    _sequenceDna[SDNA_MMNMM] = valuesDna[VDNA_FOURN1];
    _sequenceDna[SDNA_MMMNN] = valuesDna[VDNA_THREE];
    _sequenceDna[SDNA_MMMNM] = valuesDna[VDNA_FOURN1];
    _sequenceDna[SDNA_MMMMN] = valuesDna[VDNA_FOUR];
    _sequenceDna[SDNA_MMMMM] = valuesDna[VDNA_FIVE];
    _sequenceDna[SDNA_MMYYN] = valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_MYMMN] = minusFactor * valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_MYYNN] = valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_MYYNM] = valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_MYYNY] = valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_YNNNN] = minusFactor * valuesDna[VDNA_ONE];
    _sequenceDna[SDNA_YNNNY] = minusFactor * valuesDna[VDNA_TWON3];
    _sequenceDna[SDNA_YNNYN] = minusFactor * valuesDna[VDNA_TWON2];
    _sequenceDna[SDNA_YNNYY] = minusFactor * valuesDna[VDNA_THREEN2];
    _sequenceDna[SDNA_YNMMY] = minusFactor * valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_YNYNN] = minusFactor * valuesDna[VDNA_TWON1];
    _sequenceDna[SDNA_YNYNY] = minusFactor * valuesDna[VDNA_THREEN2];
    _sequenceDna[SDNA_YNYYN] = minusFactor * valuesDna[VDNA_THREEN1];
    _sequenceDna[SDNA_YNYYM] = valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_YNYYY] = minusFactor * valuesDna[VDNA_FOURN1];
    _sequenceDna[SDNA_YMMNN] = minusFactor * valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_YMMNM] = minusFactor * valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_YMMNY] = minusFactor * valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_YMYYN] = valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_YYNNN] = minusFactor * valuesDna[VDNA_TWO];
    _sequenceDna[SDNA_YYNNY] = minusFactor * valuesDna[VDNA_THREEN2];
    _sequenceDna[SDNA_YYNYN] = minusFactor * valuesDna[VDNA_THREEN1];
    _sequenceDna[SDNA_YYNYY] = minusFactor * valuesDna[VDNA_FOURN1];
    _sequenceDna[SDNA_YYMMN] = minusFactor * valuesDna[VDNA_POTENTIAL_CAPTURE];
    _sequenceDna[SDNA_YYYNN] = minusFactor * valuesDna[VDNA_THREE];
    _sequenceDna[SDNA_YYYNY] = minusFactor * valuesDna[VDNA_FOURN1];
    _sequenceDna[SDNA_YYYYN] = minusFactor * valuesDna[VDNA_FOUR];
    _sequenceDna[SDNA_YYYYY] = minusFactor * valuesDna[VDNA_FIVE];
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
        if (this->get_captured(blocked[i]).size() == 0)
            blocked_not_captured.push_back(blocked[i]);
    }

    this->_blocked_pos = blocked_not_captured;
    return blocked_not_captured;
}

bool Game::check_sequence(int x, int y, int dx, int dy, std::vector<e_cell> sequence) {
    for (int i = 1; i <= (int)sequence.size(); i++) {
        int nx = x + (i * dx);
        int ny = y + (i * dy);
        if (!is_in_grid(nx, ny) || _board.get(nx, ny).get() != sequence[i-1])
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
        if (this->check_sequence(x, y, dx, dy, sequence)) {
            captured.push_back((x + dx) + (y + dy) * 19);
            captured.push_back((x + 2 * dx) + (y + 2 * dy) * 19);
        }
    }
    this->_request.white_captured += (baseCell.get() == WHITE) ? captured.size() : 0;
    this->_request.black_captured += (baseCell.get() == BLACK) ? captured.size() : 0;
    return captured;
}

std::vector<int> Game::get_interesting_pos() {
    std::map<int, int> interesting_pos;

    for (int pos = 0; pos < 361; pos++) {
        if (pos != NONE && pos != BLOCKED) {
            int x = pos % 19;
            int y = pos / 19;
            if (this->get_board().get(x, y).get() != NONE) {
                for (int j = y - 2; j <= y + 2; j++) {
                    for (int i = x - 2; i <= x + 2; i++) {
                        if (is_in_grid(i, j)) {
                            if (this->get_board().get(i, j).get() == NONE) {
                                if (interesting_pos.find(i + j * 19) == interesting_pos.end())
                                    interesting_pos[i + j * 19] = 0;
                                else
                                    interesting_pos[i + j * 19] += 1;
                            }
                        }
                    }
                }
            }
        }
    }
    std::vector<std::pair<int, int> > pairs;

    for (auto& it : interesting_pos) {
        pairs.push_back(it);
    }
    //sort(pairs.begin(), pairs.end(), [](auto& a, auto& b) {
    //    return a.second > b.second;
    //});
    std::vector<int> res;
    for (size_t i = 0; i < pairs.size(); i++) {
        res.push_back(pairs[i].first);
    }
    if (res.size() == 0)
        res.push_back(180);
    return res;
}

void Game::print_board() {
    _board.print();
}


/* ************************ TEST ************************** */

void Game::init_test_board() {
    this->_board.set(8, 8, WHITE);
    this->_board.set(9, 9, WHITE);
    this->_board.set(10, 10, WHITE);
}