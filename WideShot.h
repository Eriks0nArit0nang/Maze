#ifndef __WIDESHOT_H__
#define __WIDESHOT_H__

#include "AbstractGunDecorator.h"

class WideShot : public AbstractGunDecorator
{
    public:
        WideShot(AbstractGun * gun);
};

#endif
