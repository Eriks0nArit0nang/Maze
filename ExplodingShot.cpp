#include "ExplodingShot.h"

ExplodingShot::ExplodingShot(AbstractGun * gun):AbstractGunDecorator(gun)
{
    WeaponProperties properties(_ExplodingShot, 0);
    GetProperties().damage += properties.GetDamage();
}

void ExplodingShot::Detonate()
{
    WeaponProperties properties(_ExplodingShot, 0);
    GetProperties().radius = properties.GetRadius();
    gun->GetProperties().radius = properties.GetRadius();
    destroyThis = true;
    gun->Detonate();
}

void ExplodingShot::Draw(BITMAP *buffer, int midX, int midY)
{
    circlefill (buffer, midX+gun->GetX(), midY+gun->GetY(), GetProperties().GetRadius(), makecol (255,0,0));
    gun->Draw(buffer, midX, midY);
}
