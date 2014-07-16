#include "ExplodingShot.h"

ExplodingShot::ExplodingShot(AbstractGun * gun):AbstractGunDecorator(gun){}

void ExplodingShot::Detonate()
{
    WeaponProperties properties(_ExplodingShot, 0);
    GetProperties().radius = properties.GetRadius();
    destroyThis = true;
}

void ExplodingShot::Draw(BITMAP *buffer, int midX, int midY)
{
    circlefill (buffer, midX+GetX(), midY+GetY(), GetProperties().radius, makecol (255,0,0));
    gun->Draw(buffer, midX, midY);
}
