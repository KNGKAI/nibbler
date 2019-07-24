#ifndef __SDL_G__
#define __SDL_G__

#include "IGraphic.hpp"
#include "Game.hpp"
#include <SDL2/SDL.h>


class SDL_Graphic : public IGraphic{
    private:
        int             width = 40;
        int             height = 20;
        int             scale = 10;
        
        SDL_Window*     window;
        SDL_Renderer*  renderer;
        
        void  onEvent(SDL_Event& e);
        void  DrawPixel(int x, int y);

    public:
        SDL_Graphic();
        virtual ~SDL_Graphic();

        virtual void processInput(void);
        virtual void render(Map & m);
        virtual int  getCommand();
};

extern "C" IGraphic * newGraphic(){
    return new SDL_Graphic();
}

#endif