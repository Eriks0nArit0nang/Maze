#include "WideShot.h"

WideShot::WideShot(AbstractGun *gun):AbstractGunDecorator(gun)
{
    WeaponProperties properties(_WideShot, 0);
    GetProperties().radius = properties.GetRadius();
}
