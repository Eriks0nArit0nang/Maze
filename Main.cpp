// Maze game
using namespace std;
#include "Globals.h"
#include <allegro.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>
#include <string>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Bullet.h"
#include "Allegro Functions.h"
void play_level (pair <int[4],int[GRID_SIZE][GRID_SIZE]> grid, Player &P1, int diff, int diffMult);
#include "Level Creator.h"
#include "In Game Upgrades.h"
#include "Survival Mode.h"
#include "Regular Game.h"
#include "Multiplayer.h"

#include "Map.h"

/*
Issues
Weapons
Upgrade store
graphics
*/

int main ()
{
    srand(time(0));
    start_allegro();
    pair <int[4],int[GRID_SIZE][GRID_SIZE]> level;
    cout << "Press A Key\nC to create a level\nA to generate a level\nG to create a game (20 Levels)\nP to play a selected game\nS to play survival mode (occasional glitches)\nM to play multiplayer\nAny other key to load\nAll individual levels will be saved as level.txt\n";
    readkey();
    Player P1;
    if (key[KEY_C])
    {
       level = generate_level();
       if (verify_level(level.first,level.second))// Confirm that it is a winnable level
       {
          output_level ("Level.txt",level.second,level.first);
          /*P1 =*/ play_level (level,P1);
          if (P1.Get_Health() > 0 && !close_button_pressed)
             cout << "WINNER\n";
       }
    }
    else if (key[KEY_A])
    {
       Map *map = Map::GetInstance();
       map->CreateAuto();
       for (int i = 0; i < GRID_SIZE; i++)
          for (int j = 0; j < GRID_SIZE; j++)
              level.second[i][j] = map->GetGrid()[i][j];
       level.first[0] = map->GetStartLoc().first;
       level.first[1] = map->GetStartLoc().second;
       level.first[2] = map->GetEndLoc().first;
       level.first[3] = map->GetEndLoc().second;
       set_background (level.second);
       Map::RemoveInstance();
     //  level = auto_level();
       if (true)//verify_level(level.first,level.second))// Confirm that it is a winnable level
       {
          output_level ("Level.txt",level.second,level.first);
          /*P1 =*/ play_level (level,P1);
          if (P1.Get_Health() > 0 && !close_button_pressed)
             cout << "WINNER\n";
       }
    }
    else if (key[KEY_S])
    {
         level = input_level ("Survival Maps/Map_1.txt");
         survival (level);
    }
    else if (key[KEY_G])
    {
         create_game();
    }
    else if (key[KEY_P])
    {
         play_game ();
    }
    else if (key[KEY_M])
    {
         multiplayer();
    }
    else
    {
        level = input_level ("Level.txt");
        play_level (level,P1);
    }
    rest(2000);
    cout << "Please Press A Key\n";
    clear_keybuf();
    while (!close_button_pressed && !keypressed()){}
    cout << "Thank You\n";
    close_allegro();
}
END_OF_MAIN();
