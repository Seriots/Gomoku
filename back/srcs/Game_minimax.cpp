#include "Game.hpp"

bool Game::is_already_computed(size_t board_hash) const {
    return this->_transposition_table.find(board_hash) != this->_transposition_table.end();
}

std::pair<int, int> Game::negamax(int alpha, int beta, int depth, int is_maximizing, int next_pos, std::vector<int> &board, std::chrono::steady_clock::time_point start_time, int white_capture, int black_capture) {
    size_t board_hash = this->_board.get_hash_board();

    if (is_already_computed(board_hash)) {
        return this->_transposition_table[board_hash];
    }

    if (depth == 0) {
        int score = is_maximizing * this->board_complex_heuristic(_request.color);
        this->_transposition_table[board_hash] = std::make_pair(next_pos, score);
        return std::make_pair(next_pos, score);
    }

    int max_eval = INT_MIN;
    int best_pos = -1;
    std::vector<int> tmp_interesting_pos;
    if (depth == this->get_depth())
        tmp_interesting_pos = this->getter_interesting_pos();
    else
        tmp_interesting_pos = this->get_interesting_pos();
    
    this->sort_interesting_pos((is_maximizing == 1) ? _request.color : _request.color_opponent, tmp_interesting_pos);
    if ((int)tmp_interesting_pos.size() > this->_threshold[depth - 1]) {
        tmp_interesting_pos.resize(this->_threshold[depth - 1]);
    }

    for (std::vector<int>::iterator it = tmp_interesting_pos.begin(); it != tmp_interesting_pos.end(); it++) {
        int pos = *it;

        if (_board.get(pos).get() == NONE) {
            this->set(pos, (is_maximizing == 1) ? color_to_cell(_request.color) : color_to_cell(_request.color_opponent));

            std::vector<int> captured = this->get_captured(pos);
            int _tmp_white_capture = white_capture + ((_request.color == WHITESTONE) ? captured.size() : 0);
            int _tmp_black_capture = black_capture + ((_request.color == BLACKSTONE) ? captured.size() : 0);

            this->unset(captured);

            int tmp = -this->negamax(-beta, -alpha, depth - 1, -is_maximizing, pos, board, start_time, _tmp_white_capture, _tmp_black_capture).second;

            this->unset(pos);
            this->set(captured, (is_maximizing == 1) ? color_to_cell(_request.color_opponent) : color_to_cell(_request.color));

            if (depth == this->_depth) {
                board[pos] = tmp;
            }

            if (tmp > max_eval) {
                max_eval = tmp;
                best_pos = pos;
            }

            alpha = std::max(alpha, tmp);
            if (alpha >= beta) {
                break;
            }
        }

        // auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_time).count();
        // if (elapsed > 500) {
        //     return std::make_pair(best_pos, max_eval);
        // }
    }

    this->_transposition_table[board_hash] = std::make_pair(best_pos, max_eval);
    return std::make_pair(best_pos, max_eval);
}
