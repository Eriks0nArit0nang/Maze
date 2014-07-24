// Maze game
using namespace std;
#include "Display.h"
#include "Input.h"
#include "Game.h"
#include "SurvivalGame.h"
#include "Map.h"

#include <iostream>

/*
Issues
Weapons
Upgrade store
graphics
*/

int main ()
{
    Display::GetInstance();
    Input::GetInstance();
    Game *game = Game::GetInstance();

    cout << "Press A Key\nC to create a game (20 Levels)\nS to play in Survival Mode\nAny other key to load\n";
    readkey();
    
    if (key[KEY_C])
    {
         game->Create("Game 1");
    }
    else if (key[KEY_S])
    {
        SurvivalGame::NewInstance();
        game = Game::GetInstance();
        game->Play("Game 1", 1);
    }
    else
    {
         game->Play("Game 1", 1);
    }
    rest(2000);
    cout << "Please Press A Key\n";
    clear_keybuf();
    while (!close_button_pressed && !keypressed()){}
    cout << "Thank You\n";
    Input::RemoveInstance();
    Display::RemoveInstance();
    Map::RemoveInstance();
    Game::RemoveInstance();
}
END_OF_MAIN();
