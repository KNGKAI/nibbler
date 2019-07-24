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
		std::vector<Coord>	_treats;
        bool                _running;
        bool                _paused;

        void    CheckPlayer();
        void    CreateTreats();
        void    GameOver(std::string reason);
    public:
        Game(const Coord size);
        ~Game();

        Map         GetDisplayMap();
        void        Update();
        void        Pause();
        void        Input(EKeycode key);
        bool        Running();
};

#endif
