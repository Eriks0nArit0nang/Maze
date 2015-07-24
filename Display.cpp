#include "Display.h"
#include "Globals.h"
#include "Player.h"
#include "Enemy.h"
#include "Game.h"
#include "Map.h"
#include "Button.h"
#include "ButtonManager.h"
#include "MainMenu.h"
#include "UpgradeMenu.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

using namespace std;

Display *Display::instance = 0;

Display *Display::GetInstance()
{
    if (!instance) 
	{
    	cerr << "Creating new display instance...\n";
        instance = new Display();
        cerr << "Display instance created\n";
    }
    return instance;
}

void Display::RemoveInstance()
{
    delete instance;
    instance = 0;
}

Display::Display():Interaction()
{
	cerr << "starting display construction\n";
    al_init_font_addon();
    al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);
    screen = al_create_display(SCREEN_X+MAX_GRID_SIZE*2, SCREEN_Y);
    cerr << "screen initialized\n";
    timer = al_create_timer(25);
    cerr << "timer created\n";
    int size = Map::GetInstance()->GetGridSize();
    cerr << "grid size acquired\n";
    buffer=al_get_backbuffer(screen);
    al_set_target_bitmap(buffer);
    al_clear_to_color(al_map_rgb(0,0,0));
    cerr << "display set up\n";
    al_flip_display();
    miniMap = al_create_bitmap(MAX_GRID_SIZE*2,SCREEN_Y);
    cerr << "minimap constructed\n";
    al_set_target_bitmap(miniMap);
    al_clear_to_color(al_map_rgb(100,100,100));
    cerr << "minimap set up\n";
    font=al_load_bitmap_font("a4_font.tga");
    cerr << "font set up\n";
    upgradeMenu = new UpgradeMenu(buffer);
    cerr << "initializing main menu...\n";
    InitMainMenu(buffer);
    cerr << "main menu initialized\n";
    cerr << "display created\n";
}

Display::~Display()
{
    al_destroy_bitmap(background);
    al_destroy_bitmap(miniMap);
    al_destroy_display(screen);
    al_destroy_timer(timer);
    al_destroy_font(font);
}

void Display::UpdateScreen()
{
    Player *P = Game::GetInstance()->GetPlayer();
    vector<Enemy *> E = Game::GetInstance()->GetEnemies();
    Map *mapInst = Map::GetInstance();
    int size = mapInst->GetGridSize();
    int boxSize = 2*MAX_GRID_SIZE/size;
    al_set_target_bitmap(buffer);
    al_draw_bitmap (background, -(P->GetX()-SCREEN_X/2), -(P->GetY()-SCREEN_Y/2),0);
    al_draw_bitmap (miniMap, SCREEN_X, 0,0);
    al_draw_filled_circle(SCREEN_X+P->GetX()*boxSize/BOX_PIXEL_WIDTH, P->GetY()*boxSize/BOX_PIXEL_WIDTH, 4, al_map_rgb (150,150,255)); // Draw player icon on mini map
    for (int i = 0; i < E.size(); i++)
        if (abs (E[i]->GetX () - P->GetX()) < SCREEN_X/2 && abs (E[i]->GetY() - P->GetY()) < SCREEN_Y/2)
        {
            E[i]->Draw(buffer, SCREEN_X/2-P->GetX(), SCREEN_Y/2-P->GetY());
        }
    P->Draw(buffer, SCREEN_X/2-P->GetX(), SCREEN_Y/2-P->GetY());
    int clipRemaining = P->GetWeaponProperties(_Gun).GetClipSize()-P->GetWeaponProperties(_Gun).GetShotsTaken();
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X+10, 520, 0, "Clip: %d", clipRemaining); 
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X+10, 540, 0, "Health: %d", P->GetHealth());
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X+10, 560, 0, "Enemies: %d", E.size());
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X+10, 580, 0, "Money: %d", P->GetMoney());
    al_flip_display();
}

void Display::DrawUpgrade()
{
    upgradeMenu->Draw(buffer);
}

void Display::InitMainMenu(ALLEGRO_BITMAP *buffer)
{
    mainMenu = new MainMenu(buffer);
}

void Display::DrawMainMenu()
{
    mainMenu->Draw(buffer);
}

