#include "GraphicEngine.hpp"

GraphicEngine::GraphicEngine(int width, int height)
{
    this->game = new Game(Coord(width, height));
    
    this->lib = this->loadLibrary("lib/ncurses/ncurses.dynlib");
    //this->lib = this->loadLibrary("lib/openGL/opengl.dynlib");
    //this->lib = this->loadLibrary("lib/sdl/sdl.dynlib");
}

GraphicEngine::~GraphicEngine()
{
    dlclose(this->handler);
    return;
}

void GraphicEngine::loadLibrary(std::string name)
{
    this->handler = dlopen(name.c_str(), RTLD_NOW);
    if(this->handler == NULL){
        std::cout << dlerror() << std::endl;
        exit(-1);
    }
    void *mkr = dlsym(this->handler, "newGraphic");
    this->lib = reinterpret_cast<IGraphic *(*)()>(mkr)();
}

void GraphicEngine::switchLibrary(int i)
{
    delete this->lib;
    if (i == 1) { this->loadLibrary("lib/ncurses/ncurses.dynlib"); }
    if (i == 2) { this->loadLibrary("lib/openGL/opengl.dynlib"); }
    if (i == 3) { this->loadLibrary("lib/sdl/sdl.dynlib"); }
}

IGraphic *GraphicEngine::getCurrentLib()
{
    return this->lib;
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
        case 1:
            this->switchLibrary(1);
            break;
        case 2:
            this->switchLibrary(2);
            break;
        case 3:
            this->switchLibrary(3);
            break;
    }
}