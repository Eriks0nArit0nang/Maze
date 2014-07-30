#ifndef __EXPLODINGSHOT_H__
#define __EXPLODINGSHOT_H__

#include "AbstractGunDecorator.h"

class ExplodingShot : public AbstractGunDecorator
{
    public:
        ExplodingShot(AbstractGun * gun);
        void Detonate();
        void Draw(ALLEGRO_BITMAP *buffer, int midX, int midY);
};

#endif
