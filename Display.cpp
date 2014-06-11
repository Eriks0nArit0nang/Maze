#include "Display.h"
#include "Globals.h"
#include "Player.h"
#include "Map.h"
#include <cmath>

using namespace std;

Display::Display()
{
    int size = Map::GetInstance()->GetGridSize();
    show_mouse(screen);
    upgradeScreen = load_bmp ("Upgrade.bmp",NULL);
    buffer=create_bitmap(SCREEN_X+size*2,SCREEN_Y);
    miniMap = create_bitmap(size*2,600);
    rectfill (miniMap,0,0,size*2,size*4,makecol(100,100,100));
    background=create_bitmap(size*12,size*12);
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
    //Player &P, vector <Enemy> &E, Bullet &B, int shotX, int shotY, bool shot, volatile char key[KEY_MAX]
  /*   draw_sprite (buffer, background, -(P.Get_X()-SCREEN_X/2), -(P.Get_Y()-SCREEN_Y/2));
     draw_sprite (buffer, miniMap, SCREEN_X, 0);
     circlefill (buffer, SCREEN_X+P.Get_X()/30, P.Get_Y()/30, 4, makecol (150,150,255));
     for (int i = 0; i < E.size(); i++)
         if (abs (E[i].Get_X () - P.Get_X()) < 300 && abs (E[i].Get_Y() - P.Get_Y()) < 300)
         {
            if (E[i].Get_Type() == 3 || E[i].Get_Type() == 4)
            {
               int x = SCREEN_X/2+E[i].Get_X()-P.Get_X(), y = SCREEN_Y/2+E[i].Get_Y()-P.Get_Y();
               triangle (buffer, x,y+E[i].Get_Rad()/2,x+3*E[i].Get_Rad()/2,y,x-3*E[i].Get_Rad()/2,y,makecol(255,0,0));
            }
            if (E[i].Get_Type() <= 4)
               circlefill (buffer, SCREEN_X/2+E[i].Get_X()-P.Get_X() , SCREEN_Y/2+E[i].Get_Y()-P.Get_Y() , E[i].Get_Rad(), makecol (255,255,0));
            else
                circlefill (buffer, SCREEN_X/2+E[i].Get_X()-P.Get_X() , SCREEN_Y/2+E[i].Get_Y()-P.Get_Y() , E[i].Get_Rad(), makecol (255,150,150));
            circlefill (buffer, SCREEN_X/2+E[i].Get_X()-P.Get_X() , SCREEN_Y/2+E[i].Get_Y()-P.Get_Y() , E[i].Get_Rad()-E[i].Get_Health()/10-1, makecol (255,0,0));
            circle (buffer, SCREEN_X/2+E[i].Get_X()-P.Get_X() , SCREEN_Y/2+E[i].Get_Y()-P.Get_Y() , E[i].Get_Rad(), makecol (255,0,0));
         }
     if (shotX > -1 && shotY > -1 && P.Get_ActiveWeapon() == 0)
     {
        if (key[KEY_W] || key[KEY_S])
           for (int i = 0; i <= P.Get_Quantity(1)*3;i++)
           {
               vline (buffer, SCREEN_X/2+i, SCREEN_Y/2+shotY-P.Get_Y(), SCREEN_Y/2, makecol (255,0,0));
               vline (buffer, SCREEN_X/2-i, SCREEN_Y/2+shotY-P.Get_Y(), SCREEN_Y/2, makecol (255,0,0));
           }
        else if (key[KEY_A] || key[KEY_D])
             for (int i = 0; i <= P.Get_Quantity(1)*3;i++)
             {
                 hline (buffer, SCREEN_X/2, SCREEN_Y/2+i, SCREEN_X/2+shotX-P.Get_X(), makecol (255,0,0));
                 hline (buffer, SCREEN_X/2, SCREEN_Y/2-i, SCREEN_X/2+shotX-P.Get_X(), makecol (255,0,0));
             }
        if (P.Get_Quantity(3))
           circlefill (buffer, SCREEN_X/2+shotX-P.Get_X(), SCREEN_Y/2+shotY-P.Get_Y(), 30, makecol (255,0,0));
     }
     else if (shotX > -1 && shotY > -1 && P.Get_ActiveWeapon() == 1)
     {
          circlefill (buffer, SCREEN_X/2+shotX-P.Get_X(), SCREEN_Y/2+shotY-P.Get_Y(), 40, makecol (255,0,0));
     }
     else if (shotX == -1 || shotY == -1)
     {
          if (key[KEY_W])
             for (int i = -P.Get_Quantity(1)*3; i <= P.Get_Quantity(1)*3;i++)
                 vline (buffer, SCREEN_X/2+i, SCREEN_Y/2, SCREEN_Y/2-B.Get_Range(), makecol (255,0,0));
          else if (key[KEY_A])
               for (int i = -P.Get_Quantity(1)*3; i <= P.Get_Quantity(1)*3;i++)
                   hline (buffer, SCREEN_X/2, SCREEN_Y/2+i, SCREEN_X/2-B.Get_Range(), makecol (255,0,0));
          else if (key[KEY_S])
               for (int i = -P.Get_Quantity(1)*3; i <= P.Get_Quantity(1)*3;i++)
                   vline (buffer, SCREEN_X/2+i, SCREEN_Y/2, SCREEN_Y/2+B.Get_Range(), makecol (255,0,0));
          else if (key[KEY_D])
               for (int i = -P.Get_Quantity(1)*3; i <= P.Get_Quantity(1)*3;i++)
                   hline (buffer, SCREEN_X/2, SCREEN_Y/2+i, SCREEN_X/2+B.Get_Range(), makecol (255,0,0));
     }
     if (B.Number_of_Bombs() > 0)
     {
        for (int i = 0; i < B.Number_of_Bombs(); i++)
            circlefill (buffer, SCREEN_X/2+B.Get_BombX(i)-P.Get_X(), SCREEN_Y/2+B.Get_BombY(i)-P.Get_Y(), 3, makecol(255,150,0));
     }
     if (B.Get_GrenadeTimer() > 0)
        circlefill (buffer, SCREEN_X/2+B.Get_GrenadeX()-P.Get_X(), SCREEN_Y/2+B.Get_GrenadeY()-P.Get_Y(), 2, makecol (0,64,0));
     if (!shot)
        circlefill (buffer, SCREEN_X/2, SCREEN_Y/2, 5, makecol(0,0,255));
     else
     {
         circlefill (buffer, SCREEN_X/2, SCREEN_Y/2, 5, makecol(255,0,0));
     }
     if (P.Get_InitialHealth()-P.Get_Health() >= 0)
        circlefill (buffer, SCREEN_X/2, SCREEN_Y/2, (P.Get_InitialHealth()-P.Get_Health())/(P.Get_InitialHealth()/5), makecol(150,150,255)); 
     textprintf_ex(buffer, font, 500+GRID_SIZE*2, 500, makecol(255,0,0), -1, "Health: %d", P.Get_Health());
     textprintf_ex(buffer, font, 500+GRID_SIZE*2, 520, makecol(255,0,0), -1, "Enemies: %d", E.size());
     textprintf_ex(buffer, font, 500+GRID_SIZE*2, 540, makecol(255,0,0), -1, "Money: %d", P.Get_Money());
     textprintf_ex(buffer, font, 500+GRID_SIZE*2, 560, makecol(255,0,0), -1, "Weapon:\n%s", P.Get_ActiveWeapon() == 0 ? "Gun" : ( P.Get_ActiveWeapon() == 1 ? "Grenade" : "Walls"));
     
    // textprintf_ex(buffer, font, 605, 560, makecol(255,0,0), -1, "%d %d %d %d %d %d", P.Get_Quantity (0), P.Get_Quantity (1), P.Get_Quantity (2), P.Get_Quantity (3), P.Get_Quantity (4), P.Get_Quantity (5));
        
     scare_mouse();
     acquire_screen();
     draw_sprite (screen, buffer,0,0);
     release_screen(); 
     unscare_mouse();*/
}

