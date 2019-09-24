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
        void        closeLibrary();
        IGraphic    *lib;
        Game        *game;
    public:
        GraphicEngine(int width, int height);
        ~GraphicEngine();
        void        loadLibrary(std::string name);
        IGraphic    *getCurrentLib();
        Map         getGameMap();
        void        updateGame();
        void        inputToGame(int i);
        
        class LibraryNotFoundException : public std::exception
        {
            public:
                virtual const char *what() const throw();
        };
};

#endif