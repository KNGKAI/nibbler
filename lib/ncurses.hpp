#ifndef NCURSES_G
#define NCURSES_G

    #include "IGraphic.hpp"

    class Ncurses : public IGraphic{
        public:
            Ncurses();
            ~Ncurses();
            virtual void processInput(void);
            virtual void render(Map & m);
            virtual int  getCommand();
    };

    extern "C" IGraphic * newGraphic(){
        return new Ncurses();
    }

#endif