void Display::DrawUpgrade()
{
    Player P(0,0);// TODO extract player
    draw_sprite (buffer,upgradeScreen,0,0);
    int rate = P.GetWeaponProperties(_Gun).GetFireRate();
    int clip = P.GetWeaponProperties(_Gun).GetClipSize();
    int range = P.GetWeaponProperties(_Gun).GetRange();
    int health = P.GetHealth();
    int money = P.GetMoney();
    textprintf_ex(buffer, font, 180, 162, makecol(255,255,255), -1, "%d Cost: %d", rate, 250*(11-rate)*(11-rate));
    textprintf_ex(buffer, font, 180, 201, makecol(255,255,255), -1, "%d Cost: %d", clip, 5*clip);
    textprintf_ex(buffer, font, 180, 240, makecol(255,255,255), -1, "%d Cost: %d", range, range*2);
    textprintf_ex(buffer, font, 180, 279, makecol(255,255,255), -1, "%d Cost: %d", health, 100);
    textprintf_ex(buffer, font, 300, 162, makecol(255,255,255), -1, "Money: %d", money);
//    textprintf_ex(buffer, font, 400, 355, makecol(255,255,255), -1, "N %d Cost: %d", P.Get_Quantity(0), P.Get_Cost(0));
//    textprintf_ex(buffer, font, 400, 394, makecol(255,255,255), -1, "W %d Cost: %d", P.Get_Quantity(1), P.Get_Cost(1));
//    textprintf_ex(buffer, font, 400, 433, makecol(255,255,255), -1, "G %d Cost: %d", P.Get_Quantity(2), P.Get_Cost(2));
//    textprintf_ex(buffer, font, 400, 472, makecol(255,255,255), -1, "E %d Cost: %d", P.Get_Quantity(3), P.Get_Cost(3));
//    textprintf_ex(buffer, font, 400, 511, makecol(255,255,255), -1, "M %d Cost: %d", P.Get_Quantity(4), P.Get_Cost(4));
//    textprintf_ex(buffer, font, 400, 550, makecol(255,255,255), -1, "S %d Cost: %d", P.Get_Quantity(5), P.Get_Cost(5));
    draw_sprite (screen,buffer,0,0);
}

