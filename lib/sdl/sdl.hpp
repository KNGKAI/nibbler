#ifndef SDL_G
#define SDL_G

    #include "IGraphic.hpp"
    #include "SDL2/SDL.h"

    class SDL : public IGraphic{
        private:
            SDL_Window      *window;
            SDL_Renderer    *renderer;
            void            drawPixel(int x, int y, int scale);

        public:
            SDL();
            ~SDL();
            virtual void init();
            virtual void close();
            virtual void processInput(void);
            virtual void render(Map & m);
            virtual int  getCommand();
    };

    extern "C" IGraphic * newGraphic(){
        return new SDL();
    }

#endif