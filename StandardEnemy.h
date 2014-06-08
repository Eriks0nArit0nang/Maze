#ifndef __STANDARDENEMY_H__
#define __STANDARDENEMY_H__


#include "Character.h"

class StandardEnemy : public Character
{
    
    public:
        StandardEnemy(int health, double xPos, double yPos, int radius, WeaponType activeWeapon, WeaponProperties weaponProperties[WEAPON_TYPES]);
        void Attack ();     
        void Move ();
};

#endif
