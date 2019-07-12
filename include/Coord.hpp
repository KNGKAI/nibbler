#ifndef COORD_HPP
#define COORD_HPP

class Coord
{
    public:
        Coord();
        Coord(int _x, int _y);
        ~Coord();

        int x;
        int y;

        Coord &operator=(const Coord &rhs);
};

Coord::Coord() : x(0), y(0)
{
    return;
}

Coord::Coord(int _x, int _y) : x(_x), y(_y)
{
    return;
}

Coord::~Coord()
{
    return;
}

Coord &Coord::operator=(const Coord &rhs)
{
    this->x = rhs.x;
    this->y = rhs.y;
    return (*this);
}




#endif