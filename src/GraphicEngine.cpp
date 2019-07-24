#include "GraphicEngine.hpp"

GraphicEngine::GraphicEngine(int width, int height)
{
    this->game = new Game(Coord(width, height));
    
    void *hndl = dlopen("lib/opengl/opengl.dynlib", RTLD_NOW);
    if(hndl == NULL){
        std::cout << dlerror() << std::endl;
        exit(-1);
    }
    void *mkr = dlsym(hndl, "newGraphic");
    libs[0] = reinterpret_cast<IGraphic *(*)()>(mkr)();

    currentLib = 0;
}

IGraphic *GraphicEngine::getCurrentLib()
{
    return this->libs[this->currentLib];
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