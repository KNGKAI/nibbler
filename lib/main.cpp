#include "ncurses.hpp"
#include "../include/Game.hpp"
#include "curses.h"

int main(){
    Game myGame(Coord(40, 20));
    Map myMap = myGame.GetDisplayMap();
    IGraphic * myNl = newGraphic();
    myNl->processInput();
    myNl->render(myMap);
    // switch (myNl->getCommand())
    // {
    //     case 27: //ESC
    //         myGame.Input(Keycode_Exit);
    //         break;
    //     case 32: //SPACE
    //         myGame.Input(Keycode_Pause);
    //         break;
    //     case KEY_UP:
    //         myGame.Input(Keycode_Up);
    //         break;
    //     case KEY_DOWN:
    //         myGame.Input(Keycode_Down);
    //         break;
    //     case KEY_LEFT:
    //         myGame.Input(Keycode_Left);
    //         break;
    //     case KEY_RIGHT:
    //         myGame.Input(Keycode_Right);
    //         break;
    // }
    myMap = myGame.GetDisplayMap();
    myNl->render(myMap);
    return 0;
}