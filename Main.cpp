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
Wall breakers - switch active weapon?
Upgrade store - use buttons
graphics quality
*/

void cleanup(void)
{
    Input::RemoveInstance();
    Display::RemoveInstance();
    Map::RemoveInstance();
    Game::RemoveInstance();
}

int main (int argc, int* argv)
{
    
    // Set up logging
    std::ofstream out("log.txt");
    std::cerr.rdbuf(out.rdbuf());
    
    Display *display = Display::GetInstance();
    Input *input = Input::GetInstance();
    Game *game = Game::GetInstance();

    while (!input->IsClosed())
    {
        bool action = false;
        display->DrawMainMenu();
        while (!action)
        {
            action = display->UpdateGUI();
            input->ReadInput();
            if (input->IsClosed())
                action = true;
        }
    }
    
    cleanup();
    out.close();
}
