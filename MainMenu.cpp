#include "MainMenu.h"
#include "Game.h"
#include "SurvivalGame.h"
#include "Display.h"
#include "Input.h"
#include "Button.h"

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <string>
#include <vector>
#include "Globals.h"

using namespace std;
 
#define WHITE al_map_rgb(255, 255, 255)
 
MainMenu::MainMenu(ALLEGRO_BITMAP *buffer)
{
    mainMenu = al_load_bitmap ("MainMenu.bmp");
    Init(buffer);
}

MainMenu::~MainMenu()
{
    al_destroy_bitmap(mainMenu);
}
 
void MainMenu::Draw(ALLEGRO_BITMAP *buffer)
{
    al_set_target_bitmap(buffer);
    al_clear_to_color(al_map_rgb(100,100,100));
    al_draw_bitmap(mainMenu,0,0,0);
    buttonManager.Update();
    buttonManager.Render(buffer);
    al_flip_display();
}

void MainMenu::Init(ALLEGRO_BITMAP *buffer)
{
    Button *create = new Button();
    create->SetCaption("Create Game");
    create->SetSize(120, 40);
    create->Create();
    create->OnClick = MainMenu::Create;
    create->SetPosition(SCREEN_X-150, SCREEN_Y-375);
    buttonManager.AddButton(create);
    Button *play = new Button();
    play->SetCaption("Play Game");
    play->SetSize(120, 40);
    play->Create();
    play->OnClick = MainMenu::Play;
    play->SetPosition(SCREEN_X-150, SCREEN_Y-275);
    buttonManager.AddButton(play);
    Button *survival = new Button();
    survival->SetCaption("Survival Game");
    survival->SetSize(120, 40);
    survival->Create();
    survival->OnClick = MainMenu::Survival;
    survival->SetPosition(SCREEN_X-150, SCREEN_Y-175);
    buttonManager.AddButton(survival);
}

ButtonManager &MainMenu::GetButtonManager()
{
    return buttonManager;
}

string MainMenu::ReadString(int yCoord, int type)
{
	cerr << "reading game name...\n";
    ALLEGRO_BITMAP *buffer = al_create_bitmap(180,40);
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
    // List existing games
    ALLEGRO_DISPLAY *display;
    if (type == 1 || type == 2)
    {
        vector <string> gameNames = Game::GetInstance()->GetGameNames();
        al_set_target_bitmap(al_get_backbuffer(Display::GetInstance()->GetDisplay()));
        al_draw_text(font, WHITE, SCREEN_X+1, 10, 0, "Valid Games");
        for (int i = 0; i < gameNames.size(); i++)
            al_draw_textf(font, WHITE, SCREEN_X+1, 30+i*15, 0, "%s", gameNames[i].c_str());
        al_flip_display();
    }
    
    cerr << "ready to read...\n";
    
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
    // the main loop
    do
    {
    	string old_text = edittext;
        while(al_get_next_event(queue,&event))
        {
            int  newkey, keycode;
            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                exit = true;
                Input::GetInstance()->ForceClose();
            }
            else if (event.type == ALLEGRO_EVENT_KEY_CHAR)
            {
                newkey = event.keyboard.unichar;
                keycode = event.keyboard.keycode;
            }
            else
                break;
            char ASCII = newkey & 0xff;
     
            // a character key was pressed; add it to the string
            if(ASCII >= 32 && ASCII <= 126 && edittext.size() < 21)
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
        if (old_text != edittext)
        {
	        // clear screen
	        al_set_target_bitmap(buffer);
	        al_clear_to_color(al_map_rgb(0,0,0));
	        // output the string to the screen
	        cerr << "seriously?\n";
	        al_draw_textf(font, WHITE, 1, 10, 0, "Enter the game name");
	        cerr << "wtf\n" << font << endl << edittext.c_str() << endl;
	        al_draw_textf(font, WHITE, 1, 30, 0, "%s", edittext.c_str());
	        cerr << "I don't understand\n";
	
	        // draw the caret
	        al_draw_line(caret * 8 + 1, 28, caret * 8 + 1, 38, WHITE, 0);
	        // blit to screen
	        al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
	        al_draw_bitmap(buffer, 420, yCoord, 0);
	        al_flip_display();
	    }
    } while(!exit); // end of game loop
    
    cerr << "finished reading input\n";
    al_destroy_bitmap(buffer);
    al_destroy_event_queue(queue);
    al_destroy_font(font);
    
    return edittext;
}

