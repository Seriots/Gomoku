#include "Game.hpp"

bool Game::is_in_grid(int x, int y) {
    return (x >= 0 && x < 19 && y >= 0 && y < 19);
}