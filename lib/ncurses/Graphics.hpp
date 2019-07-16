#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "IGraphics.hpp"
#include "Game.hpp"
#include <ncurses.h>

class Graphics : IGraphics
{
    private:
        Game &_game;
    public:
        Graphics(Game &game);
        ~Graphics();
        void Update();
        EKeycode Input();
};

#endif