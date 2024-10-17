
#include <string>
#include <vector>

#include "request.hpp"
#include "utils.hpp"

#include "Game.hpp"
#include "Board.hpp"

/*
    For each direction, we compute the score information
    @args: dir_info -> the direction information
    @return: the score information
*/
t_score_info Game::compute_score_information(std::vector<t_direction_info> &dir_info) {
    t_score_info score_info = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (int i = 0; i < 8; i+=2) {
        score_info.any_alignement += dir_info[i].my_free_alignement;
        score_info.any_alignement += dir_info[i+1].my_free_alignement;

        int real_align = dir_info[i].my_real_alignement + dir_info[i+1].my_real_alignement;
        score_info.align_five += real_align >= 5 ? 1 : 0;
        score_info.free_four += real_align == 4 ? 1 : 0;
        score_info.free_three += real_align == 3 ? 1 : 0;

        score_info.capture += dir_info[i].capture == true ? 1 : 0;
        score_info.capture += dir_info[i + 1].capture == true ? 1 : 0;

        int other_real_align = dir_info[i].other_real_alignement + dir_info[i+1].other_real_alignement;
        score_info.block_win += other_real_align >= 5 ? 1 : 0;
        score_info.block_free_four += other_real_align == 4 ? 1 : 0;
        score_info.block_free_three += other_real_align == 3 ? 1 : 0;

        score_info.setup_capture += dir_info[i].setup_capture ? 1 : 0;
        score_info.setup_capture += dir_info[i+1].setup_capture ? 1 : 0;

        score_info.is_capturable += dir_info[i].is_capturable ? 1 : 0;
        score_info.is_capturable += dir_info[i+1].is_capturable ? 1 : 0;

        score_info.block_capture += dir_info[i].block_capture ? 1 : 0;
        score_info.block_capture += dir_info[i+1].block_capture ? 1 : 0;
    }

    return score_info;
}
/*
    Compute the score of the position
    @args: score_info -> the score information
    @args: my_captured -> the number of captured stones
    @return: the score of the position
*/
int Game::compute_score(t_score_info &score_info, int &my_captured) {
    int score = 0;

    score += score_info.any_alignement * _dna[ANY_ALIGNEMENT];
    score += score_info.align_five * _dna[ALIGN_FIVE];
    score += score_info.free_four * _dna[FREE_FOUR];
    score += score_info.free_three * _dna[FREE_THREE];
    if (my_captured == 0)
        score += score_info.capture * _dna[CAPTURE_TOTAL_2];
    else if (my_captured == 2)
        score += score_info.capture * _dna[CAPTURE_TOTAL_4];
    else if (my_captured == 4)
        score += score_info.capture * _dna[CAPTURE_TOTAL_6];
    else if (my_captured == 6)
        score += score_info.capture * _dna[CAPTURE_TOTAL_8];
    else if (my_captured == 8)
        score += score_info.capture * _dna[CAPTURE_TOTAL_10];
    
    score += score_info.block_win * _dna[BLOCK_WIN];
    score += score_info.block_free_four * _dna[BLOCK_FREE_FOUR];
    score += score_info.block_free_three * _dna[BLOCK_FREE_THREE];
    score += score_info.setup_capture * _dna[SETUP_CAPTURE];
    score += score_info.is_capturable > 0 ? _dna[IS_CAPTURABLE] : 0;

    score += score_info.block_capture * _dna[BLOCK_CAPTURE];
    return score;
}

static t_direction_info init_direction_info() {
    return {0, 0, 0, false, false, false, false};
}

/*
    Compute the direction information for a given position
    @args: grid_pos -> the position to compute the direction information
    @args: my_color -> the color of the player
    @args: other_color -> the color of the other player
    @return: the direction information
*/
std::vector<t_direction_info> Game::compute_dirs_info(t_position &grid_pos, e_cell &my_color, e_cell &other_color) {
    std::vector<std::vector<int> >  directions;
    std::vector<t_direction_info>   dirs_info;

    (void)other_color;

    directions = {{-1, 0},{1, 0},{0, -1},{0, 1}, {-1, -1},{1, 1},{1, -1},{-1, 1}};
    for (size_t i = 0; i < directions.size(); i++) {
        t_direction_info di = init_direction_info();

        bool found_none = false;
        
        int dx = directions[i][0];
        int dy = directions[i][1];

        for (int forward = 1; forward < 5; forward++) {
            int nx = grid_pos.x + (forward * dx);
            int ny = grid_pos.y + (forward * dy);
            if (!is_in_grid(nx, ny))
                break;
            e_cell cell = this->_board.get(nx, ny).get();
            if (cell == NONE) {
                if (found_none)
                    break;
                else if (di.other_real_alignement != 0) {
                    if (di.other_real_alignement == 2)
                        di.setup_capture = true;
                    break;
                } 
                else
                    found_none = true;
            }
            else if (cell == my_color) {
                if (di.other_real_alignement != 0) {
                    if (di.other_real_alignement == 2)
                        di.capture = true;
                    di.other_real_alignement--;
                    break;
                }
                di.my_free_alignement++;
                if (!found_none)
                    di.my_real_alignement++;
            }
            else {
                if (found_none)
                    break;
                if (di.my_real_alignement != 0) {
                    if (di.my_real_alignement == 2)
                        di.block_capture = true;
                    else if (di.my_real_alignement == 1)
                        di.is_capturable = true;
                    break;
                }
                di.other_real_alignement++;
            } 
        }
        dirs_info.push_back(di);
    }
    return dirs_info;
}

