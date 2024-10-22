#include "Game.hpp"

// TODO remove next_pos

bool Game::is_already_computed(size_t board_hash) const {
    return this->_transposition_table.find(board_hash) != this->_transposition_table.end();
}

std::pair<int, int> Game::minimax(int alpha, int beta, int depth, bool is_maxi, int next_pos, std::vector<int> &board) {
    size_t board_hash = this->_board.get_hash_board();

    // std::cout << "board hash: " << board_hash << std::endl;

    //std::cout << "size of transposition: " << this->_transposition_table.size() << std::endl;
    if (is_already_computed(board_hash)) {
        //std::cout << "Already computed" << std::endl;
        return this->_transposition_table[board_hash];
    }

    if (depth) {
        if (is_maxi) {
            int max_eval = INT_MIN;
            int best_pos = -1;
            for (std::vector<int>::iterator it = this->_interesting_pos.begin(); it != this->_interesting_pos.end(); it++) {
                int pos = *it;
                if (_board.get(pos).get() == NONE)
                {
                    this->set(pos, BLACK);

                    int tmp = this->minimax(alpha, beta, depth - 1, false, pos, board).second;
                    this->unset(pos);
                    /* LOG */
                    if (depth == 5)
                        board[pos] = tmp;
                    /* ****** */
                    if (tmp > max_eval) {
                        max_eval = tmp;
                        best_pos = pos;
                    }
                    alpha = std::max(alpha, tmp);
                    if (beta <= alpha) {
                        break;
                    }
                }
            }

            this->_transposition_table[board_hash] = std::make_pair(best_pos, max_eval);
            return std::make_pair(best_pos, max_eval);
        } else {
            int min_eval = INT_MAX;
            int best_pos = -1;
            for (std::vector<int>::iterator it = this->_interesting_pos.begin(); it != this->_interesting_pos.end(); it++) {
                int pos = *it;
                if (_board.get(pos).get() == NONE)
                {
                    this->set(pos, WHITE);
                    int tmp = this->minimax(alpha, beta, depth - 1, true, pos, board).second;
                    this->unset(pos);

                    if (tmp < min_eval) {
                        min_eval = tmp;
                        best_pos = pos;
                    }
                    beta = std::min(beta, tmp);
                    if (beta <= alpha) {
                        break;
                    }
                }
            }

            this->_transposition_table[board_hash] = std::make_pair(best_pos, min_eval);
            return std::make_pair(best_pos, min_eval);
        }
    } else {

            int score = this->board_complex_heuristic(BLACKSTONE);

            /* LOG */
            // this->print_board();
            // std::map<e_cell, std::vector<int> > positions = this->get_all_positions_stone();
            // std::vector<int> white = positions[WHITE];
            // std::vector<int> black = positions[BLACK];
            // std::cout << "WHITE: " << white.size() << std::endl;
            // for (size_t i = 0; i < white.size(); i++)
            //     std::cout << white[i] << " ";
            // std::cout << std::endl;

            // std::cout << "BLACK: " << black.size() << std::endl;
            // for (size_t i = 0; i < black.size(); i++)
            //     std::cout << black[i] << " ";
            // std::cout << std::endl << std::endl;

            // std::string color = is_maxi ? "WHITE" : "BLACK";
            // std::cout << "complex heuristic for " << color << " at " << next_pos << " is " << score << std::endl << std::endl << std::endl;
            /* ******** */

            this->_transposition_table[board_hash] = std::make_pair(next_pos, score);
            return std::make_pair(next_pos, score);
    }
}

std::pair<int, int> Game::negamax(int alpha, int beta, int depth, int color, int next_pos, std::vector<int> &board, std::chrono::steady_clock::time_point start_time) {
    size_t board_hash = this->_board.get_hash_board();

    if (is_already_computed(board_hash)) {
        return this->_transposition_table[board_hash];
    }

    if (depth == 0) {
        int score = color * this->board_complex_heuristic(BLACKSTONE);
        this->_transposition_table[board_hash] = std::make_pair(next_pos, score);
        return std::make_pair(next_pos, score);
    }

    int max_eval = INT_MIN;
    int best_pos = -1;

    for (std::vector<int>::iterator it = this->_interesting_pos.begin(); it != this->_interesting_pos.end(); it++) {
        int pos = *it;

        if (_board.get(pos).get() == NONE) {
            this->set(pos, (color == 1) ? BLACK : WHITE);

            int tmp = -this->negamax(-beta, -alpha, depth - 1, -color, pos, board, start_time).second;

            this->unset(pos);

            if (depth == 5) {
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

        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_time).count();
        if (elapsed > 500) {
            return std::make_pair(best_pos, max_eval);
        }
    }

    this->_transposition_table[board_hash] = std::make_pair(best_pos, max_eval);
    return std::make_pair(best_pos, max_eval);
}

std::pair<int, int> Game::negascout(int alpha, int beta, int depth, bool is_maxi, int next_pos, std::vector<int> &board) {
    size_t board_hash = this->_board.get_hash_board();

    if (is_already_computed(board_hash)) {
        return this->_transposition_table[board_hash];
    }

    if (depth == 0) {
        int score = this->board_complex_heuristic(BLACKSTONE);
        this->_transposition_table[board_hash] = std::make_pair(next_pos, score);
        return std::make_pair(next_pos, score);
    }

    int bestScore = INT_MIN;
    int best_pos = -1;
    int b = beta;

    for (size_t i = 0; i < this->_interesting_pos.size(); i++) {
        int pos = this->_interesting_pos[i];
        if (_board.get(pos).get() == NONE) {
            this->set(pos, is_maxi ? BLACK : WHITE);

            // first evaluation
            int score = -negascout(-b, -alpha, depth - 1, !is_maxi, pos, board).second;
            if (score > alpha && score < beta && i > 0) { // re-search
                score = -negascout(-beta, -score, depth - 1, !is_maxi, pos, board).second;
            }

            if (depth == 5) {
                board[pos] = score;
            }
            if (score > bestScore) {
                bestScore = score;
                best_pos = pos;
            }
            alpha = std::max(alpha, score);
            this->unset(pos);

            if (alpha >= beta) {
                break;
            }
            b = alpha + 1;

        }
    }

    this->_transposition_table[board_hash] = std::make_pair(best_pos, bestScore);
    return std::make_pair(best_pos, bestScore);
}
