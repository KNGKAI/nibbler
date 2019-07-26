#include "GraphicEngine.hpp"
#include "Game.hpp"
#include "curses.h"
#include <dlfcn.h>
#define _GNU_SOURCE
#include <iomanip>

#define MS_PER_UPDATE 250
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

double diffclock(clock_t clock1, clock_t clock2)
{
    double diffticks = clock2 - clock1;
    double diffms = diffticks / CLOCKS_PER_SEC;
    return (diffms);
}

int main(int argc, char **argv){
    if (argc == 4)
    {
        int w = std::atoi(argv[1]);
        int h = std::atoi(argv[2]);
        std::string lib = argv[3];

        if (w < 10 || h < 10)
        {
            std::cout << "Invalid Size" << std::endl;
            return (0);
        }
        else
        {
            myEngine = GraphicEngine(w, h);
            try
            {
                myEngine.loadLibrary(lib);
            }
            catch(const std::exception& e)
            {
                std::cout << e.what() << std::endl;
                return (0);
            }
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
        }
    }
    else
    {
        std::cout << "Argument Error" << std::endl;
    }
    
    
    return 0;
}