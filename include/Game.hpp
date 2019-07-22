#ifndef GAME_HPP
#define GAME_HPP

#include <chrono>
#include <dlfcn.h>

#include "Coord.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "EKeycode.hpp"

#define FREQ 0.2
#define FILL 0.3

#define NODE_EMPTY 0
#define NODE_WALL 1
#define NODE_PLAYER 2
#define NODE_TREAT 3

class Game
{
    private:
        Map                 _map;
        Player              _player;
        std::vector<Coord>  _treats;
        bool                _running;
        bool                _paused;

        void    CheckPlayer();
        void    CreateTreats();
        void    GameOver(std::string reason);
    public:
        Game(const Coord size);
        ~Game();
        
        Map         GetDisplayMap();
        void        Start();
        void        Update();
        void        Pause();
        void        Input(EKeycode key);
        bool        Running();
};

Game::Game(const Coord size) :
    _map(size),
    _player(size.x / 2, size.y / 2),
    _running(true),
    _paused(false)
{
    this->CreateTreats();
    this->_map.PerlinFill(FREQ, 0, FILL);
    return;
}

Game::~Game()
{
    return;
}

void Game::CheckPlayer()
{
    int count;

    count = 0;
    for (std::vector<Coord>::iterator i = this->_player.GetBody().begin(); i < this->_player.GetBody().end(); i++)
    {
        if (this->_map.GetNode(i->x, i->y) != 0)
        {
            this->GameOver((this->_map.GetNode(i->x, i->y) > 0 ? "Collided with wall, x:" : "Out of range, x:") + std::to_string(i->x) + ", y:" + std::to_string(i->y) + "; " + std::to_string(this->_map.GetNode((*i).x, (*i).y)));
            return;
        }
        for (std::vector<Coord>::iterator j = this->_treats.begin(); j < this->_treats.end(); j++)
        {
            if ((*i).x == (*j).x && (*i).y == (*j).y)
            {
                this->_player.IncreaseSize();
                this->_treats.erase(j);
                break;
            }
        }
        int c = 0;
        for (std::vector<Coord>::iterator k = this->_player.GetBody().begin(); k < this->_player.GetBody().end(); k++)
        {
            if (c != count)
            {
                if (k->x == i->x && k->y == i->y)
                {
                    this->GameOver("Collide with self, x:" + std::to_string(i->x) + ", y:" + std::to_string(i->y) + "; " + std::to_string(count) + ", " + std::to_string(c));
                }
            }
            c++;
        }
        count++;
    }
}

void Game::CreateTreats()
{
    for (int x = 0; x < this->_map.GetWidth(); x++)
    {
        for (int y = 0; y < this->_map.GetHeight(); y++)
        {
            if (this->_map.GetNode(x, y) == 0 && x % 5 == 0 && y % 5 == 0) { this->_treats.push_back(Coord(x, y)); }
        }
    }
}

void Game::GameOver(std::string reason)
{
    std::cout << std::endl << "Game Over: " << reason << std::endl;
    this->_running = false;
}

Map Game::GetDisplayMap()
{
    Map displayMap(this->_map.GetWidth(), this->_map.GetHeight());
    
    for (std::vector<Coord>::iterator i = this->_treats.begin(); i < this->_treats.end(); i++) { displayMap.SetNode((*i).x, (*i).y, NODE_TREAT); }
    for (int x = 0; x < displayMap.GetWidth(); x++)
    {
        for (int y = 0; y < displayMap.GetHeight(); y++)
        {
            if (this->_map.GetNode(x, y) > 0) { displayMap.SetNode(x, y, NODE_WALL); }
        }
    }
    for (std::vector<Coord>::iterator i = this->_player.GetBody().begin(); i < this->_player.GetBody().end(); i++) { displayMap.SetNode(i->x, i->y, NODE_PLAYER); }
    return (displayMap);
}

void Game::Start()
{
    if (this->_running) return;
    this->_running = true;
    while (this->_running) Update();
}

void Game::Update()
{
    if (this->_paused) { return; }
    this->_player.Move();
    CheckPlayer();
}

void Game::Pause() { this->_paused = !this->_paused; }

void Game::Input(EKeycode key)
{
    switch (key)
    {
        case Keycode_Up: this->_player.ChangeDirection(Up); break;
        case Keycode_Down: this->_player.ChangeDirection(Down); break;
        case Keycode_Left: this->_player.ChangeDirection(Left); break;
        case Keycode_Right: this->_player.ChangeDirection(Right); break;
        case Keycode_Pause: this->Pause(); break;
        case Keycode_Exit: this->_running = false; break;
        default: break;
    }
}

bool Game::Running() { return(this->_running); }

#endif