void Display::SetBackground ()
{
    Map *mapInst = Map::GetInstance();
    int **map = mapInst->GetGrid();
    int size = mapInst->GetGridSize();
    background=al_create_bitmap(size*BOX_PIXEL_WIDTH,size*BOX_PIXEL_WIDTH);
    al_set_target_bitmap(background);
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_filled_rectangle(0,0,size*BOX_PIXEL_WIDTH,size*BOX_PIXEL_WIDTH,al_map_rgb(0,0,0));
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (map[i][j] == 0)
                al_draw_filled_rectangle(i*BOX_PIXEL_WIDTH,j*BOX_PIXEL_WIDTH,(i+1)*BOX_PIXEL_WIDTH,(j+1)*BOX_PIXEL_WIDTH,al_map_rgb(255,255,255));
            else if (map[i][j] == 2)
            {
                al_draw_filled_rectangle(i*BOX_PIXEL_WIDTH,j*BOX_PIXEL_WIDTH,(i+1)*BOX_PIXEL_WIDTH,(j+1)*BOX_PIXEL_WIDTH,al_map_rgb(255,0,254));
            }
            else if (map[i][j] == 3)
                al_draw_filled_rectangle(i*BOX_PIXEL_WIDTH,j*BOX_PIXEL_WIDTH,(i+1)*BOX_PIXEL_WIDTH,(j+1)*BOX_PIXEL_WIDTH,al_map_rgb(0,255,0));
    
    al_set_target_bitmap(miniMap);
    al_clear_to_color(al_map_rgb(100,100,100));
}

void Display::UpdateMiniMap (int centreX, int centreY)
{
    Map *mapInst = Map::GetInstance();
    int **map = mapInst->GetGrid();
    int size = mapInst->GetGridSize();
    int boxSize = 2*MAX_GRID_SIZE/size;
    al_set_target_bitmap(miniMap);
    for (int i = centreX-5; i < centreX+5 && i >= 0 && i < size; i++)
        for (int j = centreY-5; j < centreY+5 && j >= 0 && j < size; j++)
            if (map[i][j] == 0)
                al_draw_filled_rectangle(i*boxSize,j*boxSize,i*boxSize+boxSize,j*boxSize+boxSize,al_map_rgb(255,255,255));
            else if (map[i][j] == 1)
                al_draw_filled_rectangle(i*boxSize,j*boxSize,i*boxSize+boxSize,j*boxSize+boxSize,al_map_rgb(0,0,0));
            else if (map[i][j] == 2)
                al_draw_filled_rectangle(i*boxSize,j*boxSize,i*boxSize+boxSize,j*boxSize+boxSize,al_map_rgb(255,0,254));
            else if (map[i][j] == 3)
                al_draw_filled_rectangle(i*boxSize,j*boxSize,i*boxSize+boxSize,j*boxSize+boxSize,al_map_rgb(0,255,0));
}

