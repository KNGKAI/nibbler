#include "sdl.hpp"

SDL_Graphic::SDL_Graphic()
{
    scale = 10;
    _time = 0.0;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(width * scale, height * scale, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "nibbler SDL");
    SDL_UpdateWindowSurface(window);
}


SDL_Graphic::~SDL_Graphic()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SDL_Graphic::DrawPixel(SDL_Renderer * renderer, int x, int y)
{
    for (int i = 0; i < scale; i++)
    {
        for (int j = 0; j < scale; j++)
        {
            SDL_RenderDrawPoint(renderer, x * scale + i, y * scale + j);
        }
    }
}

void SDL_Graphic::onEvent(SDL_Event& e)
{
    switch (e.type)
    {
    case SDL_QUIT:
        game.Input(Keycode_Exit);
        break;
    case SDL_KEYDOWN:
        switch (e.key.keysym.sym)
        {
        case SDLK_LEFT:
            game.Input(Keycode_Left);
            break;
        case SDLK_RIGHT:
            game.Input(Keycode_Right);
            break;
        case SDLK_UP:
            game.Input(Keycode_Up);
            break;
        case SDLK_DOWN:
            game.Input(Keycode_Down);
            break;
        case SDLK_SPACE:
            game.Input(Keycode_Pause);
            break;
        case SDLK_ESCAPE:
            game.Input(Keycode_Exit);
            break;
        default:
            break;
        }
    breaK:
    default:
        break;
    }
}

void SDL_Graphic::processInput()
{
    while (game.Running())
    {
        while (SDL_PollEvent(&e))
        {
            onEvent(e);
        }
        render(m);
    }
}

int SDL_Graphic::getCommand()
{
    if (this->command = nullptr)
        return (-1);
    return (this->command->command);
}

void SDL_Graphic::render(Map& m)
{
    SDL_SetRenderDrawColor(renderer, 155, 155, 155, 255);
    SDL_RenderClear(renderer);
    for (int x = 0; x < m.GetWidth(); x++)
    {
        for (int y = 0; y < m.GetHeight(); y++)
        {
            /////Set Color of pixel
            switch (m.GetNode(x, y))
            {
            case NODE_EMPTY:
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                break;
            case NODE_WALL:
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                break;
            case NODE_PLAYER:
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                break;
            case NODE_TREAT:
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                break;
            default:
                SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
                break;
            }
            DrawPixel(renderer, x, m.GetHeight() - y - 1);
        }
    }
    SDL_RenderPresent(renderer);
}