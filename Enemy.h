#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Character.h"

class Enemy : public Character
{
    public:
        Enemy(int health, double xPos, double yPos, int radius, WeaponType activeWeapon);
        bool Visit (AbstractGun &gun);
        bool Visit (Grenade &grenade);
        bool Visit (Bomb &bomb);
        bool Visit (Nuke &nuke);
};

#endif
