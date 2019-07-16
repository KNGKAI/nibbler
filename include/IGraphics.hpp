#ifndef IGRAPHICS_HPP
#define IGRAPHICS_HPP

#include <queue>
#include "EKeycode.hpp"

class IGraphics
{
    public:
        virtual void	    Update() = 0;
        virtual EKeycode    Input() = 0;
        
        EKeycode        input;
};

#endif