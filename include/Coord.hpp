#ifndef COORD_HPP
#define COORD_HPP

class Coord
{
    public:
        Coord();
        Coord(int _x, int _y);
        Coord(const Coord &src);
        ~Coord();

        int x;
        int y;

        Coord &operator=(const Coord &rhs);
};

#endif
