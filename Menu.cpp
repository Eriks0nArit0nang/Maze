#include "Menu.h"
#include "Game.h"
#include "SurvivalGame.h"
#include "Display.h"
#include "Button.h"

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <string>
#include "Globals.h"

using namespace std;
 
#define WHITE al_map_rgb(255, 255, 255)
 
static string read_string(int yCoord)
{
    ALLEGRO_BITMAP *buffer = al_create_bitmap(270,40);
    string  edittext = "";                         // an empty string for editting
    string::iterator iter = edittext.begin(); // string iterator
    int caret  = 0;                       // tracks the text caret
    bool insert = true;                    // true of should text be inserted
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(Display::GetInstance()->GetDisplay()));
    
    ALLEGRO_FONT* font=al_load_bitmap_font("a4_font.tga");
    ALLEGRO_EVENT event;
    bool exit = false;
 
    // the game loop
    do
    {
        while(al_get_next_event(queue,&event))
        {
            int  newkey, keycode;
            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                exit = true;
            else if (event.type == ALLEGRO_EVENT_KEY_CHAR)
            {
                newkey = event.keyboard.unichar;
                keycode = event.keyboard.keycode;
            }
            else
                break;
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
                switch(keycode)
                {
                    case ALLEGRO_KEY_DELETE:
                        if(iter != edittext.end()) iter = edittext.erase(iter);
                        break;
     
                    case ALLEGRO_KEY_BACKSPACE:
                        if(iter != edittext.begin())
                        {
                            caret--;
                            iter--;
                            iter = edittext.erase(iter);
                        }
                        break;
     
                    case ALLEGRO_KEY_RIGHT:
                        if(iter != edittext.end())   caret++, iter++;
                        break;
     
                    case ALLEGRO_KEY_LEFT:
                        if(iter != edittext.begin()) caret--, iter--;
                        break;
     
                    case ALLEGRO_KEY_INSERT:
                        if(insert) insert = 0; else insert = 1;
                        break;
                        
                    case ALLEGRO_KEY_ENTER:
                    case ALLEGRO_KEY_ESCAPE:
                        exit = true;
                        break;
                        
                    default:
     
                        break;
                }
            }
        }
        // clear screen
        al_set_target_bitmap(buffer);
        al_clear_to_color(al_map_rgb(0,0,0));
 
        // output the string to the screen
        al_draw_textf(font, WHITE, 1, 10, 0, "Enter the game name");
        al_draw_textf(font, WHITE, 1, 30, 0, "%s", edittext.c_str());
     
        // draw the caret
        al_draw_line(caret * 8 + 1, 28, caret * 8 + 1, 38, WHITE, 0);
     
        // blit to screen
        al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
        al_draw_bitmap(buffer, 420, yCoord, 0);
        al_flip_display();
    }while(!exit); // end of game loop
      
    al_destroy_bitmap(buffer);
    al_destroy_event_queue(queue);
    al_destroy_font(font);
    
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

