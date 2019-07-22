#ifndef IGRAPHIC_H
#define IGRAPHIC_H
    
    #include "../include/Map.hpp"

    #define NODE_EMPTY 0
    #define NODE_WALL 1
    #define NODE_PLAYER 2
    #define NODE_TREAT 3

    // Command Queue
    typedef struct c_queue{
        int command;
        c_queue * next;
    } c_queue;

    class IGraphic{
        protected:
             c_queue * command;
        public:
            virtual void processInput() = 0;
            virtual void render(Map & m) = 0;
    };

#endif