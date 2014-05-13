#ifndef __ABSTRACTGUNDECORATOR_H__
#define __ABSTRACTGUNDECORATOR_H__

#include "AbstractGun.h"

class AbstractGunDecorator : public AbstractGun
{
    private:
        AbstractGun * gun;
        
    public:
        AbstractGunDecorator(AbstractGun * gun);
        void Update();
        void Detonate();
};

#endif
