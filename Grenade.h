#ifndef __GRENADE_H__
#define __GRENADE_H__

#include "Weapon.h"
class Character;

class Grenade : public Weapon
{
    private:
        int velocity;
        int direction;
        int timer;
    
    public:
        Grenade(int xPos, int yPos, WeaponProperties weaponProperties, int direction);
        void Update();
        void Detonate();
        void Action(Character * character);
};

#endif