/*
    In the complex heuristic we compute the score of the position with many parameters
    @args: color -> the color of the player
    @args: pos -> the position to compute the score
    @return: the score of the position
*/
int Game::complex_heuristic(e_color color, int &pos) {

    t_position grid_pos = {pos % 19, pos / 19};

    e_cell my_color = color == WHITESTONE ? WHITE : BLACK;
    e_cell other_color = (my_color == WHITE ? BLACK : WHITE);

    int my_captured = get_captured_count_by_color(this->_request, color);
    //int other_captured = get_captured_count_by_color(this->_request, other_color);

    int score = 20 - get_linear_distance(grid_pos, this->_center);

    std::vector<t_direction_info> dirs_info = compute_dirs_info(grid_pos, my_color, other_color);

    t_score_info score_info = compute_score_information(dirs_info);


    score += compute_score(score_info, my_captured);

    return score;
}

/*
    In the simple heuristic we only compute the score of the position
    @args: color -> the color of the player
    @args: pos -> the position to compute the score
    @return: the score of the position
*/
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

/*
    New solution ! No we need to compute heuristic on the full board instead of only the position
    This is much smarter and much more logical
    In the simple version we only compute on the distance from the relative center
    
    @args: color -> the color of the player
    @return: the score of the board
*/
int Game::full_simple_heuristic(e_color color) {
    e_cell my = color == WHITESTONE ? WHITE : BLACK;
    e_cell other = (my == WHITE) ? BLACK : WHITE;

    int score = 0;
    for (int y = 0; y < 19; y++) {
        for (int x = 0; x < 19; x++) {
            t_position pos = {x, y};
            if (_board.get(x, y).get() == my)
                score += get_linear_distance(pos, this->_center);
            else if (_board.get(x, y).get() == other)
                score += get_linear_distance(pos, this->_center);
        }
    }
    return score;
}

static int computeSequenceName(std::deque<e_cell> &sequence, e_cell &my_color, e_cell &other_color) {
    int name = 0;
    for (size_t i = 0; i < sequence.size(); i++) {
        name *= 3;
        if (sequence[i] == my_color)
            name += 1;
        else if (sequence[i] == other_color)
            name += 2;
    }
    return name;
}

static int computeSequenceName2(std::deque<e_cell> &sequence, int previous_name, e_cell &my_color, e_cell &other_color) {
    int name = previous_name;
    if (sequence.size() < 5)
        return name;
    else if (sequence.size() > 5)
        name = (name - sequence[0] * 243) * 3 + sequence[5];
    else
        name = computeSequenceName(sequence, my_color, other_color);

    return name;
}

static void display_sequence(std::deque<e_cell> &sequence) {
    for (size_t i = 0; i < sequence.size(); i++) {
        if (sequence[i] == WHITE)
            std::cout << "W";
        else if (sequence[i] == BLACK)
            std::cout << "B";
        else
            std::cout << "N";
    }
    std::cout << std::endl;
}

int Game::board_complex_heuristic(e_color color) {
    e_cell my = color == WHITESTONE ? WHITE : BLACK;
    e_cell other = (my == WHITE) ? BLACK : WHITE;

    std::deque<e_cell> sequence_1;
    std::deque<e_cell> sequence_2;
    int sequence_1_name;
    int sequence_2_name;

    int score = 0;

    /* Handle horizontal and vertical sequences */
    for (int y = 0; y < 19; y++) {
        sequence_1.clear();
        sequence_2.clear();
        sequence_1_name = 0;
        sequence_2_name = 0;
        for (int x = 0; x < 19; x++) {
            sequence_1.push_back(_board.get(x, y).get());
            if (sequence_1.size() == 5) {
                sequence_1_name = computeSequenceName(sequence_1, my, other);
                score += this->_sequenceDna[(e_sequenceDna)sequence_1_name];
                sequence_1.pop_front();
            }
            sequence_2.push_back(_board.get(y, x).get());
            if (sequence_2.size() == 5) {
                sequence_2_name = computeSequenceName(sequence_2, my, other);
                score += this->_sequenceDna[(e_sequenceDna)sequence_2_name];
                sequence_2.pop_front();
            }
        }
    }

    /* Handle diagonales sequences */
    for (int i = 0; i < 29; i++) {
        sequence_1.clear();
        sequence_2.clear();
        sequence_1_name = 0;
        sequence_2_name = 0;
        int y = std::max(14 - i, 0);
        int x = std::max(-14 + i, 0);
        while (y < 19 && x < 19) {
            sequence_1.push_back(_board.get(x, y).get());
            if (sequence_1.size() == 5) {
                sequence_1_name = computeSequenceName(sequence_1, my, other);
                score += this->_sequenceDna[(e_sequenceDna)sequence_1_name];
                sequence_1.pop_front();
            }
            sequence_2.push_back(_board.get(y, x).get());
            if (sequence_2.size() == 5) {
                sequence_2_name = computeSequenceName(sequence_2, my, other);
                score += this->_sequenceDna[(e_sequenceDna)sequence_2_name];
                sequence_2.pop_front();
            }
            y++;
            x++;
        }
    } 

    std::cout << "Score: " << score << std::endl;
    return score;   
}