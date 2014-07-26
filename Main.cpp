// Maze game
using namespace std;
#include "Display.h"
#include "Input.h"
#include "Game.h"
#include "Map.h"

#include <iostream>
#include <fstream>

/*
Issues
Shooting Grenades
Upgrade store
graphics
*/

void cleanup()
{
    Input::RemoveInstance();
    Display::RemoveInstance();
    Map::RemoveInstance();
    Game::RemoveInstance();
}

int main ()
{
    atexit(cleanup);
    
    // Set up logging
    std::ofstream out("log.txt");
    std::cerr.rdbuf(out.rdbuf());
    
    Display *display = Display::GetInstance();
    Input::GetInstance();
    Game *game = Game::GetInstance();

    while (!close_button_pressed)
    {
        display->DrawMainMenu();
        rest(1);
    }
}
END_OF_MAIN();
