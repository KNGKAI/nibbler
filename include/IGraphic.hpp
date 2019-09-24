#ifndef IGRAPHIC_H
#define IGRAPHIC_H

#include "Map.hpp"
    
typedef struct c_queue{
    int command;
    c_queue * next;
} c_queue;

class IGraphic{
    protected:
            c_queue * command;
    private:
    public:
        bool            init = false;
        virtual void    open() = 0;
        virtual void    close() = 0;
        virtual void    processInput() = 0;
        virtual void    render(Map & m) = 0;
        virtual int     getCommand() = 0; 
};

#endif
