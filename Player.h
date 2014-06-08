#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Character.h"

class Player : public Character
{
    
    public:
        Player(int health, double xPos, double yPos, int radius, WeaponType activeWeapon, WeaponProperties weaponProperties[WEAPON_TYPES]);
        void Attack ();     
        void Move ();
};

#endif
