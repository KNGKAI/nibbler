#include "Map.hpp"

Map::Map() : _size(20, 20)
{
    CreateNodes();
    return;
}

Map::Map(Coord size) : _size(size)
{
    CreateNodes();
    return;
}

Map::Map(int width, int height) : _size(width, height)
{
    CreateNodes();
    return;
}

Map::~Map()
{
    for (int x = 0; x < this->GetWidth(); x++)
    {
        delete[] this->_nodes[x];
    }
    delete[] this->_nodes;
    return;
}

Map &Map::operator=(const Map &rhs)
{
    this->_size = Coord(rhs.GetWidth(), rhs.GetHeight());
    this->CreateNodes();
    return (*this);
}

bool Map::OutOfRange(int x, int y) const
{
    if (x < 0 || y < 0 || x >= this->GetWidth() || y >= this->GetHeight())
    { 
        return (true); 
    }
    return (false);
}

void Map::CreateNodes()
{
    this->_nodes = new int*[this->_size.x];
    for (int i = 0; i < this->_size.x; i++)
    {
        this->_nodes[i] = new int[this->_size.y];
    }
    
    for (int x = 0; x < this->GetWidth(); x++)
    {
        for (int y = 0; y < this->GetHeight(); y++)
        {
            this->SetNode(x, y, 0);
        }
    }
}

void Map::PerlinFill(float freq, float t, float fill)
{
    for (int x = 0; x < this->GetWidth(); x++)
    {
        for (int y = 0; y < this->GetHeight(); y++)
        {
            this->SetNode(x, y, this->_noise.Perlin(x * freq, y * freq, t * freq) < fill ? 1 : 0);
        }
    }
}

const Coord Map::GetSize() const
{
    return (this->_size);
}

const int Map::GetWidth() const
{
    return (this->_size.x);
}

const int Map::GetHeight() const
{
    return (this->_size.y);
}

int **Map::GetNodes() const
{
    return (this->_nodes);
}

int Map::GetNode(int x, int y) const
{
    if (this->OutOfRange(x, y)) { return (-1); }
    return (this->_nodes[x][y]);
}

void Map::SetNode(int x, int y, int value)
{
    if (this->OutOfRange(x, y)) { return; }
    this->_nodes[x][y] = value;
}

void Map::Clear()
{
    for (int x = 0; x < this->GetWidth(); x++)
    {
        for (int y = 0; y < this->GetHeight(); y++)
        {
            this->SetNode(x, y, 0);
        }
    }
}