void Display::SetBackground ()
{
    Map *mapInst = Map::GetInstance();
    int **map = mapInst->GetGrid();
    int size = mapInst->GetGridSize();
    rectfill(background,0,0,size*BOX_PIXEL_WIDTH,size*BOX_PIXEL_WIDTH,makecol(0,0,0));
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (map[i][j] == 0)
                rectfill (background,i*BOX_PIXEL_WIDTH,j*BOX_PIXEL_WIDTH,i*(BOX_PIXEL_WIDTH+1)-1,j*(BOX_PIXEL_WIDTH+1)-1,makecol(255,255,255));
            else if (map[i][j] == 2)
                rectfill (background,i*BOX_PIXEL_WIDTH,j*BOX_PIXEL_WIDTH,i*(BOX_PIXEL_WIDTH+1)-1,j*(BOX_PIXEL_WIDTH+1)-1,makecol(255,0,254));
            else if (map[i][j] == 3)
                rectfill (background,i*BOX_PIXEL_WIDTH,j*BOX_PIXEL_WIDTH,i*(BOX_PIXEL_WIDTH+1)-1,j*(BOX_PIXEL_WIDTH+1)-1,makecol(0,255,0));
}

void Display::UpdateMiniMap (int centreX, int centreY)
{
    Map *mapInst = Map::GetInstance();
    int **map = mapInst->GetGrid();
    int size = mapInst->GetGridSize();
    for (int i = centreX-5; i < centreX+5 && i >= 0 && i < size; i++)
        for (int j = centreY-5; j < centreY+5 && j >= 0 && j < size; j++)
            if (map[i][j] == 0)
                rectfill (miniMap,i*2,j*2,i*2+1,j*2+1,makecol(255,255,255));
            else if (map[i][j] == 1)
                rectfill (miniMap,i*2,j*2,i*2+1,j*2+1,makecol(0,0,0));
            else if (map[i][j] == 2)
                rectfill (miniMap,i*2,j*2,i*2+1,j*2+1,makecol(255,0,254));
            else if (map[i][j] == 3)
                rectfill (miniMap,i*2,j*2,i*2+1,j*2+1,makecol(0,255,0));
}

