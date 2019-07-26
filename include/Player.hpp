#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "EDirection.hpp"
#include "Coord.hpp"
#include "Map.hpp"
#include <vector>

class Player
{
    private:
        EDirection          _direction;
        EDirection          _wantedDirection;
        Coord               _position;
        std::vector<Coord>  _body;
        int                 _size;

        void                CreateBody();

    public:
        Player();
        Player(Coord position);
        Player(int x, int y);
        ~Player();

        void                Move();
        void                ChangeDirection(EDirection direction);
        void                IncreaseSize();
        Coord               GetPosition();
        std::vector<Coord>  GetBody();
        int                 GetSize();
};

#endif
