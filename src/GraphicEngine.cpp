#include "GraphicEngine.hpp"

GraphicEngine::GraphicEngine(int width, int height)
{
    this->game = new Game(Coord(width, height));
    this->loadLibrary("lib/ncurses/ncurses.dynlib");
    //this->loadLibrary("lib/opengl/opengl.dynlib");
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
    if (this->lib)
    {
        this->lib->close();
        dlclose(this->handler);
    }
    this->lib = reinterpret_cast<IGraphic *(*)()>(mkr)();
}

IGraphic *GraphicEngine::getCurrentLib()
{
    if (!this->lib->init) { this->lib->open(); }
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
        case KEY_UP: //UP
            this->game->Input(Keycode_Up);
            break;
        case KEY_DOWN: //DOWN
            this->game->Input(Keycode_Down);
            break;
        case KEY_LEFT: //LEFT
            this->game->Input(Keycode_Left);
            break;
        case KEY_RIGHT: //RIGHT
            this->game->Input(Keycode_Right);
            break;
        case 49: // 1
            this->loadLibrary("lib/ncurses/ncurses.dynlib");
            break;
        case 50: // 2
            this->loadLibrary("lib/openGL/opengl.dynlib");
            break;
        case 51: // 3
            this->loadLibrary("lib/sdl/sdl.dynlib");
            break;
    }
}