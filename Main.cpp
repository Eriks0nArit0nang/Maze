// Maze game
using namespace std;
#include "Display.h"
#include "Input.h"
#include "Game.h"
#include "Map.h"

#include <iostream>
#include <fstream>

void cleanup(void)
{
    Input::RemoveInstance();
    Display::RemoveInstance();
    Map::RemoveInstance();
    Game::RemoveInstance();
}

int main (int argc, char** argv)
{
    
    // Set up logging
    std::ofstream out("log.txt");
    std::cerr.rdbuf(out.rdbuf());
    
    cerr << "Initializing...\n";
    Display *display = Display::GetInstance();
    cerr << "Display fully initialized\n\n";
    Input *input = Input::GetInstance();
    cerr << "Input fully initialized\n\n";
    Game::GetInstance();
    cerr << "Game fully initialized\n\n";

    while (!input->IsClosed())
    {
        bool action = false;
        display->DrawMainMenu();
        while (!action)
        {
            action = display->UpdateMainMenuGUI();
            input->ReadInput();
            if (input->IsClosed())
                action = true;
        }
    }
    
    cleanup();
    out.close();
}
