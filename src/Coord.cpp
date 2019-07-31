#include "Coord.hpp"

Coord::Coord() : x(0), y(0) { return; }

Coord::Coord(int _x, int _y) : x(_x), y(_y) { return; }

Coord::Coord(const Coord &src)
{
    *this = src;
    return;
}

Coord::~Coord() { return; }

Coord &Coord::operator=(const Coord &rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	return (*this);
}