void Display::Zoom (int centreX, int centreY)
{
    Map *mapInst = Map::GetInstance();
    int **map = mapInst->GetGrid();
    int size = mapInst->GetGridSize();
    //int n[GRID_SIZE][GRID_SIZE], bool b[GRID_SIZE][GRID_SIZE], int x, int y, Player &p, vector <Enemy> &E
    rectfill (miniMap,0,size*2,size*2,size*4,makecol (100,100,100));
    for (int i = -(int)floor(size/10); i < (int)floor(size/10); i++)
        for (int j = -(int)floor(size/10); j < (int)floor(size/10); j++)
            if (i+centreX >= 0 && i+centreX < size  && j+centreY >= 0 && j+centreY < size)
                if (mapInst->Fog(centreX+i, centreY+j))
                {
                    if (map[centreX+i][centreY+j] == 0)
                        rectfill (miniMap,(i+(int)floor(size/10))*10,size*2+(j+(int)floor(size/10))*10,(i+(int)floor(size/10))*10+9,size*2+(j+(int)floor(size/10))*10+9,makecol(255,255,255));
                    else if (map[centreX+i][centreY+j] == 1)
                        rectfill (miniMap,(i+(int)floor(size/10))*10,size*2+(j+(int)floor(size/10))*10,(i+(int)floor(size/10))*10+9,size*2+(j+(int)floor(size/10))*10+9,makecol(0,0,0));
                    else if (map[centreX+i][centreY+j] == 2)
                        rectfill (miniMap,(i+(int)floor(size/10))*10,size*2+(j+(int)floor(size/10))*10,(i+(int)floor(size/10))*10+9,size*2+(j+(int)floor(size/10))*10+9,makecol(255,0,254));
                    else if (map[centreX+i][centreY+j] == 3)
                        rectfill (miniMap,(i+(int)floor(size/10))*10,size*2+(j+(int)floor(size/10))*10,(i+(int)floor(size/10))*10+9,size*2+(j+(int)floor(size/10))*10+9,makecol(0,255,0));
                }
//    for (int i = 0; i < E.size(); i++)
//        if ((E[i].Get_Y()/BOX_PIXEL_WIDTH-centreY+(int)floor(size/10))*10 >= 0 && (E[i].Get_Y()/BOX_PIXEL_WIDTH-centreY+(int)floor(size/10))*10 < size*2 && mapInst->Fog(E[i].Get_X()/BOX_PIXEL_WIDTH, E[i].Get_Y()/BOX_PIXEL_WIDTH))
//            for (int j = 0; j < 2; j++)
//                rect (miniMap,(E[i].Get_X()/BOX_PIXEL_WIDTH-centreX+(int)floor(size/10))*10+j,size*2+(E[i].Get_Y()/BOX_PIXEL_WIDTH-centreY+(int)floor(size/10))*10+j,(E[i].Get_X()/BOX_PIXEL_WIDTH-centreX+(int)floor(size/10))*10+9-j,size*2+(E[i].Get_Y()/60-centreY+(int)floor(size/10))*10+9-j,makecol(255,0,0));
//    if ((p.Get_Y()/BOX_PIXEL_WIDTH-centreY+(int)floor(size/10))*10 >= 0 && (p.Get_Y()/BOX_PIXEL_WIDTH-centreY+(int)floor(size/10))*10 < size*2)
//        for (int i = 0; i < 2; i++)
//            rect (miniMap,(p.Get_X()/BOX_PIXEL_WIDTH-centreX+(int)floor(size/10))*10+i,size*2+(p.Get_Y()/BOX_PIXEL_WIDTH-centreY+(int)floor(size/10))*10+i,(p.Get_X()/BOX_PIXEL_WIDTH-centreX+(int)floor(size/10))*10+9-i,size*2+(p.Get_Y()/BOX_PIXEL_WIDTH-centreY+(int)floor(size/10))*10+9-i,makecol(0,0,255));
     
}

void Display::NukeAnimation ()
{
    for (int i = 1; i < 45; i++)
    {
        circlefill (buffer, SCREEN_X/2, SCREEN_Y/2, i*10, makecol(255,i*8,0));
        draw_sprite (screen, buffer, 0, 0);
        rest (1);
    }
}

void Display::WallAnimation (int x1, int y1, int x2, int y2, int i)
{
    rectfill (screen,x1,y1,x2,y2,makecol(i*5,i*5,i*5));
}
