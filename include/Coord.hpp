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
		bool operator==(const Coord&) const;
};

Coord::Coord() : x(0), y(0) {}

Coord::Coord(int _x, int _y) : x(_x), y(_y){}

Coord::~Coord() {}

Coord &Coord::operator=(const Coord &rhs)
{
	if (this != rhs)
	{

		this->x = rhs.x;
		this->y = rhs.y;
	}
    return (*this);
}

bool operator==(const Cood &rhs) const
{
	return (rhs.x == this.x && rhs.y == this.y);
}

#endif
