#include "ShootingEnemy.h"
#include "Globals.h"
#include "Player.h"
#include "Map.h"
#include "Game.h"
#include "Gun.h"
#include <cmath>

ShootingEnemy::ShootingEnemy(int health, double xPos, double yPos):
    Enemy(health, xPos, yPos, health/10+1, _Gun)
{
    InitializeWeaponProperties();
    xVel = std::max(1.0,75.0/(1.0*health));
    yVel = std::max(1.0,75.0/(1.0*health));
    
}

void ShootingEnemy::InitializeWeaponProperties()
{
    weaponProperties[_None] = WeaponProperties(_None, 0);
    weaponProperties[_Gun] = WeaponProperties(_Gun, 1);
    weaponProperties[_Gun].SetRange(std::max(health,60));
    weaponProperties[_Gun].SetDamage(std::min(2*(health/10+1),weaponProperties[_Gun].GetDamage()));
    weaponProperties[_WideShot] = WeaponProperties(_WideShot, 0);
    weaponProperties[_ExplodingShot] = WeaponProperties(_ExplodingShot, 0);
    weaponProperties[_Grenade] = WeaponProperties(_Grenade, 0);
    weaponProperties[_Mine] = WeaponProperties(_Mine, 0);
    weaponProperties[_Nuke] = WeaponProperties(_Nuke, 0);
    weaponProperties[_WallBreaker] = WeaponProperties(_WallBreaker, 0);
    weaponProperties[_Enemy] = WeaponProperties(_Enemy, -1);
}

void ShootingEnemy::Attack ()
{
    attackDelay--;
    Player *p = Game::GetInstance()->GetPlayer();
    if (attackDelay <= 0 && (abs(p->GetX()-GetX()) <= GetWeaponProperties(activeWeapon).GetRange() ||
                             abs(p->GetY()-GetY()) <= GetWeaponProperties(activeWeapon).GetRange()))
    {
        int xDiff = p->GetX()-GetX();
        int yDiff = p->GetY()-GetY();
        if (xDiff <= GetWeaponProperties(activeWeapon).GetRange() && xDiff >= 0 && abs(yDiff) < 10)
            weapons.push_back(new Gun(GetX(), GetY(), GetWeaponProperties(activeWeapon), 1000, this));
        else if (xDiff >= -GetWeaponProperties(activeWeapon).GetRange() && xDiff < 0 && abs(yDiff) < 10)
            weapons.push_back(new Gun(GetX(), GetY(), GetWeaponProperties(activeWeapon), 100, this));
        else if (yDiff <= GetWeaponProperties(activeWeapon).GetRange() && yDiff >= 0 && abs(xDiff) < 10)
            weapons.push_back(new Gun(GetX(), GetY(), GetWeaponProperties(activeWeapon), 10, this));
        else if (yDiff >= -GetWeaponProperties(activeWeapon).GetRange() && yDiff < 0 && abs(xDiff) < 10)
            weapons.push_back(new Gun(GetX(), GetY(), GetWeaponProperties(activeWeapon), 1, this));
        attackDelay = GetWeaponProperties(activeWeapon).GetFireRate();
    }
}     

void ShootingEnemy::Move ()
{
    int **check = Map::GetInstance()->GetDistFromPlayer();
    Player &p = *Game::GetInstance()->GetPlayer();
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

void ShootingEnemy::Draw(BITMAP *buffer, int midX, int midY)
{
    for (int i = 0; i < weapons.size(); i++)
        weapons[i]->Draw(buffer, midX, midY);
    circlefill (buffer, midX+GetX(), midY+GetY(), radius, makecol (255,150,150));
    circlefill (buffer, midX+GetX(), midY+GetY(), radius-GetHealth()/10-1, makecol (255,0,0));
    circle (buffer, midX+GetX(), midY+GetY(), radius, makecol (255,0,0));
        
}
