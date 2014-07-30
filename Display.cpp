#include "Display.h"
#include "Globals.h"
#include "Player.h"
#include "Enemy.h"
#include "Game.h"
#include "Map.h"
#include "Button.h"
#include "ButtonManager.h"
#include "Menu.h"
#include <cmath>
#include <vector>
#include <allegro5/allegro_font.h>

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
    screen = al_create_display(SCREEN_X+GRID_SIZE*2, SCREEN_Y);
    timer = al_create_timer(25);
    int size = Map::GetInstance()->GetGridSize();

    upgradeScreen = al_load_bmp ("Upgrade.bmp",NULL);
    mainMenu = al_load_bmp ("MainMenu.bmp",NULL);
    buffer=al_get_backbuffer(display);
    miniMap = al_create_bitmap(size*2,600);
    rectfill (miniMap,0,0,size*2,size*4,al_map_rgb(100,100,100));
    background=al_create_bitmap(SCREEN_X*12,SCREEN_Y*12);
    InitMainMenu();
}

Display::~Display()
{
    destroy_bitmap(buffer);
    destroy_bitmap(background);
}

int Display::RotateReallignedSprite (BITMAP* screen, BITMAP* sprite, int x, int y, int angle)
{
    int size_x = sprite -> w, size_y = sprite -> h; 
    if (abs(angle) == 64 || abs(angle) == 192)
        rotate_sprite (screen, sprite, x+(size_y-size_x)/2, y+(size_y-size_x)/2+60-size_y, itofix (angle));
    else
        rotate_sprite (screen, sprite, x, y+60-size_y, itofix (angle)); 
}

void Display::UpdateScreen()
{
    Player *P = Game::GetInstance()->GetPlayer();
    vector<Enemy *> E = Game::GetInstance()->GetEnemies();
    Map *mapInst = Map::GetInstance();
    int size = mapInst->GetGridSize();
    draw_sprite (buffer, background, -(P->GetX()-SCREEN_X/2), -(P->GetY()-SCREEN_Y/2));
    draw_sprite (buffer, miniMap, SCREEN_X, 0);
    circlefill (buffer, SCREEN_X+P->GetX()/30, P->GetY()/30, 4, al_map_rgb (150,150,255)); // Draw player icon on mini map
    for (int i = 0; i < E.size(); i++)
        if (abs (E[i]->GetX () - P->GetX()) < 300 && abs (E[i]->GetY() - P->GetY()) < 300)
        {
            E[i]->Draw(buffer, SCREEN_X/2-P->GetX(), SCREEN_Y/2-P->GetY());
        }
    P->Draw(buffer, SCREEN_X/2-P->GetX(), SCREEN_Y/2-P->GetY());
    int clipRemaining = P->GetWeaponProperties(_Gun).GetClipSize()-P->GetWeaponProperties(_Gun).GetShotsTaken();
    al_draw_textf(buffer, font, 500+GRID_SIZE*2, 480, al_map_rgb(255,0,0), -1, "Clip: %d", clipRemaining);
    al_draw_textf(buffer, font, 500+GRID_SIZE*2, 500, al_map_rgb(255,0,0), -1, "Health: %d", P->GetHealth());
    al_draw_textf(buffer, font, 500+GRID_SIZE*2, 520, al_map_rgb(255,0,0), -1, "Enemies: %d", E.size());
    al_draw_textf(buffer, font, 500+GRID_SIZE*2, 540, al_map_rgb(255,0,0), -1, "Money: %d", P->GetMoney());
    al_draw_textf(buffer, font, 500+GRID_SIZE*2, 560, al_map_rgb(255,0,0), -1, "Weapon:");
    al_draw_textf(buffer, font, 500+GRID_SIZE*2, 580, al_map_rgb(255,0,0), -1, "%s", P->GetActiveWeapon() == _Gun ? "Gun" : ( P->GetActiveWeapon() == _Grenade ? "Grenade" : "Walls"));
     
    scare_mouse();
    acquire_screen();
    release_screen(); 
    unscare_mouse();
}

void Display::DrawUpgrade()
{
    Player &P = *Game::GetInstance()->GetPlayer();
    draw_sprite (buffer,upgradeScreen,0,0);
    int rate = P.GetWeaponProperties(_Gun).GetFireRate();
    int clip = P.GetWeaponProperties(_Gun).GetClipSize();
    int range = P.GetWeaponProperties(_Gun).GetRange();
    int health = P.GetHealth();
    int money = P.GetMoney();
    WeaponProperties nuke = P.GetWeaponProperties(_Nuke);
    WeaponProperties wideShot = P.GetWeaponProperties(_WideShot);
    WeaponProperties grenade = P.GetWeaponProperties(_Grenade);
    WeaponProperties explodingShot = P.GetWeaponProperties(_ExplodingShot);
    WeaponProperties mine = P.GetWeaponProperties(_Mine);
    WeaponProperties wallBreaker = P.GetWeaponProperties(_WallBreaker);
    al_set_target_bitmap(buffer);
    al_draw_textf(font, 180, 162, al_map_rgb(255,255,255), -1, "%d Cost: %d", rate, 250*(11-rate)*(11-rate));
    al_draw_textf(font, 180, 201, al_map_rgb(255,255,255), -1, "%d Cost: %d", clip, 10*clip);
    al_draw_textf(buffer, font, 180, 240, al_map_rgb(255,255,255), -1, "%d Cost: %d", range, 100*(range/BOX_PIXEL_WIDTH));
    al_draw_textf(font, 180, 279, al_map_rgb(255,255,255), -1, "%d Cost: %d", health, 100+P.GetAddedHealth()/4);
    al_draw_textf(font, 300, 162, al_map_rgb(255,255,255), -1, "Money: %d", money);
    al_draw_textf(font, 400, 355, al_map_rgb(255,255,255), -1, "N %d Cost: %d", nuke.GetWeaponQuantity(), nuke.GetCost());
    al_draw_textf(font, 400, 394, al_map_rgb(255,255,255), -1, "W %d Cost: %d", wideShot.GetWeaponQuantity(), wideShot.GetCost());
    al_draw_textf(font, 400, 433, al_map_rgb(255,255,255), -1, "G %d Cost: %d", grenade.GetWeaponQuantity(), grenade.GetCost());
    al_draw_textf(font, 400, 472, al_map_rgb(255,255,255), -1, "E %d Cost: %d", explodingShot.GetWeaponQuantity(), explodingShot.GetCost());
    al_draw_textf(font, 400, 511, al_map_rgb(255,255,255), -1, "M %d Cost: %d", mine.GetWeaponQuantity(), mine.GetCost());
    al_draw_textf(font, 400, 550, al_map_rgb(255,255,255), -1, "S %d Cost: %d", wallBreaker.GetWeaponQuantity(), wallBreaker.GetCost());
}