void Display::Zoom (int centreX, int centreY)
{
    Map *mapInst = Map::GetInstance();
    int **map = mapInst->GetGrid();
    int size = mapInst->GetGridSize();
    float boxSize = 2*MAX_GRID_SIZE/11.0;
    
    al_set_target_bitmap(miniMap);
    al_draw_filled_rectangle(0,MAX_GRID_SIZE*2,MAX_GRID_SIZE*2,MAX_GRID_SIZE*4,al_map_rgb (100,100,100));
    for (int i = -5; i <= 5; i++)
        for (int j = -5; j <= 5; j++)
            if (i+centreX >= 0 && i+centreX < size  && j+centreY >= 0 && j+centreY < size)
                if (mapInst->Fog(centreX+i, centreY+j))
                {
                    if (map[centreX+i][centreY+j] == 0)
                        al_draw_filled_rectangle((i+(int)floor(MAX_GRID_SIZE/boxSize))*boxSize,MAX_GRID_SIZE*2+(j+(int)floor(MAX_GRID_SIZE/boxSize))*boxSize,(i+(int)floor(MAX_GRID_SIZE/boxSize)+1)*boxSize,MAX_GRID_SIZE*2+(j+(int)floor(MAX_GRID_SIZE/boxSize)+1)*boxSize,al_map_rgb(255,255,255));
                    else if (map[centreX+i][centreY+j] == 1)
                        al_draw_filled_rectangle((i+(int)floor(MAX_GRID_SIZE/boxSize))*boxSize,MAX_GRID_SIZE*2+(j+(int)floor(MAX_GRID_SIZE/boxSize))*boxSize,(i+(int)floor(MAX_GRID_SIZE/boxSize)+1)*boxSize,MAX_GRID_SIZE*2+(j+(int)floor(MAX_GRID_SIZE/boxSize)+1)*boxSize,al_map_rgb(0,0,0));
                    else if (map[centreX+i][centreY+j] == 2)
                        al_draw_filled_rectangle((i+(int)floor(MAX_GRID_SIZE/boxSize))*boxSize,MAX_GRID_SIZE*2+(j+(int)floor(MAX_GRID_SIZE/boxSize))*boxSize,(i+(int)floor(MAX_GRID_SIZE/boxSize)+1)*boxSize,MAX_GRID_SIZE*2+(j+(int)floor(MAX_GRID_SIZE/boxSize)+1)*boxSize,al_map_rgb(255,0,254));
                    else if (map[centreX+i][centreY+j] == 3)
                        al_draw_filled_rectangle((i+(int)floor(MAX_GRID_SIZE/boxSize))*boxSize,MAX_GRID_SIZE*2+(j+(int)floor(MAX_GRID_SIZE/boxSize))*boxSize,(i+(int)floor(MAX_GRID_SIZE/boxSize)+1)*boxSize,MAX_GRID_SIZE*2+(j+(int)floor(MAX_GRID_SIZE/boxSize)+1)*boxSize,al_map_rgb(0,255,0));
                }    
    
    Player *p = Game::GetInstance()->GetPlayer();
    vector<Enemy *> E = Game::GetInstance()->GetEnemies();
    for (int i = 0; i < E.size(); i++)
        if (E[i]->GetY()/BOX_PIXEL_WIDTH-centreY >= -5 && 
                E[i]->GetY()/BOX_PIXEL_WIDTH-centreY <= 5 && 
                mapInst->Fog(E[i]->GetX()/BOX_PIXEL_WIDTH, E[i]->GetY()/BOX_PIXEL_WIDTH))
            al_draw_rectangle ((E[i]->GetX()/BOX_PIXEL_WIDTH-centreX+(int)floor(MAX_GRID_SIZE/boxSize))*boxSize+1,
                               MAX_GRID_SIZE*2+(E[i]->GetY()/BOX_PIXEL_WIDTH-centreY+(int)floor(MAX_GRID_SIZE/boxSize))*boxSize+1,
                               (E[i]->GetX()/BOX_PIXEL_WIDTH-centreX+(int)floor(MAX_GRID_SIZE/boxSize))*boxSize+boxSize-1,
                               MAX_GRID_SIZE*2+(E[i]->GetY()/BOX_PIXEL_WIDTH-centreY+(int)floor(MAX_GRID_SIZE/boxSize))*boxSize+boxSize-1,
                               al_map_rgb(255,0,0),2);
    if (p->GetY()/BOX_PIXEL_WIDTH-centreY >= -5 && p->GetY()/BOX_PIXEL_WIDTH-centreY <= 5)
        al_draw_rectangle ((p->GetX()/BOX_PIXEL_WIDTH-centreX+(int)floor(MAX_GRID_SIZE/boxSize))*boxSize+1,
                           MAX_GRID_SIZE*2+(p->GetY()/BOX_PIXEL_WIDTH-centreY+(int)floor(MAX_GRID_SIZE/boxSize))*boxSize+1,
                           (p->GetX()/BOX_PIXEL_WIDTH-centreX+(int)floor(MAX_GRID_SIZE/boxSize))*boxSize+boxSize-1,
                           MAX_GRID_SIZE*2+(p->GetY()/BOX_PIXEL_WIDTH-centreY+(int)floor(MAX_GRID_SIZE/boxSize))*boxSize+boxSize-1,
                           al_map_rgb(0,0,255),2);
                           
}

void Display::NukeAnimation ()
{
    al_set_target_bitmap(buffer);
    for (int i = 1; i < 45; i++)
    {
        al_draw_filled_circle (SCREEN_X/2, SCREEN_Y/2, i*10, al_map_rgb(255,i*8,0));
        al_flip_display();
        al_rest(1);
    }
}

void Display::RemoveWall (int xPos, int yPos)
{
    int x1 = xPos/BOX_PIXEL_WIDTH*BOX_PIXEL_WIDTH;
    int x2 = (xPos/BOX_PIXEL_WIDTH+1)*BOX_PIXEL_WIDTH-1;
    int y1 = yPos/BOX_PIXEL_WIDTH*BOX_PIXEL_WIDTH;
    int y2 = (yPos/BOX_PIXEL_WIDTH+1)*BOX_PIXEL_WIDTH-1;
    al_set_target_bitmap(background);
    al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(255,255,255));
}

bool Display::UpdateMainMenuGUI()
{
    return mainMenu->GetButtonManager().Update();
}

bool Display::UpdateUpgradeMenuGUI()
{
    return upgradeMenu->GetButtonManager().Update();
}

ALLEGRO_DISPLAY* Display::GetDisplay() const
{
	std::cerr << "Getting display...\n";
    return screen;
}
