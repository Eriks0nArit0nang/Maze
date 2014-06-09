#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Character.h"

class Player : public Character
{
    private:
        static const int HEALTH;
        static const int RADIUS;
    public:
        Player(double xPos, double yPos, WeaponProperties weaponProperties[WEAPON_TYPES]);
        void Attack ();     
        void Move ();
};

#endif
