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
        size_t currentLib;
        IGraphic * libs[4];
        
        void        *handler;
        void        loadLibrary(std::string name);
        void        switchLibrary(int i);
        IGraphic    *lib;
        Game        *game;
    public:
        GraphicEngine(int width, int height);
        ~GraphicEngine();
        IGraphic * getCurrentLib();
        Map getGameMap();
        void updateGame();
        void inputToGame(int i);
};

#endif