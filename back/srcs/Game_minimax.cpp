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
                    if (depth == 6)
                        board[pos] = tmp;
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

            this->print_board();
            int score = this->board_complex_heuristic(BLACKSTONE);

            std::map<e_cell, std::vector<int> > positions = this->get_all_positions_stone();
            std::vector<int> white = positions[WHITE];
            std::vector<int> black = positions[BLACK];
            std::cout << "WHITE: " << white.size() << std::endl;
            for (size_t i = 0; i < white.size(); i++)
                std::cout << white[i] << " ";
            std::cout << std::endl;

            std::cout << "BLACK: " << black.size() << std::endl;
            for (size_t i = 0; i < black.size(); i++)
                std::cout << black[i] << " ";
            std::cout << std::endl << std::endl;

            std::string color = is_maxi ? "WHITE" : "BLACK";
            std::cout << "complex heuristic for " << color << " at " << next_pos << " is " << score << std::endl << std::endl << std::endl;
            return std::make_pair(next_pos, score);
    }
}


//bool is_cutting_alpha_beta(int *alpha, int *beta, int score, int is_maxi) {
//    if (is_maxi)
//    {
//        *beta = std::min(*beta, score);
//        if (*alpha >= *beta)
//            return true;
//    }
//    else
//    {
//        *alpha = std::max(*alpha, score);
//        if (*alpha >= *beta)
//            return true;
//    }
//    return false;
//}

//bool maximum(const std::pair<int, int>& a, const std::pair<int, int>& b) {
//    return a.second < b.second;
//}

//bool minimum(const std::pair<int, int>& a, const std::pair<int, int>& b) {
//    return a.second > b.second;
//}
/* int Game::compute_best_move(int depth) {
    std::cout << "nb interesting pos: " << this->_interesting_pos.size() << std::endl;

    std::vector<int> board;
    for (int i = 0; i < 19*19; i++)
        board.push_back(-1);

    float best_score = INT_MIN;
    int best_pos = -1;
    for (std::vector<int>::iterator it = this->_interesting_pos.begin(); it != this->_interesting_pos.end(); it++) {
        float score = this->minimax(best_score, INT_MAX, depth, false, *it);
        if (score > best_score) {
            best_score = score;
            best_pos = *it;
        }
        std::cout << "--------------------------------------------\n\n\n\n\n";

        board[*it % 19 + *it / 19 * 19] = score;
    }

    std::cout << "best pos: " << best_pos << " - " << best_score << std::endl;

    // display board
    for (int y = 0; y < 19; y++) {
        for (int x = 0; x < 19; x++) {
            if (board[x + y * 19] != -1)
                std::cout << std::setw(4) << std::setfill('0') << board[x + y * 19] << " ";
            else
                std::cout << "---- ";
        }
        std::cout << std::endl;
    }
    return best_pos;
} */

//TODO: Need to add _blocked_pos check for the first iteration
/* std::pair<int, int> Game::compute_best_move(e_color color, int depth, bool is_maxi, int alpha, int beta) {
    std::map<int, int>  moves;

    for (std::vector<int>::iterator it = this->_interesting_pos.begin(); it != this->_interesting_pos.end(); it++) {
        int pos = *it;

        if (_board.get(pos).get() == NONE)
        {
            if (depth == 0)
            {
                int score = this->complex_heuristic(color, pos);
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
     if (depth == 3) {
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
    if (is_maxi)
        return std::make_pair(std::max_element(moves.begin(), moves.end(), maximum)->first, std::max_element(moves.begin(), moves.end(), maximum)->second);
    else
        return std::make_pair(std::min_element(moves.begin(), moves.end(), maximum)->first, std::min_element(moves.begin(), moves.end(), maximum)->second);
} */

