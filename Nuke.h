#ifndef __NUKE_H__
#define __NUKE_H__

#include "Weapon.h"
class Character;

class Nuke : public Weapon
{
    public:
        Nuke(int xPos, int yPos, WeaponProperties weaponProperties);
        void Update();
        void Detonate();
        void Action(Character * character);
};

#endif