#ifndef __BOMB_H__
#define __BOMB_H__

#include "Weapon.h"
class Character;

class Bomb : public Weapon
{
    private:
        int timer;
    
    public:
        Bomb(int xPos, int yPos, WeaponProperties weaponProperties);
        void Update();
        void Detonate();
        void Action(Character *character);
};

#endif
