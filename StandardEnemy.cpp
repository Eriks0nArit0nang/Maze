#include "StandardEnemy.h"
#include "Globals.h"
#include "Player.h"
#include "Map.h"
#include <cmath>

StandardEnemy::StandardEnemy(int health, double xPos, double yPos, int radius):
    Character(health, xPos, yPos, radius, _Enemy)
{
    InitializeWeaponProperties();
}

void StandardEnemy::InitializeWeaponProperties()
{
    weaponProperties[_None] = WeaponProperties(_None, 0);
    weaponProperties[_Gun] = WeaponProperties(_Gun, 0);
    weaponProperties[_WideShot] = WeaponProperties(_WideShot, 0);
    weaponProperties[_ExplodingShot] = WeaponProperties(_ExplodingShot, 0);
    weaponProperties[_Grenade] = WeaponProperties(_Grenade, 0);
    weaponProperties[_Mine] = WeaponProperties(_Mine, 0);
    weaponProperties[_Nuke] = WeaponProperties(_Nuke, 0);
    weaponProperties[_WallBreaker] = WeaponProperties(_WallBreaker, 0);
    weaponProperties[_Enemy] = WeaponProperties(_Enemy, -1);
}

void StandardEnemy::Attack ()
{
    weapons.push_back(new EnemyWeapon(GetX(), GetY(), GetWeaponProperties(activeWeapon)));
}     

void StandardEnemy::Move ()
{
    int **check = Map::GetInstance()->GetDistFromPlayer();
    Player p(0,0); // TODO extract player from somewhere (Game Class)
    if (!(p.GetX()/BOX_PIXEL_WIDTH==GetX()/BOX_PIXEL_WIDTH&&p.GetY()/BOX_PIXEL_WIDTH==GetY()/BOX_PIXEL_WIDTH))
     {
        if (check[GetX()/BOX_PIXEL_WIDTH][GetY()/BOX_PIXEL_WIDTH] > 0)
        {
           int i = GetX()/BOX_PIXEL_WIDTH, j = GetY()/BOX_PIXEL_WIDTH;
           if (check[i-1][j] == check[i][j]-1)
           {
              if (abs(GetY() % BOX_PIXEL_WIDTH - BOX_PIXEL_WIDTH/2) < BOX_PIXEL_WIDTH/2 - radius)
                 xPos-=xVel;
              else
                  yPos += (BOX_PIXEL_WIDTH/2 - GetY() % BOX_PIXEL_WIDTH)/abs (BOX_PIXEL_WIDTH/2 - GetY() % BOX_PIXEL_WIDTH)*yVel;
           }
           else if (check[i+1][j] == check[i][j]-1)
           {
                if (abs(GetY() % BOX_PIXEL_WIDTH - BOX_PIXEL_WIDTH/2) < BOX_PIXEL_WIDTH/2-radius)
                   xPos+=xVel;
                else
                  yPos += (BOX_PIXEL_WIDTH/2 - GetY() % BOX_PIXEL_WIDTH)/abs (BOX_PIXEL_WIDTH/2 - GetY() % BOX_PIXEL_WIDTH)*yVel;
           }
           else if (check[i][j-1] == check[i][j]-1)
           {
                if (abs(GetX() % BOX_PIXEL_WIDTH - BOX_PIXEL_WIDTH/2) < BOX_PIXEL_WIDTH/2-radius)
                   yPos-=yVel;
                else
                  xPos += (BOX_PIXEL_WIDTH/2 - GetX() % BOX_PIXEL_WIDTH)/abs (BOX_PIXEL_WIDTH/2 - GetX() % BOX_PIXEL_WIDTH)*xVel;
           }
           else if (check[i][j+1] == check[i][j]-1)
           {
                if (abs(GetX() % BOX_PIXEL_WIDTH - BOX_PIXEL_WIDTH/2) < BOX_PIXEL_WIDTH/2-radius)
                   yPos+=yVel;
                else
                  xPos += (BOX_PIXEL_WIDTH/2 - GetX() % BOX_PIXEL_WIDTH)/abs (BOX_PIXEL_WIDTH/2 - GetX() % BOX_PIXEL_WIDTH)*xVel;
           }
        }
     }
     else
     {
         int x = -GetX()+p.GetX(), y = -GetY()+p.GetY();
         if (x != 0)
         {
            if (abs(GetX() % BOX_PIXEL_WIDTH - BOX_PIXEL_WIDTH/2) >= BOX_PIXEL_WIDTH/2-radius)
               xPos += (BOX_PIXEL_WIDTH/2 - GetX() % BOX_PIXEL_WIDTH)/abs (BOX_PIXEL_WIDTH/2 - GetX() % BOX_PIXEL_WIDTH)*xVel;
            else
            {
                xPos += x/abs(x)*std::min(xVel,(double)abs(x));
                if (abs(GetX() % BOX_PIXEL_WIDTH - BOX_PIXEL_WIDTH/2) >= BOX_PIXEL_WIDTH/2-radius)
                   xPos += (BOX_PIXEL_WIDTH/2 - GetX() % BOX_PIXEL_WIDTH)/abs (BOX_PIXEL_WIDTH/2 - GetX() % BOX_PIXEL_WIDTH)*xVel;
            }
         }
         if (y != 0)
         {
            if (abs(GetY() % BOX_PIXEL_WIDTH - BOX_PIXEL_WIDTH/2) >= BOX_PIXEL_WIDTH/2-radius)
               yPos += (BOX_PIXEL_WIDTH/2 - GetY() % BOX_PIXEL_WIDTH)/abs (BOX_PIXEL_WIDTH/2 - GetY() % BOX_PIXEL_WIDTH)*yVel;
            else
            {
                yPos += y/abs(y)*std::min(yVel,(double)abs(y));
                if (abs(GetY() % BOX_PIXEL_WIDTH - BOX_PIXEL_WIDTH/2) >= BOX_PIXEL_WIDTH-radius)
                   yPos += (BOX_PIXEL_WIDTH/2 - GetY() % BOX_PIXEL_WIDTH)/abs (BOX_PIXEL_WIDTH/2 - GetY() % BOX_PIXEL_WIDTH)*yVel;
            }
         }
     }
}

