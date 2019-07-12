#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <cstdlib>
#include <ncurses.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#include "EDisplayType.hpp"
#include "EKeycode.hpp"
#include "Map.hpp"

class Display
{
    private:
        EDisplayType    _type;
        char            **_argv;
        bool            _initOpenGL;
        bool            _initTerminal;
        int             _argc;

        void            DrawTerminal(Map map);
        void            InitTerminal();
        void            CloseTerminal();
        void            DrawOpenGL(Map map);
        void            InitOpenGL();
        void            CloseOpenGL();
    public:
        Display();
        ~Display();
        
        static Display      *_display;

        void            Close();
        void            Draw(Map map);
        void            Init(int argc, char **argv);
        void            Switch(EDisplayType type);
        virtual void    Input(EKeycode key) = 0;

        static void            DisplayOpenGL();
        static void            KeyboardOpenGL(unsigned char key, int x, int y);
};

Display *Display::_display = nullptr;

Display::Display() : _type(OpenGL), _initTerminal(false), _initOpenGL(false)
{
    _display = this;
    return;
}

Display::~Display()
{
    return;
}

void Display::DrawTerminal(Map map)
{
    int a;
    int b;

    if (!this->_initTerminal) { this->InitTerminal(); }
    clear();
    for (int x = -1; x <= map.GetWidth(); x++)
    {
        for (int y = -1; y <= map.GetHeight(); y++)
        {
            a = map.GetHeight() - y + 3;
            b = x + 3;
            if (x >= 0 && y >= 0 && x < map.GetWidth() && y < map.GetHeight())
            {
                switch (map.GetNode(x, y))
                {
                    case 0: mvprintw(a, b, " "); break;
                    case 1: mvprintw(a, b, "X"); break;
                    case 2: mvprintw(a, b, "0"); break;
                    case 3: mvprintw(a, b, "+"); break;
                    default: mvprintw(a, b, "?"); break;
                }
            }
            else
            {
                mvprintw(a, b, "X");
            }
        }
    }
    refresh();
}

void Display::InitTerminal()
{
    WINDOW *w = initscr(); 
    nodelay(w, true);
    noecho();
    raw();
    curs_set(FALSE);
    cbreak();
    keypad(w, true);
    this->_initTerminal = true;
}

void Display::CloseTerminal()
{
    this->_initTerminal = false;
    endwin();
}

void Display::DrawOpenGL(Map map)
{
    if (!this->_initOpenGL) {this->InitOpenGL(); }
}

void Display::DisplayOpenGL()
{
    // clear the draw buffer .
    glClear(GL_COLOR_BUFFER_BIT);   // Erase everything

    // set the color to use in draw
    glColor3f(0.5, 0.5, 0.0);       
    // create a polygon ( define the vertexs) 
    glBegin(GL_POLYGON);
    {           
        glVertex2f(-0.5, -0.5);
        glVertex2f(-0.5,  0.5);
        glVertex2f( 0.5,  0.5);
        glVertex2f( 0.5, -0.5);
    }
    glEnd();
    // flush the drawing to screen . 
    glFlush();
}

void Display::KeyboardOpenGL(unsigned char key, int x, int y)
{
    std::cout << key;
    if (key == 'q' || key == 'Q') { _display->Input(Key_Exit); }
    if (key == 'w' || key == 'W') { _display->Input(Key_Up); }
    if (key == 'a' || key == 'A') { _display->Input(Key_Left); }
    if (key == 's' || key == 'S') { _display->Input(Key_Down); }
    if (key == 'd' || key == 'D') { _display->Input(Key_Right); }
    if (key == '1') { _display->Input(Key_Terminal); }
    if (key == '2') { _display->Input(Key_OpenGL); }
}

void Display::InitOpenGL()
{
    this->_initOpenGL = true;
    glutInit(&this->_argc, this->_argv);            // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Nibbler");                    // Create a window
    glutDisplayFunc(this->DisplayOpenGL);           // Register display callback
    glutKeyboardFunc(this->KeyboardOpenGL);         // Register keyboard callback
    glutMainLoop();                                 // Enter main event loop
}

void Display::CloseOpenGL()
{
    this->_initOpenGL = false;
}

void Display::Close()
{
    switch (this->_type)
    {
        case Terminal:
            this->CloseTerminal();
            break;
        case OpenGL:
            this->CloseOpenGL();
            break;        
        default:
            break;
    }
}

void Display::Draw(Map map)
{
    switch (this->_type)
    {
        case Terminal:
            switch (int ch = getch())
            {
                case 'w':
                    Input(Key_Up);
                    break;
                case 's':
                    Input(Key_Down);
                    break;
                case 'a':
                    Input(Key_Left);
                    break;
                case 'd':
                    Input(Key_Right);
                    break;
                case '1':
                    Input(Key_Terminal);
                    break;
                case '2':
                    Input(Key_OpenGL);
                    break;
                case ' ':
                    Input(Key_Pause);
                    break;
                case 'q':
                    Input(Key_Exit);
                    break;
                default:
                    break;
            }
            DrawTerminal(map);
            break;
        case OpenGL:
            DrawOpenGL(map);
        default:
            break;
    }
}

void Display::Init(int argc, char **argv)
{
    this->_argc = argc;
    this->_argv = argv;
}

void Display::Switch(EDisplayType type)
{
    if (this->_type == type) { return; }
    this->Close();
    this->_type = type;
}

#endif