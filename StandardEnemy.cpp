#include "StandardEnemy.h"
#include "Globals.h"
#include "Player.h"
#include "Map.h"
#include "Game.h"
#include <cmath>
#include <iostream> // TODO remove once done debugging
StandardEnemy::StandardEnemy(int health, double xPos, double yPos):
    Character(health, xPos, yPos, health/10+1, _Enemy)
{
    InitializeWeaponProperties();
    weapons.push_back(new EnemyWeapon(GetX(), GetY(), GetWeaponProperties(activeWeapon), this));
    xVel = std::max(1.0,75.0/(1.0*health));
    yVel = std::max(1.0,75.0/(1.0*health));
    
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
    // Nothing to do
}     

void StandardEnemy::Move ()
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

void StandardEnemy::Draw(BITMAP *buffer, int midX, int midY)
{
    for (int i = 0; i < weapons.size(); i++)
        weapons[i]->Draw(buffer, midX, midY);
    circlefill (buffer, midX+GetX(), midY+GetY(), radius, makecol (255,255,0));
    circlefill (buffer, midX+GetX(), midY+GetY(), radius-GetHealth()/10-1, makecol (255,0,0));
    circle (buffer, midX+GetX(), midY+GetY(), radius, makecol (255,0,0));
        
}

bool StandardEnemy::Visit (AbstractGun &gun)
{
    if (InRange(gun.GetX(), gun.GetY(), gun.GetProperties().GetRadius()))
    {
        Hit(gun.GetProperties().GetDamage());
        return true;
    }
    return false;
}

bool StandardEnemy::Visit (Grenade &grenade)
{
    if (InRange(grenade.GetX(), grenade.GetY(), grenade.GetProperties().GetRadius()))
    {
        Hit(grenade.GetProperties().GetDamage());
        return true;
    }
    return false;
}

bool StandardEnemy::Visit (Bomb &bomb)
{
    if (InRange(bomb.GetX(), bomb.GetY(), bomb.GetProperties().GetRadius()))
    {
        Hit(bomb.GetProperties().GetDamage());
        return true;
    }
    return false;
}

bool StandardEnemy::Visit (Nuke &nuke)
{
    if (InRange(nuke.GetX(), nuke.GetY(), nuke.GetProperties().GetRadius()))
    {
        Hit(nuke.GetProperties().GetDamage());
    }
    return false;
}
