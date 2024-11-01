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

            if (board[x + y * 19] != -2147483647)
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

int Game::negamax(t_negamaxInformation info, t_captureCount capture, int currPos) {
    (void)currPos;
    size_t              board_hash;
    std::vector<int>    tmp_interesting_pos;
    int                 score;
    int                 max_eval;
    t_captureCount      tmp_capture;
    std::vector<int>    captured;
    int                 limit;

    board_hash = this->_board.get_hash_board();
    if (is_already_computed(board_hash)) {
        return this->_transposition_table[board_hash];
    }

    else if (info.depth == 0) {
        score = info.is_maximizing * this->board_complex_heuristic(_request.color, capture.white, capture.black);
        this->_transposition_table[board_hash] = score;
        return score;
    }

    max_eval = INT_MIN;
    
    tmp_interesting_pos = this->get_interesting_pos();

    if ((int)tmp_interesting_pos.size() > this->_threshold[info.depth - 1])
        this->sort_interesting_pos((info.is_maximizing == 1) ? _request.color : _request.color_opponent, tmp_interesting_pos, capture);
    
    limit = this->_threshold[info.depth - 1];
    for (std::vector<int>::iterator it = tmp_interesting_pos.begin(); it != tmp_interesting_pos.end() && limit-- > 0; it++) {
        int pos = *it;

        captured = this->get_captured(pos, (info.is_maximizing == 1) ? _request.color : _request.color_opponent);
        tmp_capture = capture;
        if ((info.is_maximizing == 1 && _request.color == WHITESTONE) || (info.is_maximizing == -1 && _request.color == BLACKSTONE))
            tmp_capture.black += captured.size();
        else if ((info.is_maximizing == 1 && _request.color == BLACKSTONE) || (info.is_maximizing == -1 && _request.color == WHITESTONE))
            tmp_capture.white += captured.size();

        this->set(pos, (info.is_maximizing == 1) ? color_to_cell(_request.color) : color_to_cell(_request.color_opponent));
        this->unset(captured);

        if (tmp_capture.white >= 10 || tmp_capture.black >= 10)
            score = info.is_maximizing * this->board_complex_heuristic(_request.color, tmp_capture.white, tmp_capture.black) * (info.depth + 1);
        else if (check_win_by_alignement(pos, (info.is_maximizing == 1 ? color_to_cell(_request.color) : color_to_cell(_request.color_opponent))))
            score = info.is_maximizing * this->board_complex_heuristic(_request.color, tmp_capture.white, tmp_capture.black) * (info.depth + 1);
        else 
            score = -this->negamax({-info.beta, -info.alpha, info.depth - 1, -info.is_maximizing}, tmp_capture, pos);

        this->set(captured, (info.is_maximizing == 1) ? color_to_cell(_request.color_opponent) : color_to_cell(_request.color));
        this->unset(pos);

        if (score > max_eval)
            max_eval = score;

        info.alpha = std::max(info.alpha, score);
        if (info.alpha >= info.beta)
            break;
    }
    this->_transposition_table[board_hash] = max_eval;
    return max_eval;
}

int Game::fdNegamax(t_negamaxInformation info, t_captureCount capture) {
    std::vector<int>    board(361, -2147483647);
    std::vector<int>    captured;
    int                 score;
    int                 pos;
    t_captureCount      tmp_capture;
    int                 best_pos;
    int                 limit;
    if (info.depth == 0) {
        return (this->_interesting_pos.size() > 0 ? *this->_interesting_pos.begin() : -1);
    }

    if (this->_interesting_pos.size() == 1)
        return *this->_interesting_pos.begin();
    
    limit = this->_threshold[info.depth - 1];

    best_pos = -1;
    for (std::vector<int>::iterator it = this->_interesting_pos.begin(); it != this->_interesting_pos.end() && limit-- > 0; it++) {
        pos = *it;
        
        captured = this->get_captured(pos, _request.color);
        tmp_capture = capture;
        if (_request.color == BLACKSTONE)
            tmp_capture.black += captured.size();
        else
            tmp_capture.white += captured.size();

        this->set(pos, color_to_cell(_request.color));
        this->unset(captured);
        if (tmp_capture.white >= 10 || tmp_capture.black >= 10) {
            this->set(captured, color_to_cell(_request.color_opponent));
            this->unset(pos);
            return pos;
        }
        if (check_win_by_alignement(pos, color_to_cell(_request.color))) {
            std::vector<int>    prevent = get_capture_prevent_win_pos(pos, color_to_cell(_request.color));
            if (!((prevent.size() + 1) * 2 + (_request.color == WHITESTONE ? tmp_capture.black : tmp_capture.white) >= 10)) {
                this->set(captured, color_to_cell(_request.color_opponent));
                this->unset(pos);
                return pos;
            }
        }

        score = -this->negamax({-info.beta, -info.alpha, info.depth - 1, -info.is_maximizing}, tmp_capture, pos);

        this->set(captured, color_to_cell(_request.color_opponent));
        this->unset(pos);
        board[pos] = score;

        if (best_pos == -1 || score > board[best_pos]) {
            best_pos = pos;
        }

        info.alpha = std::max(info.alpha, score);
    }
    this->display_negamax_board(board);
    return best_pos;
}
