#include "FloatingEnemy.h"
#include "Globals.h"
#include "Player.h"
#include "Map.h"
#include "Game.h"
#include <cmath>
#include <allegro5/allegro_primitives.h>

FloatingEnemy::FloatingEnemy(int health, double xPos, double yPos):
    Enemy(health, xPos, yPos, health/10+1, _Enemy)
{
    InitializeWeaponProperties();
    xVel = std::max(1.0,75.0/(1.0*health));
    yVel = std::max(1.0,75.0/(1.0*health));
    
}

void FloatingEnemy::InitializeWeaponProperties()
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
    weaponProperties[_Enemy].SetDamage(std::min(2*(health/10+1),weaponProperties[_Enemy].GetDamage()));
}

void FloatingEnemy::Attack ()
{
    attackDelay--;
    if (attackDelay == GetWeaponProperties(activeWeapon).GetFireRate() - 1)
    {
        delete weapons[0];
        weapons.pop_back();
    }
    else if (attackDelay <= 0)
    {
        weapons.push_back(new EnemyWeapon(GetX(), GetY(), GetWeaponProperties(activeWeapon), this));
        attackDelay = GetWeaponProperties(activeWeapon).GetFireRate();
    }
}     

void FloatingEnemy::Move ()
{
    Player &p = *Game::GetInstance()->GetPlayer();
    int x = -GetX()+p.GetX(), y = -GetY()+p.GetY();
    if (sqrt(pow(x,2.0)+pow(y,2.0)) < 425)
    {
        if (x != 0)
            xPos += x/abs(x)*std::min(xVel,(double)abs(x));
        if (y != 0)
            yPos += y/abs(y)*std::min(yVel,(double)abs(y));
     }
}

void FloatingEnemy::Draw(ALLEGRO_BITMAP *buffer, int midX, int midY)
{
    for (unsigned int i = 0; i < weapons.size(); i++)
        weapons[i]->Draw(buffer, midX, midY);
    al_set_target_bitmap(buffer);
    al_draw_filled_triangle (midX+GetX(),midY+GetY()+radius,midX+GetX()+2*radius,midY+GetY()-radius/2,midX+GetX()-2*radius,midY+GetY()-radius/2,al_map_rgb(255,0,0));
    al_draw_filled_circle (midX+GetX(), midY+GetY(), radius, al_map_rgb (255,255,0));
    al_draw_filled_circle (midX+GetX(), midY+GetY(), radius-GetHealth()/10-1, al_map_rgb (255,0,0));
    al_draw_circle (midX+GetX(), midY+GetY(), radius, al_map_rgb (255,0,0), 0);
        
}
