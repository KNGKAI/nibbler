#include "GraphicEngine.hpp"

GraphicEngine::GraphicEngine(int width, int height)
{
    this->game = new Game(Coord(width, height));
    // OpenGL
    void *hndl = dlopen("lib/opengl/opengl.dynlib", RTLD_NOW);
    if(hndl == NULL){
        std::cout << dlerror() << std::endl;
        exit(-1);
    }
    mkrs[0] = dlsym(hndl, "newGraphic");
    // SDL
    hndl = dlopen("lib/opengl/opengl.dynlib", RTLD_NOW);
    if(hndl == NULL){
        std::cout << dlerror() << std::endl;
        exit(-1);
    }
    mkrs[1] = dlsym(hndl, "newGraphic");
    // NCURSES
    hndl = dlopen("lib/opengl/opengl.dynlib", RTLD_NOW);
    if(hndl == NULL){
        std::cout << dlerror() << std::endl;
        exit(-1);
    }
    mkrs[2] = dlsym(hndl, "newGraphic");
    // Initialise with 1st lib
    currentLib = reinterpret_cast<IGraphic *(*)()>(mkrs[0])();
}

IGraphic *GraphicEngine::getCurrentLib()
{
    return this->currentLib;
}

Map GraphicEngine::getGameMap()
{
    return this->game->GetDisplayMap();
}

void GraphicEngine::updateGame()
{
    this->game->Update();
}

void GraphicEngine::inputToGame(int i)
{
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