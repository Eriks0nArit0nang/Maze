#include "Menu.h"
#include "Game.h"
#include "SurvivalGame.h"
#include "Interaction.h"
#include "Button.h"

#include <iostream>
#include <allegro.h>
#include <string>
#include "Globals.h"

using namespace std;
 
#define WHITE makecol(255, 255, 255)
 
static string read_string(int yCoord)
{
    BITMAP *buffer = create_bitmap(270,40);
    string  edittext;                         // an empty string for editting
    string::iterator iter = edittext.begin(); // string iterator
    int caret  = 0;                       // tracks the text caret
    bool insert = true;                    // true of should text be inserted
 
    // the game loop
    do
    {
        while(keypressed())
        {
            int  newkey = readkey();
            readkey();
            char ASCII = newkey & 0xff;
            char scancode = newkey >> 8;
     
            // a character key was pressed; add it to the string
            if(ASCII >= 32 && ASCII <= 126 && edittext.size() < 30)
            {
                // add the new char, inserting or replacing as need be
                if(insert || iter == edittext.end())
                    iter = edittext.insert(iter, ASCII);
                else
                    edittext.replace(caret, 1, 1, ASCII);
     
                // increment both the caret and the iterator
                caret++;
                iter++;
            }
            // some other, "special" key was pressed; handle it here
            else
            {
                switch(scancode)
                {
                    case KEY_DEL:
                        if(iter != edittext.end()) iter = edittext.erase(iter);
                        break;
     
                    case KEY_BACKSPACE:
                        if(iter != edittext.begin())
                        {
                            caret--;
                            iter--;
                            iter = edittext.erase(iter);
                        }
                        break;
     
                    case KEY_RIGHT:
                        if(iter != edittext.end())   caret++, iter++;
                        break;
     
                    case KEY_LEFT:
                        if(iter != edittext.begin()) caret--, iter--;
                        break;
     
                    case KEY_INSERT:
                        if(insert) insert = 0; else insert = 1;
                        break;
     
                    default:
     
                        break;
                }
            }
        }
        clear_keybuf();
        // clear screen
        clear(buffer);
 
        // output the string to the screen
        textprintf_ex(buffer, font, 0, 10, WHITE, -1, "Enter the game name");
        textprintf_ex(buffer, font, 0, 30, WHITE, -1, edittext.c_str());
     
        // draw the caret
        vline(buffer, caret * 8, 28, 38, WHITE);
     
        // blit to screen
        draw_sprite(screen, buffer, 420, yCoord);
    }while(!key[KEY_ESC] && !key[KEY_ENTER] && !close_button_pressed); // end of game loop
    
    destroy_bitmap(buffer);
    
    return edittext;
}

void Menu::Create(Button* object, void* data)
{
    Game *game = Game::GetInstance();
    string name = read_string(object->GetY()+45);
    game->Create(name);
}

void Menu::Survival(Button* object, void* data)
{
    Game *game = Game::GetInstance();
    SurvivalGame::NewInstance();
    game = Game::GetInstance();
    string name = read_string(object->GetY()+45);
    if (game->Valid(name))
        game->Play(name, 1);
    else
        cerr << "Invalid game name \"" << name << "\"\n";
}

void Menu::Play(Button* object, void* data)
{
    Game *game = Game::GetInstance();
    string name = read_string(object->GetY()+45);
    if (game->Valid(name))
        game->Play(name, 1);
    else
        cerr << "Invalid game name \"" << name << "\"\n";
}

