#include "Graphics.hpp"

Graphics::Graphics(Game &game) : _game(game)
{
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
}

Graphics::~Graphics()
{
    endwin();
}

void Graphics::Update()
{
    Map map;

    switch (getch())
    {
        case KEY_UP:
            this->input = Keycode_Up;
            break;
        case KEY_DOWN:
            this->input = Keycode_Down;
            break;
        case KEY_LEFT:
            this->input = Keycode_Left;
            break;
        case KEY_RIGHT:
            this->input = Keycode_Right;
            break;
        default:
            break;
    }
    clear();
    map = this->_game.GetDisplayMap();
    for (int y = 0; y < map.GetHeight(); y++)
    {
        for (int x = 0; x < map.GetWidth(); x++)
        {
            switch (map.GetNode(x, y))
            {
                case Node_Empty:
                    printw(" ");
                    break;
                case Node_Wall:
                    printw("X");
                    break;
                case Node_Player:
                    printw("0");
                    break;
                case Node_Treat:
                    printw("+");
                    break;
                default:
                    printw("?");
                    break;
            }
        }
    }
    refresh();
}

EKeycode Graphics::Input()
{
    EKeycode k;

    k = this->input;
    this->input = Keycode_None;
    return (k);
}