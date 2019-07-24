#ifndef IGRAPHIC_H
#define IGRAPHIC_H

    // Command Queue
    typedef struct c_queue{
        char command;
        c_queue * next;
    } c_queue;

    class IGraphic{
        private:
             c_queue command;
        public:
            virtual void processInput();
            virtual void render();
    };

#endif
