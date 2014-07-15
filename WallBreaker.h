#ifndef __WALLBREAKER_H__
#define __WALLBREAKER_H__

#include "Weapon.h"
class Character;

class WallBreaker : public Weapon
{
    private:
        static const int VELOCITY;
        int direction;
        
    public:
        WallBreaker(int xPos, int yPos, WeaponProperties weaponProperties, int direction, Character * watcher);
        void Action(Character * character);
        void Update();
        void Detonate();
};

#endif
