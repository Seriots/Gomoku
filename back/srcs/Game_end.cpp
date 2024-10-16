#include <string>
#include <deque>

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

bool    Game::check_win_by_alignement(int pos, e_cell color) {
    t_position grid_pos = {pos % 19, pos / 19};

    std::vector<std::vector<int> > directions = {{-1, 0},{0, -1},{-1, -1},{1, -1}};

    for (size_t dir = 0; dir < directions.size(); dir++) {
        int dx = directions[dir][0];
        int dy = directions[dir][1];

        int alignement = 1;

        for (int i = 1; i < 5; i++) {
            int nx = grid_pos.x + (i * dx);
            int ny = grid_pos.y + (i * dy);

            if (!is_in_grid(nx, ny))
                break;
            if (this->_board.get(nx, ny).get() != color)
                break;
            alignement++;
        }
        for (int i = -1; i > -5; i--) {
            int nx = grid_pos.x + (i * dx);
            int ny = grid_pos.y + (i * dy);

            if (!is_in_grid(nx, ny))
                break;
            if (this->_board.get(nx, ny).get() != color)
                break;
            alignement++;
        }
        if (alignement >= 5)
            return true;
    }
    return false;
}

bool Game::is_capturable(t_position &grid_pos, e_cell color, std::vector<int> *capture_spot) {
    std::vector<std::vector<int> > directions;

    e_cell inv_color = color == WHITE ? BLACK : WHITE;
    int is_capturable = 4;

    directions = {{-1, 0},{1, 0},{0, -1},{0, 1}, {-1, -1},{1, 1},{1, -1},{-1, 1}};
    for (size_t dir = 0; dir < directions.size(); dir+=2) {
        int dx = directions[dir][0];
        int dy = directions[dir][1];

        int dx2 = directions[dir + 1][0];
        int dy2 = directions[dir + 1][1];

        if (check_sequence(grid_pos.x, grid_pos.y, dx, dy, {inv_color}) && check_sequence(grid_pos.x, grid_pos.y, dx2, dy2, {color, NONE}))
            capture_spot->push_back((grid_pos.y + 2 * dy2) * 19 + grid_pos.x + 2 * dx2);
        else if (check_sequence(grid_pos.x, grid_pos.y, dx, dy, {color, NONE}) && check_sequence(grid_pos.x, grid_pos.y, dx2, dy2, {inv_color}))
            capture_spot->push_back((grid_pos.y + 2 * dy) * 19 + grid_pos.x + 2 * dx);
        else if (check_sequence(grid_pos.x, grid_pos.y, dx, dy, {color, inv_color}) && check_sequence(grid_pos.x, grid_pos.y, dx2, dy2, {NONE}))
            capture_spot->push_back((grid_pos.y + dy2) * 19 + grid_pos.x + dx2);
        else if (check_sequence(grid_pos.x, grid_pos.y, dx, dy, {NONE}) && check_sequence(grid_pos.x, grid_pos.y, dx2, dy2, {color, inv_color}))
            capture_spot->push_back((grid_pos.y + dy) * 19 + grid_pos.x + dx);
        else 
            is_capturable--;
    }

    return is_capturable > 0;

}

std::vector<int>    Game::get_capture_prevent_win_pos(int pos, e_cell color) {
    std::vector<std::deque<t_position> >    alignements;
    std::vector<int>                        capture_spot;

    t_position grid_pos = {pos % 19, pos / 19};

    if (is_capturable(grid_pos, color, &capture_spot))
        return capture_spot;

    std::vector<std::vector<int> > directions = {{-1, 0},{0, -1},{-1, -1},{1, -1}};
    for (size_t dir = 0; dir < directions.size(); dir++) {
        int dx = directions[dir][0];
        int dy = directions[dir][1];

        std::deque<t_position> alignement = {grid_pos};

        for (int i = 1; i < 5; i++) {
            int nx = grid_pos.x + (i * dx);
            int ny = grid_pos.y + (i * dy);

            if (!is_in_grid(nx, ny))
                break;
            if (this->_board.get(nx, ny).get() != color)
                break;
            alignement.push_back({nx, ny});
        }
        for (int i = -1; i > -5; i--) {
            int nx = grid_pos.x + (i * dx);
            int ny = grid_pos.y + (i * dy);

            if (!is_in_grid(nx, ny))
                break;
            if (this->_board.get(nx, ny).get() != color)
                break;
            alignement.push_front({nx, ny});
        }
        if (alignement.size() >= 5)
            alignements.push_back(alignement);
    }
    if (alignements.size() != 1)
        return {};
    int delta = alignements[0].size() - 5;
    for (size_t i = delta; i < alignements[0].size() - delta; i++) {
       is_capturable(alignements[0][i], color, &capture_spot);
    }
    return capture_spot;
}

bool   Game::check_no_winner() {

    return false;
}

t_endgame_info  Game::check_end_game(int pos) {
    t_endgame_info endgame_info = {this->_request.color, false, false, false, {}};

    e_cell cell = this->_request.color == WHITESTONE ? WHITE : BLACK;

    endgame_info.win_by_capture = check_win_by_capture();
    endgame_info.win_by_alignement = check_win_by_alignement(pos, cell);
    if (endgame_info.win_by_alignement)
        endgame_info.capture_prevent_win_pos = get_capture_prevent_win_pos(pos, cell);
    if (!endgame_info.win_by_capture && !endgame_info.win_by_alignement)
        endgame_info.no_winner = check_no_winner();
    return endgame_info;
}