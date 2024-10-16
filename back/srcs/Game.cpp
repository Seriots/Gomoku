
#include <string>
#include <vector>

#include "request.hpp"
#include "utils.hpp"

#include "Game.hpp"
#include "Board.hpp"

/* ************************ Constructors/Destructor ************************** */
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
    _dna[BLOCK_FREE_THREE] = 1900;
    _dna[BLOCK_FREE_FOUR] = 5900;
    _dna[BLOCK_CAPTURE] = 6000;
    _dna[BLOCK_WIN] = 89000;
    _dna[SETUP_CAPTURE] = 200;
    _dna[IS_CAPTURABLE] = -3000;
}

Game::Game(t_request &request)
{
    _request = request;
    _board = Board(request.white, request.black);
    _interesting_pos = this->get_interesting_pos();
    this->init_dna();
}

Game::Game(const Game &g) {
    _board = g.get_board();
    _dna = g._dna;
    _request = g._request;
    _interesting_pos = g._interesting_pos;
}

Game::~Game() { }

void Game::operator= (const Game &g) {
    _board = g.get_board();
    _dna = g._dna;
    _request = g._request;
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

/* ************************ Algorithme ************************** */
bool Game::check_free_three(int x, int y, int ax, int ay, e_cell color) {
    int inv_color = (color == WHITE) ? BLACK : WHITE;
    std::vector<e_cell> axis_values;

    for (int i = -4; i <= 4; i++) {
        if (i == 0)
            axis_values.push_back(color);
        else if (x + (i * ax) >= 0 && x + (i * ax) < 19 && y + (i * ay) >= 0 && y + (i * ay) < 19)
            axis_values.push_back(this->_board.get(x + (i * ax), y + (i * ay)).get());
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
        if (this->check_sequence(x, y, dx, dy, sequence)) {
            captured.push_back((x + dx) + (y + dy) * 19);
            captured.push_back((x + 2 * dx) + (y + 2 * dy) * 19);
        }
    }
    return captured;
}

bool operator==(const t_data &a, const t_data &b) {
    return a.pos == b.pos && a.color == b.color;
}



bool maximum(const std::pair<int, int>& a, const std::pair<int, int>& b) {
    return a.second < b.second;
}

bool minimum(const std::pair<int, int>& a, const std::pair<int, int>& b) {
    return a.second > b.second;
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
                        if (i >= 0 && i < 19 && j >= 0 && j < 19) {
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
    sort(pairs.begin(), pairs.end(), [](auto& a, auto& b) {
        return a.second > b.second;
    });
    std::vector<int> res;
    for (size_t i = 0; i < pairs.size(); i++) {
        res.push_back(pairs[i].first);
    }
    return res;
}

bool is_cutting_alpha_beta(int *alpha, int *beta, int score, int is_maxi) {
    if (is_maxi)
    {
        *beta = std::min(*beta, score);
        if (*alpha >= *beta)
            return true;
    }
    else
    {
        *alpha = std::max(*alpha, score);
        if (*alpha >= *beta)
            return true;
    }
    return false;
}

int Game::complex_heuristic(int pos) {
    std::vector<std::vector<int> >  directions;

    int x = pos % 19;
    int y = pos / 19;
    e_cell color =  this->get_board().get(x, y).get();
    e_cell other_color =  color == WHITE ? BLACK : WHITE;

    int my_captured = get_captured_count_by_color(this->_request, color);
    //int other_captured = get_captured_count_by_color(this->_request, other_color);

    int linear_distance = get_linear_distance((t_position){x, y}, this->get_board().get_center());
    int score = 20 - linear_distance;

    directions = {{-1, 0},{1, 0},{0, -1},{0, 1},{-1, -1},{1, 1},{1, -1},{-1, 1}};
    std::vector<t_direction_info> dir_info;
    for (size_t i = 0; i < directions.size(); i++) {
        int my_free_alignement = 0;
        int my_real_alignement = 0;
        int other_real_alignement = 0;
        bool capture = false;
        bool setup_capture = false;
        bool is_capturable = false;
        bool nothing = false;
        bool block_capture = false;

        bool found_none = false;

        int dx = directions[i][0];
        int dy = directions[i][1];

        for (int forward = 1; forward < 5; forward++) {
            int nx = x + (forward * dx);
            int ny = y + (forward * dy);
            if (nx < 0 || nx >= 19 || ny < 0 || ny >= 19)
                break;
            e_cell cell = this->get_board().get(nx, ny).get();
            if (cell == NONE) {
                if (my_free_alignement == 0 && other_real_alignement == 0)
                    nothing = true;
                if (found_none)
                    break;
                else if (other_real_alignement != 0) {
                    if (other_real_alignement == 2)
                        setup_capture = true;
                    break;
                }
                else
                    found_none = true;
            }
            else if (cell == color) {
                if (other_real_alignement != 0) {
                    if (other_real_alignement == 2)
                        capture = true;
                    break;
                }
                my_free_alignement++;
                if (!found_none)
                    my_real_alignement++;
            }
            else if (cell == other_color) {
                if (my_real_alignement == 0)
                    other_real_alignement++;
                else {
                    if (my_real_alignement == 2)
                        block_capture = true;
                    if (my_real_alignement == 1)
                        is_capturable = true;
                    break;
                }
            }

        }
        dir_info.push_back({my_free_alignement, my_real_alignement, other_real_alignement, capture, setup_capture, is_capturable, nothing, block_capture});
    }
    int any_alignement = 0;
    int align_five = 0;
    int free_four = 0;
    int free_three = 0;
    int capture = 0;
    int block_win = 0;
    int block_free_four = 0;
    int block_free_three = 0;
    int block_capture = 0;
    int setup_capture = 0;
    int is_capturable = 0;
    for (int i = 0; i < 8; i+=2) {
        any_alignement += dir_info[i].my_free_alignement;
        any_alignement += dir_info[i+1].my_free_alignement;

        int real_align = dir_info[i].my_real_alignement + dir_info[i+1].my_real_alignement;
        align_five += real_align >= 5 ? 1 : 0;
        free_four += real_align == 4 ? 1 : 0;
        free_three += real_align == 3 ? 1 : 0;

        capture += dir_info[i].capture == true ? 1 : 0;
        capture += dir_info[i + 1].capture == true ? 1 : 0;

        int other_real_align = dir_info[i].other_real_alignement + dir_info[i+1].other_real_alignement;
        std::cout << "other_real_align: " << other_real_align << std::endl;
        block_win += other_real_align >= 5 ? 1 : 0;
        block_free_four += other_real_align == 4 ? 1 : 0;
        block_free_three += other_real_align == 3 ? 1 : 0;

        setup_capture += dir_info[i].setup_capture ? 1 : 0;
        setup_capture += dir_info[i+1].setup_capture ? 1 : 0;

        is_capturable += dir_info[i].is_capturable ? 1 : 0;
        is_capturable += dir_info[i+1].is_capturable ? 1 : 0;

        block_capture += dir_info[i].block_capture ? 1 : 0;
        block_capture += dir_info[i+1].block_capture ? 1 : 0;
    }

    score += any_alignement * _dna[ANY_ALIGNEMENT];
    score += align_five * _dna[ALIGN_FIVE];
    score += free_four * _dna[FREE_FOUR];
    score += free_three * _dna[FREE_THREE];
    if (my_captured == 0)
        score += capture * _dna[CAPTURE_TOTAL_2];
    else if (my_captured == 2)
        score += capture * _dna[CAPTURE_TOTAL_4];
    else if (my_captured == 4)
        score += capture * _dna[CAPTURE_TOTAL_6];
    else if (my_captured == 6)
        score += capture * _dna[CAPTURE_TOTAL_8];
    else if (my_captured == 8)
        score += capture * _dna[CAPTURE_TOTAL_10];

    score += block_win * _dna[BLOCK_WIN];
    score += block_free_four * _dna[BLOCK_FREE_FOUR];
    score += block_free_three * _dna[BLOCK_FREE_THREE];
    score += setup_capture * _dna[SETUP_CAPTURE];
    score += is_capturable * _dna[IS_CAPTURABLE];

    score += block_capture * _dna[BLOCK_CAPTURE];

    return score;
}


int Game::simple_heuristic(e_color color, int pos) {

    int x = pos % 19;
    int y = pos / 19;
    e_cell my = color == WHITESTONE ? WHITE : BLACK;
    e_cell other = (my == WHITE) ? BLACK : WHITE;

    int score = 0;
    for (int j = y - 4; j <= y + 4; j++) {
        for (int i = x - 4; i <= x + 4; i++) {
            if (i >= 0 && i < 19 && j >= 0 && j < 19) {
                if (_board.get(i, j).get() ==  my)
                    score += (100 - abs(y - j) * abs(x - i) * 2);
                else if (_board.get(i, j).get() == other)
                    score += (100 - abs(y - j) * abs(x - i));
            }
        }
    }

    return score;
}

std::pair<int, int> Game::minimax(int alpha, int beta, int depth, bool is_maxi, int next_pos) {
    if (depth) {
        std::cout << "Depth: " << depth << std::endl;
        if (is_maxi) {
            int max_eval = -100000;
            int best_pos = -1;
            for (std::vector<int>::iterator it = this->_interesting_pos.begin(); it != this->_interesting_pos.end(); it++) {
                int pos = *it;
                if (_board.get(pos).get() == NONE)
                {
                    this->set(pos, WHITE);
                    int tmp = this->minimax(alpha, beta, depth - 1, false, pos).second;
                    this->set(pos, NONE);
                    if (tmp > max_eval) {
                        max_eval = tmp;
                        best_pos = pos;
                    }
                    alpha = std::max(alpha, tmp);
                    if (beta <= alpha)
                        break;
                }
            }
            return std::make_pair(best_pos, max_eval);
        } else {
            int min_eval = 100000;
            int best_pos = -1;
            for (std::vector<int>::iterator it = this->_interesting_pos.begin(); it != this->_interesting_pos.end(); it++) {
                int pos = *it;
                if (_board.get(pos).get() == NONE)
                {
                    this->set(pos, BLACK);
                    int tmp = this->minimax(alpha, beta, depth - 1, true, pos).second;
                    this->set(pos, NONE);
                    if (tmp < min_eval) {
                        min_eval = tmp;
                        best_pos = pos;
                    }
                    beta = std::min(beta, tmp);
                    if (beta <= alpha)
                        break;
                }
            }
            return std::make_pair(best_pos, min_eval);
        }
    } else {
        int simple_score = this->simple_heuristic(is_maxi ? WHITESTONE : BLACKSTONE, next_pos);
        std::cout << "Pos: " << next_pos << std::endl;
        std::cout << "Score: " << simple_score << std::endl << std::endl;
        return std::make_pair(next_pos, simple_score);
    }
}

//TODO: Need to add _blocked_pos check for the first iteration
/* std::pair<int, int> Game::compute_best_move(e_color color, int depth, bool is_maxi, int alpha, int beta) {
    std::map<int, int>  moves;

    for (std::vector<int>::iterator it = this->_interesting_pos.begin(); it != this->_interesting_pos.end(); it++) {
        int pos = *it;

        if (_board.get(pos).get() == NONE)
        {
            if (depth == 0)
            {
                int score = this->simple_heuristic(pos);
                moves[pos] = score;
            }
            else
            {
                this->set(pos, color == WHITESTONE ? WHITE : BLACK);
                int score = this->compute_best_move(color == WHITESTONE ? BLACKSTONE : WHITESTONE, depth - 1, !is_maxi, alpha, beta).second;
                this->set(pos, NONE);
                moves[pos] = score;
                if (is_cutting_alpha_beta(&alpha, &beta, score, is_maxi))
                    break;
            }
        }
    }
     if (depth == 0 || depth == 2) {
         for (int y = 0; y < 19; y++) {
             for (int x = 0; x < 19; x++) {
                 if (moves.count(x + y * 19) > 0)
                     std::cout << std::setw(4) << std::setfill('0')<< moves[x + y * 19] << " ";
                 else
                     std::cout << "---- ";
             }
             std::cout << std::endl;
         }
         std::cout << std::endl;
     }
    if (depth == 2)
        return std::make_pair(std::min_element(moves.begin(), moves.end(), maximum)->first, std::max_element(moves.begin(), moves.end(), maximum)->second);
    if (is_maxi)
        return std::make_pair(std::max_element(moves.begin(), moves.end(), maximum)->first, std::max_element(moves.begin(), moves.end(), maximum)->second);
    else
        return std::make_pair(std::min_element(moves.begin(), moves.end(), maximum)->first, std::min_element(moves.begin(), moves.end(), maximum)->second);
} */

void Game::print_board() {
    _board.print();
}
