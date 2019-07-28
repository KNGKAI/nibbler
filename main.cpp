#include "lib/IGraphic.hpp"
#include "include/Game.hpp"
#include "GraphicEngine.hpp"
#include "Game.hpp"
#include "curses.h"
#include <dlfcn.h>
#define _GNU_SOURCE
#include <iomanip>

#define MS_PER_UPDATE 1000
#define WIDTH 40
#define HEIGHT 20

class GraphicEngine{
    private:
        size_t currentLib;
        IGraphic * libs[4];
        Game * game;
    public:
        GraphicEngine(){
            this->game = new Game(Coord(WIDTH, HEIGHT));
            
            void *hndl = dlopen("lib/ncurses.dynlib", RTLD_NOW);
            if(hndl == NULL){
               std::cout << dlerror() << std::endl;
               exit(-1);
            }
            void *mkr = dlsym(hndl, "newGraphic");
            libs[0] = reinterpret_cast<IGraphic *(*)()>(mkr)();

            currentLib = 0;
        }
        IGraphic * getCurrentLib(){
            return this->libs[this->currentLib];
        }
        Map getGameMap(){
            return this->game->GetDisplayMap();
        }
        void updateGame(){
            this->game->Update();
        }
        void inputToGame(int i){
            switch (i)
            {
                case 27: //ESC
                    this->game->Input(Keycode_Exit);
                    break;
                case 32: //SPACE
                    this->game->Input(Keycode_Pause);
                    break;
                case KEY_UP:
                    this->game->Input(Keycode_Up);
                    break;
                case KEY_DOWN:
                    this->game->Input(Keycode_Down);
                    break;
                case KEY_LEFT:
                    this->game->Input(Keycode_Left);
                    break;
                case KEY_RIGHT:
                    this->game->Input(Keycode_Right);
                    break;
            }
        }
};

GraphicEngine myEngine;
#define MS_PER_UPDATE 500
#define WIDTH 40
#define HEIGHT 20

GraphicEngine myEngine(WIDTH, HEIGHT);

void processInput(){
    IGraphic * current = myEngine.getCurrentLib();
    current->processInput();
    myEngine.inputToGame(current->getCommand());
}

void update(){
    myEngine.updateGame();
}

void render(){
    Map myMap = myEngine.getGameMap();
    IGraphic * current = myEngine.getCurrentLib();
    current->render(myMap);
}


int main(int argc, char **argv){
    double previous = time(0);
    double lag = 0.0;
    while (true)
    {
        double current = time(0);
        double elapsed = current - previous;
        previous = current;
        lag += elapsed;

        processInput();

}

void update(){
    myEngine.updateGame();
}

void render(){
    Map myMap = myEngine.getGameMap();
    IGraphic * current = myEngine.getCurrentLib();
    current->render(myMap);
}

double diffclock(clock_t clock1, clock_t clock2)
{
    double diffticks = clock2 - clock1;
    double diffms = diffticks / CLOCKS_PER_SEC;
    return (diffms);
}

int main(int argc, char **argv){
    clock_t previous = clock();
    double lag = 0.0;
    while (true)
    {
        double current = clock();
        double elapsed = diffclock(previous, current) * 1000;
        previous = current;
        lag += elapsed;

        processInput();
        while (lag >= MS_PER_UPDATE)
        {
            update();
            lag -= MS_PER_UPDATE;
        }

        render();
    }
    return 0;
}