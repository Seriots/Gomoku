#include "Game.hpp"

// TODO remove next_pos
std::pair<int, int> Game::minimax(int alpha, int beta, int depth, bool is_maxi, int next_pos, std::vector<int> &board) {
    if (depth) {
        if (is_maxi) {
            int max_eval = INT_MIN;
            int best_pos = -1;
            //this->sort_interesting_pos(BLACKSTONE);
            for (std::vector<int>::iterator it = this->_interesting_pos.begin(); it != this->_interesting_pos.end(); it++) {
                int pos = *it;
                if (_board.get(pos).get() == NONE)
                {
                    this->set(pos, BLACK);
                    int tmp = this->minimax(alpha, beta, depth - 1, false, pos, board).second;
                    this->unset(pos);
                    /* LOG */
                    //if (depth == 1)
                    //    board[pos] = tmp;
                    /* ****** */
                    if (tmp > max_eval) {
                        max_eval = tmp;
                        best_pos = pos;
                    }
                    alpha = std::max(alpha, tmp);
                    if (beta <= alpha) {
                        //std::cout << "pruning at " << pos << std::endl;
                        break;
                    }
                }
            }
            return std::make_pair(best_pos, max_eval);
        } else {
            int min_eval = INT_MAX;
            int best_pos = -1;
            //this->sort_interesting_pos(WHITESTONE);
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
                        //std::cout << "pruning at " << pos << std::endl;
                        break;
                    }
                }
            }
            return std::make_pair(best_pos, min_eval);
        }
    } else {

            //this->print_board();
            int score = this->board_complex_heuristic(BLACKSTONE);

            /* LOG */
            //std::map<e_cell, std::vector<int> > positions = this->get_all_positions_stone();
            //std::vector<int> white = positions[WHITE];
            //std::vector<int> black = positions[BLACK];
            //std::cout << "WHITE: " << white.size() << std::endl;
            //for (size_t i = 0; i < white.size(); i++)
            //    std::cout << white[i] << " ";
            //std::cout << std::endl;

            //std::cout << "BLACK: " << black.size() << std::endl;
            //for (size_t i = 0; i < black.size(); i++)
            //    std::cout << black[i] << " ";
            //std::cout << std::endl << std::endl;

            //std::string color = is_maxi ? "WHITE" : "BLACK";
            //std::cout << "complex heuristic for " << color << " at " << next_pos << " is " << score << std::endl << std::endl << std::endl;
            /* ******** */
            return std::make_pair(next_pos, score);

bool Game::is_already_computed(size_t board_hash) const {
    return this->_transposition_table.find(board_hash) != this->_transposition_table.end();
}

std::pair<int, int> Game::negamax(int alpha, int beta, int depth, int is_maximizing, int next_pos, std::vector<int> &board, std::chrono::steady_clock::time_point start_time, int white_capture, int black_capture) {
    size_t board_hash = this->_board.get_hash_board();

    if (is_already_computed(board_hash)) {
        return this->_transposition_table[board_hash];
    }

    if (depth == 0) {
        int score = is_maximizing * this->board_complex_heuristic(BLACKSTONE);
        this->_transposition_table[board_hash] = std::make_pair(next_pos, score);
        return std::make_pair(next_pos, score);
    }

bool Game::is_already_computed(size_t board_hash) const {
    return this->_transposition_table.find(board_hash) != this->_transposition_table.end();
}

std::pair<int, int> Game::negamax(int alpha, int beta, int depth, int is_maximizing, int next_pos, std::vector<int> &board, std::chrono::steady_clock::time_point start_time, int white_capture, int black_capture) {
    size_t board_hash = this->_board.get_hash_board();

    if (is_already_computed(board_hash)) {
        return this->_transposition_table[board_hash];
    }

    if (depth == 0) {
        int score = is_maximizing * this->board_complex_heuristic(BLACKSTONE);
        this->_transposition_table[board_hash] = std::make_pair(next_pos, score);
        return std::make_pair(next_pos, score);
    }

    int max_eval = INT_MIN;
    int best_pos = -1;

    std::vector<int> tmp_interesting_pos = this->get_interesting_pos();
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
            this->set(captured, (is_maximizing == 1) ? color_to_cell(_request.color) : color_to_cell(_request.color_opponent));

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