int MainMenu::ReadSize()
{
    int size = GRID_SIZE-10;
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(Display::GetInstance()->GetDisplay()));
    
    ALLEGRO_FONT* font=al_load_bitmap_font("a4_font.tga");
    ALLEGRO_EVENT event;
    bool exit = false;
    
    ButtonManager bManager;
    Button *up = new Button();
    up->SetCaption("Increase");
    up->SetSize(40, 20);
    up->Create();
    up->OnClick = MainMenu::Larger;
    up->SetMiscData (&size);
    up->SetPosition(SCREEN_X+35, 20);
    bManager.AddButton(up);
    Button *down = new Button();
    down->SetCaption("Decrease");
    down->SetSize(40, 20);
    down->Create();
    down->OnClick = MainMenu::Smaller;
    down->SetMiscData (&size);
    down->SetPosition(SCREEN_X+35, 70);
    bManager.AddButton(down);
    Button *close = new Button();
    close->SetCaption("Done");
    close->SetSize(40, 20);
    close->Create();
    close->OnClick = MainMenu::SetClose;
    close->SetMiscData (&exit);
    close->SetPosition(SCREEN_X+50, 100);
    bManager.AddButton(close);
    
    
    al_set_target_bitmap(al_get_backbuffer(Display::GetInstance()->GetDisplay()));
    al_draw_text(font, WHITE, SCREEN_X+20, 5, 0, "Set Grid Size");
    al_draw_textf(font, WHITE, SCREEN_X+63, 50, 0, "%d", size);
    bManager.Render(al_get_backbuffer(Display::GetInstance()->GetDisplay()));
    al_flip_display();
    
    while (!exit)
    {
        while(al_get_next_event(queue,&event))
        {
            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                exit = true;
                Input::GetInstance()->ForceClose();
            }
            else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
            {
                Input::GetInstance()->ForceClick(true,event.mouse.x,event.mouse.y);
            }
            else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
            {
                Input::GetInstance()->ForceClick(false,event.mouse.x,event.mouse.y);
            }
            else
                break;
            bManager.Update();
            al_draw_filled_rectangle(SCREEN_X+63,50, SCREEN_X+93, 60, al_map_rgb(100,100,100));
            al_draw_textf(font, WHITE, SCREEN_X+63, 50, 0, "%d", size);
            al_flip_display();
        }
    }
    
    al_destroy_font(font);
    al_destroy_event_queue(queue);
    return size;
}

