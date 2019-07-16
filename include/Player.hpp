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
};

Player::Player() : _position(0, 0), _direction(Up), _wantedDirection(Up), _size(6)
{
    CreateBody();
    return;
}

Player::Player(Coord position) : _position(position), _direction(Up), _wantedDirection(Up), _size(6)
{
    CreateBody();
    return;
}

Player::Player(int x, int y) : _position(x, y), _direction(Up), _wantedDirection(Up), _size(6)
{
    CreateBody();
    return;
}

Player::~Player()
{
    return;
}

void Player::CreateBody()
{
    for (int i = 0; i < this->_size; i++)
    {
        this->_body.push_back(Coord(this->_position.x, this->_position.y - i));
    }
}

void Player::Move()
{
    Coord newHead = *_body.begin();

    this->_direction = this->_wantedDirection;
    switch (this->_direction)
    {
        case Up:
            newHead.y++;
            break;
        case Down:
            newHead.y--;
            break;
        case Left:
            newHead.x--;
            break;
        case Right:
            newHead.x++;
            break;
        default:
            break;
    }
    this->_position = newHead;
    this->_body.insert(this->_body.begin(), newHead);
    if (this->_body.size() > this->_size) { this->_body.pop_back(); }
}

void Player::ChangeDirection(EDirection direction)
{
    switch (direction)
    {
        case Up:
            if (this->_direction != Down) { this->_wantedDirection = direction; }
            break;
        case Down:
            if (this->_direction != Up) { this->_wantedDirection = direction; }
            break;
        case Left:
            if (this->_direction != Right) { this->_wantedDirection = direction; }
            break;
        case Right:
            if (this->_direction != Left) { this->_wantedDirection = direction; }
            break;
        default:
            break;
    }
}

void Player::IncreaseSize()
{
    this->_size++;
}

Coord Player::GetPosition()
{
    return (this->_position);
}

std::vector<Coord> Player::GetBody()
{
    return (this->_body);
}


#endif