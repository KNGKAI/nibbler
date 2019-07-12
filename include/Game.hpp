#ifndef GAME_HPP
#define GAME_HPP

#include <chrono>

#include "Coord.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Display.hpp"

#define FREQ 0.1
#define FILL 0.3
#define UPDATE_RATE 0.2
#define DEBUG false

class Game : public Display
{
    private:
        Map                 _map;
        Player              _player;
        std::vector<Coord>  _treats;
        bool                _running;
        bool                _paused;
        float               _time;
        float               _deltaTime;
        int                 _tick;

        void    CheckPlayer();
        void    CreateTreats();
        void    GameOver(std::string reason);
    public:
        Game(const Coord size, int argc, char **argv);
        ~Game();
        
        Map         GetMap();
        bool        IsRunning();
        void        DrawFrame();
        void        Update();
        void        Pause();
        void        SwitchDisplay(EDisplayType type);
        void        Input(EKeycode key);
};

Game::Game(const Coord size, int argc, char **argv) :
    _map(size),
    _player(size.x / 2, size.y / 2, &this->_map),
    _running(true),
    _paused(true),
    _time(0),
    _deltaTime(0),
    _tick(0)
{
    this->Init(argc, argv);
    //this->_map.PerlinFill(FREQ, this->_time, FILL);
    this->CreateTreats();
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
    for (int x = 0; x < this->GetMap().GetWidth(); x++)
    {
        for (int y = 0; y < this->GetMap().GetHeight(); y++)
        {
            if (this->_map.GetNode(x, y) == 0 && x % 5 == 0 && y % 5 == 0) { this->_treats.push_back(Coord(x, y)); }
        }
    }
}

void Game::GameOver(std::string reason)
{
    #if DEBUG
        std::cout << "Last Frame: " << std::endl;
        this->DrawFrame();
    #endif
    std::cout << std::endl << "Game Over: " << reason << std::endl;
    this->Close();
    this->_running = false;
}

Map Game::GetMap() { return (this->_map); }

bool Game::IsRunning() { return (this->_running); }

void Game::DrawFrame()
{
    Map displayMap(this->GetMap().GetWidth(), this->GetMap().GetHeight());

    auto t1 = std::chrono::high_resolution_clock::now();
    for (int x = 0; x < displayMap.GetWidth(); x++)
    {
        for (int y = 0; y < displayMap.GetHeight(); y++)
        {
            displayMap.SetNode(x, y, this->GetMap().GetNode(x, y));
        }
    }
    #if DEBUG
        if (DEBUG) { std::cout << "Player:" << std::endl; }
        int count = 0;
    #endif
    for (std::vector<Coord>::iterator i = this->_player.GetBody().begin(); i < this->_player.GetBody().end(); i++)
    {
        #if DEBUG
            std::cout << count++ << ":" << std::to_string(i->x) << "-" << std::to_string(i->y) << std::endl;
        #endif
        if (displayMap.GetNode(i->x, i->y) == 0) { displayMap.SetNode(i->x, i->y, 2); }
    }
    for (std::vector<Coord>::iterator i = this->_treats.begin(); i < this->_treats.end(); i++)
    {
        displayMap.SetNode((*i).x, (*i).y, 3);
    }
    this->Draw(displayMap);
    if (this->_time > UPDATE_RATE * this->_tick)
    {
        this->_tick++;
        this->Update();
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> fs = t2 - t1;
    this->_deltaTime = fs.count();
    this->_time += this->_deltaTime;
    return;
}

void Game::Update()
{
    if (this->_paused) { return; }
    this->_player.Move();
    CheckPlayer();
    this->_map.PerlinFill(FREQ, this->_time, FILL);
    return;
}

void Game::Pause() { this->_paused = !this->_paused; }

void Game::Input(EKeycode key)
{
    switch (key)
    {
        case Key_Up:
            this->_player.ChangeDirection(Up);
            break;
        case Key_Down:
            this->_player.ChangeDirection(Down);
            break;
        case Key_Left:
            this->_player.ChangeDirection(Left);
            break;
        case Key_Right:
            this->_player.ChangeDirection(Right);
            break;
        case Key_Terminal:
            this->Switch(Terminal);
            break;
        case Key_OpenGL:
            this->Switch(OpenGL);
            break;
        case Key_Pause:
            this->Pause();
            break;
        case Key_Exit:
            std::exit(0);
            break;
        default:
            break;
    }
}

#endif