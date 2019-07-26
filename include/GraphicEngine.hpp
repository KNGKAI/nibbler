#ifndef GRAPHICENGINE_HPP
#define GRAPHICENGINE_HPP

#include "ncurses.h"
#include <dlfcn.h>
#define _GNU_SOURCE
#include <iomanip>
#include "Game.hpp"
#include "IGraphic.hpp"

class GraphicEngine{
    private:
        IGraphic * currentLib;
        void * mkrs[3]; // changed from array of libraries to array of makers
        Game * game;
    public:
        GraphicEngine(int width, int height);
        IGraphic * getCurrentLib();
        Map getGameMap();
        void updateGame();
        void inputToGame(int i);
};

#endif