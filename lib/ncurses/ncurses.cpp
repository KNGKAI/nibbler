#include "ncurses.hpp"
#include "ncurses.h"

Ncurses::Ncurses()
{
    this->command = nullptr;
}

Ncurses::~Ncurses()
{
    return;
}

void Ncurses::init()
{
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    nodelay(stdscr, TRUE);
}

void Ncurses::close()
{
    endwin();
}

int Ncurses::getCommand(){
    if (this->command == nullptr)
        return -1;
    return this->command->command;
}

void Ncurses::processInput()
{
    c_queue * node = new c_queue;
    node->command = getch();
    node->next = this->command;
    this->command = node;
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