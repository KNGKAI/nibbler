#ifndef NCURSES_G
#define NCURSES_G

    #include "IGraphic.hpp"
    #include "Game.hpp"
    #include "curses.h"

    class Ncurses : public IGraphic{
        private:
            WINDOW * _win;
        public:
            Ncurses();
            ~Ncurses();
            virtual void open();
            virtual void close();
            virtual void processInput(void);
            virtual void render(Map & m);
            virtual int  getCommand();
    };

    extern "C" IGraphic * newGraphic(){
        return new Ncurses();
    }

#endif