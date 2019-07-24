#include "sdl.hpp"
#include "Game.hpp"
#include "ncurses.h"

SDL::SDL()
{
    return;
}

SDL::~SDL()
{
    return;
}

void SDL::init()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(360, 240, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "nibbler SDL");
    SDL_UpdateWindowSurface(window);
}

void SDL::close()
{
    SDL_DestroyWindow(window);
    //SDL_Quit();
}

int SDL::getCommand()
{
    if (this->command == nullptr)
        return -1;
    return this->command->command;
}

void SDL::processInput()
{
    SDL_Event e;
    int command;

    command = 0;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT) { std::exit(0); }
        if (e.type == SDL_KEYDOWN)
        {
            switch(e.key.keysym.sym)
            {
                case SDLK_LEFT: command = KEY_LEFT; break;
                case SDLK_RIGHT: command = KEY_RIGHT; break;
                case SDLK_UP: command = KEY_UP; break;
                case SDLK_DOWN: command = KEY_DOWN; break;
                case SDLK_SPACE: command = 32; break;
                case SDLK_ESCAPE: command = 27; break;
                case SDLK_1: command = 1; break;
                case SDLK_2: command = 2; break;
                case SDLK_3: command = 3; break;
                default: break;
            }
        }
    }
    c_queue * node = new c_queue;
    node->command = command;
    node->next = this->command;
    this->command = node;
}
void SDL::render(Map &m)
{
    int scale;

    scale = 10;
    SDL_SetWindowSize(this->window, m.GetWidth() * scale, m.GetHeight() * scale);
    SDL_SetRenderDrawColor(this->renderer, 155, 155, 155, 255);
    SDL_RenderClear(this->renderer);
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
            this->drawPixel(x, m.GetHeight() - y - 1, scale);
        }
    }
    SDL_RenderPresent(this->renderer);
}

void SDL::drawPixel(int x, int y, int scale)
{
    for (int i = 0; i < scale; i++)
    {
        for (int j = 0; j < scale; j++)
        {
            SDL_RenderDrawPoint(this->renderer, x * scale + i, y * scale + j);
        }
    }
}