#ifndef __ABSTRACTGUNDECORATOR_H__
#define __ABSTRACTGUNDECORATOR_H__

#include "AbstractGun.h"
class Character;

class AbstractGunDecorator : public AbstractGun
{
    protected:
        AbstractGun * gun;
        
    public:
        AbstractGunDecorator(AbstractGun * gun);
        void Update();
        void Detonate();
        void Action( Character * character);
        int GetX() const;
        int GetY() const;
        WeaponProperties &GetProperties();
};

#endif