void Display::InitMainMenu()
{
    Button *create = new Button();
    create->SetCaption("Create Game");
    create->SetSize(120, 40);
    create->Create();
    create->OnClick = Menu::Create;
    create->SetPosition(buffer, -100, -375);
    buttonManager.AddButton(create);
    Button *play = new Button();
    play->SetCaption("Play Game");
    play->SetSize(120, 40);
    play->Create();
    play->OnClick = Menu::Play;
    play->SetPosition(buffer, -100, -275);
    buttonManager.AddButton(play);
    Button *survival = new Button();
    survival->SetCaption("Survival Game");
    survival->SetSize(120, 40);
    survival->Create();
    survival->OnClick = Menu::Survival;
    survival->SetPosition(buffer, -100, -175);
    buttonManager.AddButton(survival);
    
}

void Display::DrawMainMenu()
{
    al_set_target_bitmap(buffer);
    al_draw_bitmap(mainMenu,0,0,0);
    buttonManager.Update();
    buttonManager.Render(buffer);
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
                al_draw_filled_rectangle(i*BOX_PIXEL_WIDTH,j*BOX_PIXEL_WIDTH,(i+1)*BOX_PIXEL_WIDTH-1,(j+1)*BOX_PIXEL_WIDTH-1,al_map_rgb(255,255,255));
            else if (map[i][j] == 2)
            {
                al_draw_filled_rectangle(i*BOX_PIXEL_WIDTH,j*BOX_PIXEL_WIDTH,(i+1)*BOX_PIXEL_WIDTH-1,(j+1)*BOX_PIXEL_WIDTH-1,al_map_rgb(255,0,254));
            }
            else if (map[i][j] == 3)
                al_draw_filled_rectangle(i*BOX_PIXEL_WIDTH,j*BOX_PIXEL_WIDTH,(i+1)*BOX_PIXEL_WIDTH-1,(j+1)*BOX_PIXEL_WIDTH-1,al_map_rgb(0,255,0));
    
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
                al_draw_filled_rectangle(i*2,j*2,i*2+1,j*2+1,al_map_rgb(255,255,255));
            else if (map[i][j] == 1)
                al_draw_filled_rectangle(i*2,j*2,i*2+1,j*2+1,al_map_rgb(0,0,0));
            else if (map[i][j] == 2)
                al_draw_filled_rectangle(i*2,j*2,i*2+1,j*2+1,al_map_rgb(255,0,254));
            else if (map[i][j] == 3)
                al_draw_filled_rectangle(i*2,j*2,i*2+1,j*2+1,al_map_rgb(0,255,0));
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
                        al_draw_filled_rectangle((i+(int)floor(size/10))*10,size*2+(j+(int)floor(size/10))*10,(i+(int)floor(size/10))*10+9,size*2+(j+(int)floor(size/10))*10+9,al_map_rgb(255,255,255));
                    else if (map[centreX+i][centreY+j] == 1)
                        al_draw_filled_rectangle((i+(int)floor(size/10))*10,size*2+(j+(int)floor(size/10))*10,(i+(int)floor(size/10))*10+9,size*2+(j+(int)floor(size/10))*10+9,al_map_rgb(0,0,0));
                    else if (map[centreX+i][centreY+j] == 2)
                        al_draw_filled_rectangle((i+(int)floor(size/10))*10,size*2+(j+(int)floor(size/10))*10,(i+(int)floor(size/10))*10+9,size*2+(j+(int)floor(size/10))*10+9,al_map_rgb(255,0,254));
                    else if (map[centreX+i][centreY+j] == 3)
                        al_draw_filled_rectangle((i+(int)floor(size/10))*10,size*2+(j+(int)floor(size/10))*10,(i+(int)floor(size/10))*10+9,size*2+(j+(int)floor(size/10))*10+9,al_map_rgb(0,255,0));
                }    
}

void Display::NukeAnimation ()
{
    al_set_target_bitmap(buffer);
    for (int i = 1; i < 45; i++)
    {
        al_draw_filled_circle (SCREEN_X/2, SCREEN_Y/2, i*10, al_map_rgb(255,i*8,0));
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
