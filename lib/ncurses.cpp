#include "ncurses.hpp"
#include "ncurses.h"

Ncurses::Ncurses()
{
    /////////////////////////INIT
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    nodelay(stdscr, TRUE);
    ////////////////////////
}
Ncurses::~Ncurses()
{
    endwin();
    return;
}
int Ncurses::getCommand(){
    return this->command->command;
}
void Ncurses::processInput()
{
    c_queue * node = new c_queue;
    node->command = getch();
    node->next = this->command;
    this->command = node;
    // switch (getch())
    // {
    //     case 27: //ESC
    //         game.Input(Keycode_Exit);
    //         break;
    //     case 32: //SPACE
    //         game.Input(Keycode_Pause);
    //         break;
    //     case KEY_UP:
    //         game.Input(Keycode_Up);
    //         break;
    //     case KEY_DOWN:
    //         game.Input(Keycode_Down);
    //         break;
    //     case KEY_LEFT:
    //         game.Input(Keycode_Left);
    //         break;
    //     case KEY_RIGHT:
    //         game.Input(Keycode_Right);
    //         break;
    // }
}
void Ncurses::render(Map &m)
{
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
}