#include "Game.hpp"

bool Game::is_already_computed(size_t board_hash) const {
    return this->_transposition_table.find(board_hash) != this->_transposition_table.end();
}

void Game::display_negamax_board(std::vector<int> &board) {

    std::vector<int> interesting_pos = this->getter_interesting_pos();

    for (int y = 0; y < 19; y++) {
        for (int x = 0; x < 19; x++) {
            float displayColor;

            std::vector<int>::iterator it = std::find(interesting_pos.begin(), interesting_pos.end(), x + y * 19);

            if (it == interesting_pos.end())
                displayColor = 0;
            else
                displayColor = 1.0 - ((float)(it - interesting_pos.begin()) / (float)interesting_pos.size());
            
            if (displayColor > 0.99)
                std::cout << "\033[0;35m"; // magenta
            else if (displayColor > 0.9)
                std::cout << "\033[0;31m"; // red
            else if (displayColor > 0.8)
                std::cout << "\033[0;33m"; // yellow
            else if (displayColor > 0.7)
                std::cout << "\033[0;32m"; // green
            else if (displayColor > 0.35)
                std::cout << "\033[0;34m"; // blue

            if (board[x + y * 19] != -1)
                std::cout << std::setw(8) << std::setfill(' ') << board[x + y * 19] << "\033[0m" << " ";
            else if (this->get_board().get(x, y).get() == WHITE)
                std::cout << "oooooooo" << "\033[0m" << " ";
            else if (this->get_board().get(x, y).get() == BLACK)
                std::cout << "********" << "\033[0m" << " ";
            else if (this->get_board().get(x, y).get() == BLOCKED)
                std::cout << "xxxxxxxx" << "\033[0m" << " ";
            else
                std::cout << "--------" << "\033[0m" << " ";
            
        }
        std::cout << std::endl;
    }
}
int a = 0;

std::pair<int, int> Game::negamax(t_negamaxInformation info, int next_pos, t_captureCount capture) {
    size_t              board_hash;
    std::vector<int>    tmp_interesting_pos;
    std::pair<int, int> res;
    int                 score;
    int                 max_eval;
    int                 best_pos;
    t_captureCount      tmp_capture;
    std::vector<int>    captured;

    board_hash = this->_board.get_hash_board();

    if (is_already_computed(board_hash)) {
        return this->_transposition_table[board_hash];
    }

    if (info.depth == 0 || capture.white >= 10 || capture.black >= 10) {
        score = info.is_maximizing * this->board_complex_heuristic(_request.color, capture.white, capture.black);
        res = std::make_pair(next_pos, score);
        this->_transposition_table[board_hash] = res;
        return res;
    }

    max_eval = INT_MIN;
    best_pos = -1;
    
    tmp_interesting_pos = this->get_interesting_pos();

    this->sort_interesting_pos((info.is_maximizing == 1) ? _request.color : _request.color_opponent, tmp_interesting_pos);
    if ((int)tmp_interesting_pos.size() > this->_threshold[info.depth - 1]) {
        tmp_interesting_pos.resize(this->_threshold[info.depth - 1]);
    }

    for (std::vector<int>::iterator it = tmp_interesting_pos.begin(); it != tmp_interesting_pos.end(); it++) {
        int pos = *it;

        this->set(pos, (info.is_maximizing == 1) ? color_to_cell(_request.color) : color_to_cell(_request.color_opponent));

        captured = this->get_captured(pos);
        tmp_capture.white = capture.white;
        tmp_capture.black = capture.black; 

        if ((info.is_maximizing == 1 && _request.color == WHITESTONE) || (info.is_maximizing == -1 && _request.color == BLACKSTONE))
            tmp_capture.black += captured.size();
        else if ((info.is_maximizing == 1 && _request.color == BLACKSTONE) || (info.is_maximizing == -1 && _request.color == WHITESTONE))
            tmp_capture.white += captured.size();

        this->unset(captured);

        score = -this->negamax({-info.beta, -info.alpha, info.depth - 1, -info.is_maximizing}, pos, tmp_capture).second;

        this->set(captured, (info.is_maximizing == 1) ? color_to_cell(_request.color_opponent) : color_to_cell(_request.color));
        this->unset(pos);

        if (score > max_eval) {
            max_eval = score;
            best_pos = pos;
        }

        info.alpha = std::max(info.alpha, score);
        if (info.alpha >= info.beta) {
            a++;
            break;
        }
    }

    res = std::make_pair(best_pos, max_eval);
    this->_transposition_table[board_hash] = res;
    return res;
}

int Game::fdNegamax(t_negamaxInformation info, t_captureCount capture) {
    std::vector<int>    board(361, -1);
    std::vector<int>    captured;
    int                 score;
    int                 pos;
    t_captureCount      tmp_capture;
    int                 best_pos;
    int                 limit;
    
    if (info.depth == 0) {
        return (this->_interesting_pos.size() > 0 ? *this->_interesting_pos.begin() : -1);
    }
    
    limit = this->_threshold[info.depth - 1];

    best_pos = -1;
    for (std::vector<int>::iterator it = this->_interesting_pos.begin(); it != this->_interesting_pos.end() && limit-- > 0; it++) {
        pos = *it;
        
        this->set(pos, color_to_cell(_request.color));
        captured = this->get_captured(pos);
        tmp_capture = capture;
        
        if (_request.color == WHITESTONE)
            tmp_capture.white += captured.size();
        else
            tmp_capture.black += captured.size();

        this->unset(captured);
        
        score = -this->negamax({-info.beta, -info.alpha, info.depth - 1, -info.is_maximizing}, pos, tmp_capture).second;

        this->set(captured, color_to_cell(_request.color_opponent));
        this->unset(pos);
        board[pos] = score;

        if (best_pos == -1 || score > board[best_pos]) {
            best_pos = pos;
        }

        info.alpha = std::max(info.alpha, score);
    }
        std::cout << a << std::endl;
    this->display_negamax_board(board);

    return best_pos;
}
