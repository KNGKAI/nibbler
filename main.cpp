#include <ncurses.h>

#include "include/Game.hpp"

#define GAME_WIDTH 25
#define GAME_HEIGHT 25

int main(int ac, char** av)
{
    Game game(Coord(GAME_WIDTH, GAME_HEIGHT), ac, av);
    while(game.IsRunning()) { game.DrawFrame(); }
    return (0);
}