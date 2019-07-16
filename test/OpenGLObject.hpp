#ifndef OPENGLOBJECT_HPP
#define OPENGLOBJECT_HPP

#include <iostream>
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

#include "EDisplayType.hpp"
#include "Map.hpp"

class OpenGLObject
{
    private:
        char        **_argv;
        int         _argc;
        int         _window;

        static Map  _screen;
        static void _display();

    public:
        OpenGLObject(int ac, char **av, int width, int height);
        ~OpenGLObject();
        void Init();
        void Close();
        void SetPixel(int x, int y, int value);

        bool        _init;
};

Map OpenGLObject::_screen = Map();

void OpenGLObject::_display()
{
    float sizeX;
    float sizeY;
    float a;
    float b;

    sizeX = 1.0f / _screen.GetWidth() * 2;
    sizeY = 1.0f / _screen.GetHeight() * 2;
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    for (int x = 0; x < _screen.GetWidth(); x++)
    {
        for (int y = 0; y < _screen.GetHeight(); y++)
        {
            if (_screen.GetNode(x, y) > 0)
            {
                a = (float)(x) / _screen.GetWidth() * 2 - 1;
                b = (float)(y) / _screen.GetHeight() * 2 - 1;
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex2f(a, b);
                glVertex2f(a + sizeX, b);
                glVertex2f(a + sizeX, b + sizeY);
                glVertex2f(a, b + sizeY);
            }
        }
    }
}

OpenGLObject::OpenGLObject(int ac, char **av, int width, int height) : _argc(ac), _argv(av) { _screen = Map(width, height); return; }

OpenGLObject::~OpenGLObject() { return; }

void OpenGLObject::Init()
{
    this->_init = true;
    _screen.PerlinFill(0.1f);
    glutInit(&this->_argc, this->_argv);
    this->_window = glutCreateWindow("Nibbler OpenGL");
    glutInitWindowSize(_screen.GetWidth(), _screen.GetHeight());
    glutInitWindowPosition(50, 50);
    glutDisplayFunc(_display); 
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutMainLoop();
}

void OpenGLObject::SetPixel(int x, int y, int value) { _screen.SetNode(x, y, value); }

void OpenGLObject::Close() { glutDestroyWindow(this->_window); }

#endif