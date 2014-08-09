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
#include <vector>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

using namespace std;

Display *Display::instance = 0;

Display *Display::GetInstance()
{
    if (!instance)
        instance = new Display();
    return instance;
}

void Display::RemoveInstance()
{
    delete instance;
    instance = 0;
}

Display::Display():Interaction()
{
    al_init_font_addon();
    al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);
    screen = al_create_display(SCREEN_X+GRID_SIZE*2, SCREEN_Y);
    timer = al_create_timer(25);
    int size = Map::GetInstance()->GetGridSize();
    buffer=al_get_backbuffer(screen);
    al_set_target_bitmap(buffer);
    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();
    miniMap = al_create_bitmap(size*2,600);
    al_set_target_bitmap(miniMap);
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_filled_rectangle(0,0,size*2,size*4,al_map_rgb(100,100,100));
    background=al_create_bitmap(size*BOX_PIXEL_WIDTH,size*BOX_PIXEL_WIDTH);
    al_set_target_bitmap(background);
    al_clear_to_color(al_map_rgb(0,0,0));
    font=al_load_bitmap_font("a4_font.tga");
    upgradeMenu = new UpgradeMenu(buffer);
    InitMainMenu(buffer);
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
    al_set_target_bitmap(buffer);
    al_draw_bitmap (background, -(P->GetX()-SCREEN_X/2), -(P->GetY()-SCREEN_Y/2),0);
    al_draw_bitmap (miniMap, SCREEN_X, 0,0);
    al_draw_filled_circle(SCREEN_X+P->GetX()/30, P->GetY()/30, 4, al_map_rgb (150,150,255)); // Draw player icon on mini map
    for (int i = 0; i < E.size(); i++)
        if (abs (E[i]->GetX () - P->GetX()) < 300 && abs (E[i]->GetY() - P->GetY()) < 300)
        {
            E[i]->Draw(buffer, SCREEN_X/2-P->GetX(), SCREEN_Y/2-P->GetY());
        }
    P->Draw(buffer, SCREEN_X/2-P->GetX(), SCREEN_Y/2-P->GetY());
    int clipRemaining = P->GetWeaponProperties(_Gun).GetClipSize()-P->GetWeaponProperties(_Gun).GetShotsTaken();
    al_draw_textf(font, al_map_rgb(255,0,0), 500+GRID_SIZE*2, 520, 0, "Clip: %d", clipRemaining); 
    al_draw_textf(font, al_map_rgb(255,0,0), 500+GRID_SIZE*2, 540, 0, "Health: %d", P->GetHealth());
    al_draw_textf(font, al_map_rgb(255,0,0), 500+GRID_SIZE*2, 560, 0, "Enemies: %d", E.size());
    al_draw_textf(font, al_map_rgb(255,0,0), 500+GRID_SIZE*2, 580, 0, "Money: %d", P->GetMoney());
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
    al_set_target_bitmap(background);
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
    al_draw_filled_rectangle(0,0,GRID_SIZE*2,600,al_map_rgb(100,100,100));
}

void Display::UpdateMiniMap (int centreX, int centreY)
{
    Map *mapInst = Map::GetInstance();
    int **map = mapInst->GetGrid();
    int size = mapInst->GetGridSize();
    al_set_target_bitmap(miniMap);
    for (int i = centreX-5; i < centreX+5 && i >= 0 && i < size; i++)
        for (int j = centreY-5; j < centreY+5 && j >= 0 && j < size; j++)
            if (map[i][j] == 0)
                al_draw_filled_rectangle(i*2,j*2,i*2+2,j*2+2,al_map_rgb(255,255,255));
            else if (map[i][j] == 1)
                al_draw_filled_rectangle(i*2,j*2,i*2+2,j*2+2,al_map_rgb(0,0,0));
            else if (map[i][j] == 2)
                al_draw_filled_rectangle(i*2,j*2,i*2+2,j*2+2,al_map_rgb(255,0,254));
            else if (map[i][j] == 3)
                al_draw_filled_rectangle(i*2,j*2,i*2+2,j*2+2,al_map_rgb(0,255,0));
}

void Display::Zoom (int centreX, int centreY)
{
    Map *mapInst = Map::GetInstance();
    int **map = mapInst->GetGrid();
    int size = mapInst->GetGridSize();
    al_set_target_bitmap(miniMap);
    al_draw_filled_rectangle(0,size*2,size*2,size*4,al_map_rgb (100,100,100));
    for (int i = -(int)floor(size/10); i < (int)floor(size/10); i++)
        for (int j = -(int)floor(size/10); j < (int)floor(size/10); j++)
            if (i+centreX >= 0 && i+centreX < size  && j+centreY >= 0 && j+centreY < size)
                if (mapInst->Fog(centreX+i, centreY+j))
                {
                    if (map[centreX+i][centreY+j] == 0)
                        al_draw_filled_rectangle((i+(int)floor(size/10))*10,size*2+(j+(int)floor(size/10))*10,(i+(int)floor(size/10)+1)*10,size*2+(j+(int)floor(size/10)+1)*10,al_map_rgb(255,255,255));
                    else if (map[centreX+i][centreY+j] == 1)
                        al_draw_filled_rectangle((i+(int)floor(size/10))*10,size*2+(j+(int)floor(size/10))*10,(i+(int)floor(size/10)+1)*10,size*2+(j+(int)floor(size/10)+1)*10+10,al_map_rgb(0,0,0));
                    else if (map[centreX+i][centreY+j] == 2)
                        al_draw_filled_rectangle((i+(int)floor(size/10))*10,size*2+(j+(int)floor(size/10))*10,(i+(int)floor(size/10)+1)*10,size*2+(j+(int)floor(size/10)+1)*10,al_map_rgb(255,0,254));
                    else if (map[centreX+i][centreY+j] == 3)
                        al_draw_filled_rectangle((i+(int)floor(size/10))*10,size*2+(j+(int)floor(size/10))*10,(i+(int)floor(size/10)+1)*10,size*2+(j+(int)floor(size/10)+1)*10,al_map_rgb(0,255,0));
                }    
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
    return screen;
}
