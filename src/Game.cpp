#include "Game.hpp"

Game::Game(const Coord size) :
    _map(size),
    _player(size.x / 2, size.y / 2),
    _running(true),
    _paused(true)
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
        if (count >= this->_player.GetSize()) { return; }
    }
}

void Game::CreateTreats()
{
    for (int x = 0; x < this->_map.GetWidth(); x++)
    {
        for (int y = 0; y < this->_map.GetHeight(); y++)
        {
            if (this->_map.GetNode(x, y) == 0 && x % 5 == 0 && y % 5 == 0 && x != this->_map.GetWidth() / 2) { this->_treats.push_back(Coord(x, y)); }
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

void Game::Update()
{
    if (this->_paused) { return; }
    if (!this->_running) { return; }
    this->_player.Move();
    CheckPlayer();
}

void Game::Input(EKeycode key)
{
    switch (key)
    {
        case Keycode_Up: this->_player.ChangeDirection(Up); break;
        case Keycode_Down: this->_player.ChangeDirection(Down); break;
        case Keycode_Left: this->_player.ChangeDirection(Left); break;
        case Keycode_Right: this->_player.ChangeDirection(Right); break;
        case Keycode_Pause: this->Pause(); break;
        default: break;
    }
}

void Game::Pause() { this->_paused = !this->_paused; }

bool Game::Running() { return(this->_running); }