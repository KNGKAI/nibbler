#include "Coord.hpp"

Coord::Coord() : x(0), y(0) {}

Coord::Coord(int _x, int _y) : x(_x), y(_y){}

Coord::~Coord() {}

Coord &Coord::operator=(const Coord &rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	return (*this);
}
