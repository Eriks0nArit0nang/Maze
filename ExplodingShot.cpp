#include "ExplodingShot.h"

ExplodingShot::ExplodingShot(AbstractGun * gun):AbstractGunDecorator(gun){}

void ExplodingShot::Detonate()
{
    WeaponProperties properties(_ExplodingShot, 0);
    GetProperties().radius = properties.GetRadius();
    destroyThis = true;
}
