#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <ncurses.h>
#include <SDL2/SDL.h> 
#include <Game.hpp>

int width = 40;
int height = 20;
int scale = 10;
Game game = Game(Coord(width, height));
float _time = 0;

//SDL Draw Pixel
void DrawPixel(SDL_Renderer * renderer, int x, int y)
{
    for (int i = 0; i < scale; i++)
    {
        for (int j = 0; j < scale; j++)
        {
            SDL_RenderDrawPoint(renderer, x * scale + i, y * scale + j);
        }
    }
}

void DrawSDL()
{
    SDL_Event e;
    SDL_Window *window;
    SDL_Renderer *renderer;

    /////////////Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(width * scale, height * scale, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "nibbler SDL");
    SDL_UpdateWindowSurface(window);
    ///////////////////////////

    while (game.Running())
    {
        ////GAME LOOP
        Map m = game.GetDisplayMap();
        if (_time > 1)
        {
            _time = 0;
            game.Update();
        }
        else
        {
            _time += 0.1f;
        }
        if (!game.Running())
        {
            quit = true;
        }
        ////////////
        
        //////////INPUT
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
                case SDL_QUIT:
                   game.Input(Keycode_Exit);
                   break;
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym)
                    {
                        case SDLK_LEFT:
                            game.Input(Keycode_Left);
                            break;
                        case SDLK_RIGHT:
                            game.Input(Keycode_Right);
                            break;
                        case SDLK_UP:
                            game.Input(Keycode_Up);
                            break;
                        case SDLK_DOWN:
                            game.Input(Keycode_Down);
                            break;
                        case SDLK_SPACE:
                            game.Input(Keycode_Pause);
                            break;
                        case SDLK_ESCAPE:
                            game.Input(Keycode_Exit);
                            break;
                        default:
                            break;
                    }
                    breaK:
                default:
                    break;
            }
        }
        ///////////

        //////////RENDER
        SDL_SetRenderDrawColor(renderer, 155, 155, 155, 255);
        SDL_RenderClear(renderer);
        for (int x = 0; x < m.GetWidth(); x++)
        {
            for (int y = 0; y < m.GetHeight(); y++)
            {
                /////Set Color of pixel
                switch (m.GetNode(x, y))
                {
                    case NODE_EMPTY:
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        break;
                    case NODE_WALL:
                        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                        break;
                    case NODE_PLAYER:
                        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                        break;
                    case NODE_TREAT:
                        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                        break;                
                    default:
                        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
                        break;
                }
                DrawPixel(renderer, x, m.GetHeight() - y - 1);
            }
        }
        SDL_RenderPresent(renderer);
        //////////////
    }

    ///////////////////EXIT
    SDL_DestroyWindow(window);
    SDL_Quit();
}

////OpenGL Draw Pixel
void DrawCell(float x, float y, float w, float h)
{
    glBegin(GL_POLYGON);
        glVertex2f(x, y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y + h);
        glVertex2f(x, y + h);
    glEnd();
}
//////////

void display()
{
    Map m = game.GetDisplayMap();
    float a;
    float b;
    float w;
    float h;

    glClear(GL_COLOR_BUFFER_BIT);
    //Draw background
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_POLYGON);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(1.0f, 1.0f);
        glVertex2f(-1.0f, 1.0f);
    glEnd();
    
    //calculate pixel size
    w = 1.0f / m.GetWidth() * 2;
    h = 1.0f / m.GetHeight() * 2;

    //Update Game
    if (_time > 1)
    {
        game.Update();
        _time = 0;
    }
    else
    {
        _time += 0.1f;
    }
    ////////////////Draw map
    for (int x = 0; x < m.GetWidth(); x++)
    {
        for (int y = 0; y < m.GetHeight(); y++)
        {
            a = (float)(x) / m.GetWidth() * 2 - 1;
            b = (float)(y) / m.GetHeight() * 2 - 1;
            ////set color of pixel
            switch (m.GetNode(x, y))
            {
                case NODE_EMPTY:
                    glColor3f(0.0f, 0.0f, 0.0f);
                    break;
                case NODE_WALL:
                    glColor3f(1.0f, 0.0f, 0.0f);
                    break;
                case NODE_PLAYER:
                    glColor3f(0.0f, 0.0f, 1.0f);
                    break;
                case NODE_TREAT:
                    glColor3f(0.0f, 1.0f, 0.0f);
                    break;                
                default:
                    glColor3f(1.0f, 0.0f, 1.0f);
                    break;
            }
            DrawCell(a, b, w, h);
        }
    }
    glFlush();
    /////REDRAW SCREEN
    if (game.Running()) glutPostRedisplay();
}

void keyboard(int key, int x, int y)
{
    switch(key)
    {
        case 27: //ESC
            game.Input(Keycode_Exit);
            break;
        case 32: //SPACE
            game.Input(Keycode_Pause);
            break;
        case GLUT_KEY_UP:
            game.Input(Keycode_Up);
            break;
        case GLUT_KEY_DOWN:
            game.Input(Keycode_Down);
            break;
        case GLUT_KEY_LEFT:
            game.Input(Keycode_Left);
            break;
        case GLUT_KEY_RIGHT:
            game.Input(Keycode_Right);
            break;
    }
}

void DrawOpenGL(int argc, char** argv)
{
    //glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(width * scale, height * scale);
    glutInitWindowPosition(300, 300);
    glutCreateWindow("nibbler opengl");
    glutSpecialFunc(keyboard);
    glutDisplayFunc(display);
    glutMainLoop();
}

void DrawNcurses()
{
    /////////////////////////INIT
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    nodelay(stdscr, TRUE);
    ////////////////////////

    while (game.Running())
    {
        /////////////////////INPUT
        switch (getch()) {
            case 27: //ESC
                game.Input(Keycode_Exit);
                break;
            case 32: //SPACE
                game.Input(Keycode_Pause);
                break;
            case KEY_UP:
                game.Input(Keycode_Up);
                break;
            case KEY_DOWN:
                game.Input(Keycode_Down);
                break;
            case KEY_LEFT:
                game.Input(Keycode_Left);
                break;
            case KEY_RIGHT:
                game.Input(Keycode_Right);
                break;
        }
        /////////////////////////UPDATE GAME
        if (_time > 2)
        {
            game.Update();
            _time = 0;
        }
        else
        {
            _time += 0.01f;
        }
        ////////////////////////

        /////////////////////////DRAW
        Map m = game.GetDisplayMap();
        clear();
        for (int y = m.GetHeight(); y >= -1; y--)
        {
            for (int x = -1; x < m.GetWidth() + 1; x++)
            {
                if (x >= 0 && y >= 0 && x < m.GetWidth() && y < m.GetHeight())
                {
                    switch (m.GetNode(x, y))
                    {
                        case NODE_EMPTY:
                            printw(" ");
                            break;
                        case NODE_WALL:
                            printw("X");
                            break;
                        case NODE_PLAYER:
                            printw("0");
                            break;
                        case NODE_TREAT:
                            printw("+");
                            break;
                        default:
                            printw("?");
                            break;
                    }
                }
                else
                {
                    printw("X");
                }
            }
            printw("\n");
        }
        refresh();
        //////////
    }
    //////////////////////////////END when game is not running
    endwin();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    //DrawSDL();
    //DrawNcurses();
    //DrawOpenGL(argc, argv);
    return 0;
}