#ifndef __GUN_H__
#define __GUN_H__

#include "AbstractGun.h"

class Gun : public AbstractGun
{
    private:
        
    public:
        Gun(int xPos, int yPos, WeaponProperties weaponProperties, int direction);
        void Update();
        void Detonate();
};

#endif
