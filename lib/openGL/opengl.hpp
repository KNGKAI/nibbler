#ifndef OPENGL_G
#define OPENGL_G

#include "IGraphic.hpp"
#include <OpenGL/gl.h>
#include "glfw3.h"

class OpenGL : public IGraphic{
    private:
        GLFWwindow* window;
        void        drawCell(float x, float y, float w, float h);

    public:
        OpenGL();
        ~OpenGL();
        virtual void init();
        virtual void close();
        virtual void processInput(void);
        virtual void render(Map & m);
        virtual int  getCommand();
};

// extern "C" IGraphic * newGraphic(){
//     return new OpenGL();
// }

#endif