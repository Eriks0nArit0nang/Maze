#ifndef __ABSTRACTGUN_H__
#define __ABSTRACTGUN_H__

#include "Weapon.h"
class Character;

class AbstractGun : public Weapon
{
    protected:
        static const int VELOCITY;
        int direction;
    
    public:
        AbstractGun(int xPos, int yPos, WeaponProperties weaponProperties, int direction);
        void Action(Character * character);
};


#endif
