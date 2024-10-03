
#include <string>
#include <vector>

#include "request.hpp"
#include "utils.hpp"

#include "Game.hpp"
#include "Board.hpp"


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

int Game::heuristic(e_color color, int pos) {
    int x = pos % 19;
    int y = pos / 19;
    e_cell my = (color == WHITESTONE) ? WHITE : BLACK;
    e_cell other = (color == WHITESTONE) ? BLACK : WHITE;

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

std::pair<int, int> Game::compute_best_move(e_color color, int depth, int is_maxi, int alpha, int beta) {
    std::map<int, int>  moves;
    Game new_base_game(*this);
    
    new_base_game.unset_blocked_pos();

    for (std::vector<int>::iterator it = this->_interesting_pos.begin(); it != this->_interesting_pos.end(); it++) {
        int pos = *it;
        int x = pos % 19;
        int y = pos / 19;

        if (_board.get(x, y).get() == NONE)
        {
            if (depth == 0)
            {
                int score = this->heuristic(color, pos);
                moves[pos] = score;
            }
            else
            {
                Game new_game = Game(new_base_game);
                new_game.set(pos, color == WHITESTONE ? WHITE : BLACK);
                new_game.set(new_game.get_new_blocked_pos(color == WHITESTONE ? BLACKSTONE : WHITESTONE), BLOCKED);
                int score = this->compute_best_move(color == WHITESTONE ? BLACKSTONE : WHITESTONE, depth - 1, !is_maxi, alpha, beta).second;
                moves[pos] = score;
                if (is_maxi)
                {
                    beta = std::min(beta, score);
                    if (alpha >= beta) {
                        break;
                    }
                }
                else
                {
                    alpha = std::max(alpha, score);
                    if (alpha >= beta) {
                        break;
                    }
                }
                 
            }
        }
    }
    if (is_maxi)
        return std::make_pair(std::max_element(moves.begin(), moves.end(), maximum)->first, std::max_element(moves.begin(), moves.end(), maximum)->second);
    else
        return std::make_pair(std::min_element(moves.begin(), moves.end(), maximum)->first, std::min_element(moves.begin(), moves.end(), maximum)->second);
}

void Game::print_board() {
    _board.print();
}