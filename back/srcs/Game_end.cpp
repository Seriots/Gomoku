#include <string>

#include "utils.hpp"

#include "Game.hpp"

bool    Game::check_win_by_capture() {
    int white_captured = this->_request.white_captured;
    int black_captured = this->_request.black_captured;

    if (white_captured >= 10)
        return true;
    if (black_captured >= 10)
        return true;
    return false;
}

bool    Game::check_win_by_alignement(int pos, e_color color) {
    t_position grid_pos = {pos % 19, pos / 19};
    e_cell cell = color == WHITESTONE ? WHITE : BLACK;

    std::vector<std::vector<int> > directions = {{-1, 0},{0, -1},{-1, -1},{1, -1}};

    for (size_t dir = 0; dir < directions.size(); dir++) {
        int dx = directions[dir][0];
        int dy = directions[dir][1];

        int alignement = 1;

        for (int i = 1; i < 5; i++) {
            int nx = grid_pos.x + (i * dx);
            int ny = grid_pos.y + (i * dy);

            if (nx < 0 || nx >= 19 || ny < 0 || ny >= 19)
                break;
            if (this->_board.get(nx, ny).get() != cell)
                break;
            alignement++;
        }
        for (int i = -1; i > -5; i--) {
            int nx = grid_pos.x + (i * dx);
            int ny = grid_pos.y + (i * dy);

            if (nx < 0 || nx >= 19 || ny < 0 || ny >= 19)
                break;
            if (this->_board.get(nx, ny).get() != cell)
                break;
            alignement++;
        }
        if (alignement >= 5)
            return true;
    }
    return false;
}

std::vector<int>    Game::get_capture_prevent_win_pos() {
    return {};
}

bool   Game::check_no_winner() {
    return false;
}

t_endgame_info  Game::check_end_game(int pos) {
    t_endgame_info endgame_info = {this->_request.color, false, false, false, {}};

    endgame_info.win_by_capture = check_win_by_capture();
    endgame_info.win_by_alignement = check_win_by_alignement(pos, this->_request.color);
    if (endgame_info.win_by_alignement)
        endgame_info.capture_prevent_win_pos = get_capture_prevent_win_pos();
    if (!endgame_info.win_by_capture && !endgame_info.win_by_alignement)
        endgame_info.no_winner = check_no_winner();
    return endgame_info;
}