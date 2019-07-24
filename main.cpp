#include "GraphicEngine.hpp"
#include "Game.hpp"
#include "curses.h"
#include <dlfcn.h>
#define _GNU_SOURCE
#include <iomanip>

#define MS_PER_UPDATE 500
#define WIDTH 40
#define HEIGHT 20

GraphicEngine myEngine(WIDTH, HEIGHT);

void processInput(){
    IGraphic * current = myEngine.getCurrentLib();
    current->processInput();
    myEngine.inputToGame(current->getCommand());
    std::cout << "---processInput MAIN----\n";
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