int MainMenu::ReadDifficulty()
{
    int difficulty = 5;
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    al_register_event_source(queue, al_get_mouse_event_source());
    
    ALLEGRO_FONT* font=al_load_bitmap_font("a4_font.tga");
    ALLEGRO_EVENT event;
    bool exit = false;
    ALLEGRO_DISPLAY* display = Display::GetInstance()->GetDisplay();

    al_register_event_source(queue, al_get_display_event_source(display));
    
    ButtonManager bManager;
    Button *beg = new Button();
    beg->SetCaption("Beginner");
    beg->SetSize(40, 20);
    beg->Create();
    beg->OnClick = MainMenu::Beginner;
    beg->SetMiscData (&difficulty);
    beg->SetPosition(SCREEN_X+35, 320);
    bManager.AddButton(beg);
    Button *easy = new Button();
    easy->SetCaption("Easy");
    easy->SetSize(40, 20);
    easy->Create();
    easy->OnClick = MainMenu::Easy;
    easy->SetMiscData (&difficulty);
    easy->SetPosition(SCREEN_X+35, 350);
    bManager.AddButton(easy);
    Button *medium = new Button();
    medium->SetCaption("Medium");
    medium->SetSize(40, 20);
    medium->Create();
    medium->OnClick = MainMenu::Medium;
    medium->SetMiscData (&difficulty);
    medium->SetPosition(SCREEN_X+35, 380);
    bManager.AddButton(medium);
    Button *hard = new Button();
    hard->SetCaption("Hard");
    hard->SetSize(40, 20);
    hard->Create();
    hard->OnClick = MainMenu::Hard;
    hard->SetMiscData (&difficulty);
    hard->SetPosition(SCREEN_X+35, 410);
    bManager.AddButton(hard);
    Button *expert = new Button();
    expert->SetCaption("Expert");
    expert->SetSize(40, 20);
    expert->Create();
    expert->OnClick = MainMenu::Expert;
    expert->SetMiscData (&difficulty);
    expert->SetPosition(SCREEN_X+35, 440);
    bManager.AddButton(expert);
    
    al_set_target_bitmap(al_get_backbuffer(display));
    al_draw_text(font, WHITE, SCREEN_X+10, 301, 0, "Choose Difficulty");
    bManager.Render(al_get_backbuffer(display));
    al_flip_display();
    
    while (!exit)
    {
        while(al_get_next_event(queue,&event))
        {
            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                exit = true;
                Input::GetInstance()->ForceClose();
            }
            else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
            {
                Input::GetInstance()->ForceClick(true,event.mouse.x,event.mouse.y);
            }
            else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
            {
                Input::GetInstance()->ForceClick(false,event.mouse.x,event.mouse.y);
            }
            else
                break;
            if (!exit)
                exit = bManager.Update();
        }
    }
    
    al_destroy_font(font);
    al_destroy_event_queue(queue);
    return difficulty;
}

void MainMenu::Create(Button* object, void* data)
{
	cerr << "Creating a new game...\n";
    Game *game = Game::GetInstance();
    cerr << "Retrieved game instance\n";
    string name = ReadString(object->GetY()+45,3);
    cerr << "game name: " << name << endl;
    if (Input::GetInstance()->IsClosed())   
        return;
    int size = ReadSize() + 10;
    if (Input::GetInstance()->IsClosed())   
        return;
    game->Create(name, size);
    cerr << "Game created\n";
}

void MainMenu::Survival(Button* object, void* data)
{
    Game *game = Game::GetInstance();
    SurvivalGame::NewInstance();
    game = Game::GetInstance();
    string name = ReadString(object->GetY()+45,2);
    if (Input::GetInstance()->IsClosed())   
        return;
    int difficulty = ReadDifficulty();
    if (Input::GetInstance()->IsClosed())   
        return;
    if (game->Valid(name))
        game->Play(name, difficulty);
    else
        cerr << "Invalid game name \"" << name << "\"\n";
}

void MainMenu::Play(Button* object, void* data)
{
    Game *game = Game::GetInstance();
    string name = ReadString(object->GetY()+45,1);
    if (Input::GetInstance()->IsClosed())   
        return;
    int difficulty = ReadDifficulty();
    if (Input::GetInstance()->IsClosed())   
        return;
    if (game->Valid(name))
        game->Play(name, difficulty);
    else
        cerr << "Invalid game name \"" << name << "\"\n";
}

void MainMenu::Larger(Button* object, void* data)
{
    if (*static_cast<int*>(data) < 90)
        (*static_cast<int*>(data))++;
}

void MainMenu::Smaller(Button* object, void* data)
{
    if (*static_cast<int*>(data) > 10)
        (*static_cast<int*>(data))--;
}

void MainMenu::SetClose(Button* object, void* data)
{
    (*static_cast<bool*>(data)) = true;
}

void MainMenu::Beginner(Button* object, void* data)
{
    (*static_cast<int*>(data)) = 0;
}

void MainMenu::Easy(Button* object, void* data)
{
    (*static_cast<int*>(data)) = 1;
}

void MainMenu::Medium(Button* object, void* data)
{
    (*static_cast<int*>(data)) = 4;
}

void MainMenu::Hard(Button* object, void* data)
{
    (*static_cast<int*>(data)) = 7;
}

void MainMenu::Expert(Button* object, void* data)
{
    (*static_cast<int*>(data)) = 8;
}
