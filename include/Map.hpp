#ifndef MAP_HPP
#define MAP_HPP

#include "Coord.hpp"
#include "Noise.hpp"
#include <iostream>

class Map
{
    private:
        Noise       _noise;
        Coord       _size;
        int         **_nodes;
        bool        OutOfRange(int x, int y) const;
        void        CreateNodes();
    public:
        Map();
        Map(Coord size);
        Map(int width, int height);
        ~Map();

        Map &operator=(const Map &rhs);

        const Coord GetSize() const;
        const int   GetWidth() const;
        const int   GetHeight() const;
        int         **GetNodes() const;
        int         GetNode(int x, int y) const;
        void        SetNode(int x, int y, int value);

        void        Clear();
        void        PerlinFill(float freq, float t = 0, float fill = 0.5f);
};

#endif